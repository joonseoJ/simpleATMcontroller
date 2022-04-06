#include "atm_machine.h"
#include "atm_exception.h"
#include <iostream>
#include <limits>

AtmMachine::AtmMachine():
	isCardInserted(false),
	isDollarTaken(true),
	insertedDollar(0)
{
	card = Card();
	accountIndex = -1;
}

void AtmMachine::clearCard(){
	card.clearCompanyAndUserName();
	isCardInserted = false;
}

void AtmMachine::clearAccounts(){
	accounts.clear();
	accountIndex = -1;
}

void AtmMachine::clearCardAndAccounts(){
	clearCard();
	clearAccounts();
}

void AtmMachine::askCardInformation(){
	std::string cardCompany, userName;

	moveCursor(0, 4);
	std::cout<<"What's your card company and user name?"<<std::endl;
	std::cout<<"Card Company: ";
	getline(std::cin, cardCompany);
	std::cout<<"User Name: ";
	getline(std::cin, userName);
	try{
		card.setCompanyAndUserName(cardCompany, userName);
		isCardInserted = true;
	}
	catch(CardException& e){
		std::cerr<< e.what()<< std::endl;
		throw NoCardException();
	}
	return;
}

void AtmMachine::askPinNumber(){
	std::cout<<"Insert 4 digits Pin Number Please"<<std::endl;
	std::cout<<"Pin Number: ";
	int pinNumber;
	for(int tryCount = 0; tryCount < 5; tryCount++){
		try{
			pinNumber = getFourDigitPinNumber();
			if(isPinCorrect(pinNumber)){
				return;	
			}
			else{
				visualizeMainLogoOnly();
				std::cout<<"Insert 4 digits Pin Number Please. Wrong pin, you have "<<4-tryCount<<" chance"<<std::endl;
				std::cout<<"Pin Number: ";
			}
		}
		catch(InvalidIntegerException& e){
			visualizeMainLogoOnly();
			std::cout<<"Insert 4 digits Pin Number Please. Pin must be 4 digits integer!"<<std::endl;
			std::cout<<"Pin Number: ";
		}
	}
	clearCardAndAccounts();
	visualizeMainLogoOnly();
	throw InvalidPinException();
	return;
}

int AtmMachine::getFourDigitPinNumber(){
	std::string pins;
	unsigned char isDigit = 0b0000;
	for(int i = 0; i < 4;){
		int pin = getch();
		if(pin == 8 || pin == 127){
			if(pins.empty()) continue;
			pins.pop_back();
			std::cout<<"\b \b\b \b";
			isDigit &= ~(1<<i-1);
			i--;
		}
		else if(pin == '\n' || pin=='\r'){
			throw InvalidIntegerException();
			return 0;
		}
		else if(pin == 3){
			throw TerminalizeException();
			return 0;
		}
		else{
			std::cout<<"* ";
			pins.push_back(pin);
			isDigit |= isdigit(pins.back()) << i;
			i++;
		}
	}
	std::cout<<std::endl;
	if(isDigit == 0b1111){
		return std::stoi(pins);
	}
	else{
		throw InvalidIntegerException();
		return 0;
	}
}

bool AtmMachine::isPinCorrect(int pin){
	if(isCardInserted && pin >= 0 && pin < 10000){
		// TODO: implement bank api for pin correction
		return true;
	}
	else{
		return false;
	}
}

void AtmMachine::getEveryAccounts(){
	// TODO: implement bank api for get accounts
	std::vector<int> accountDisplayCounts = {3,6,2,3};
	Account tempAccount;
	for(int i = 1; i < 6; i++){
		std::string accountCandidate;
		for(int j : accountDisplayCounts){
			for(int k = 0; k < j; k++){
				accountCandidate += std::to_string(i);
			}
			accountCandidate.push_back('-');
		}
		accountCandidate.pop_back();
		tempAccount.setAccountNumberAndBalance(accountCandidate, 0);
		accounts.push_back(tempAccount);
	}
}

void AtmMachine::askToChooseAccount(){
	if(!isCardInserted){
		throw NoCardException();
		return;
	}
	if(accounts.empty()){
		throw NoAccountException();
		return;
	}

	//visualizeMainLogoOnly();
	std::cout<<"Choose Account by number"<<std::endl;
	for(int i = 1; i <= accounts.size(); i++){
		std::cout<<i<<": "<<accounts[i-1].getAccountNumber()<<std::endl;
	}
	std::cout<<"Account number: ";
	for(int tryCount = 0; tryCount < 5; tryCount++){
		try{
			getValidInteger(accountIndex);
			if(accountIndex <= 0 || accountIndex > accounts.size()){
				throw std::exception();
			}
			accountIndex--;
			return;
		}
		catch(std::exception& e){
			accountIndex = -1;
			if(tryCount < 4){
				visualizeMainLogoOnly();
				std::cout<<"Choose Account by number. It's invalid number... choose between 1 to "<<accounts.size()<<std::endl;
				for(int i = 1; i <= accounts.size(); i++){
					std::cout<<i<<": "<<accounts[i-1].getAccountNumber()<<std::endl;
				}
				std::cout<<"Account number: ";
			}
			continue;
		}
	}
	throw InvalidAccountException();
}

void AtmMachine::askTask(){
	visualizeMainLogoOnly();
	std::cout<<"Choose the task by number"<<std::endl;
	std::cout<<"     1: See Balance"<<std::endl;
	std::cout<<"     2: Deposit"<<std::endl;
	std::cout<<"     3: Withdraw"<<std::endl;
	std::cout<<"     4: Choose Other Account"<<std::endl;
	std::cout<<"others: End service"<<std::endl;
	std::cout<<"Task number: ";
	int taskNumber = 0;
	try{
		getValidInteger(taskNumber);
	}
	catch(InvalidIntegerException& e){
		clearCardAndAccounts();
		visualizeMainLogoOnly();
		throw EndTaskException();
		return;
	}
	visualizeMainLogoOnly();
	switch (taskNumber){
		case 1:
			viewBalanceCallback();
			enterAnyKey("Press any key to do other task");
			break;
		
		case 2:
			depositCallback();
			break;
		case 3:
			withdrawCallback();
			break;
		
		case 4:
			askToChooseAccount();
			break;

		default:
			throw EndTaskException();
			return;
	}
}

void AtmMachine::viewBalanceCallback(){
	std::cout<<"Current balance of your account is "<<getIntMaxNum()<<"$$, "<<getBalance()<<"$"<<std::endl;
	std::cout<<"(1$$ = 2,147,483,647$)"<<std::endl;
}

int AtmMachine::getBalance(){
	return accounts.at(accountIndex).getBalance();
}

int AtmMachine::getIntMaxNum(){
	return accounts.at(accountIndex).getIntMaxNum();
}

void AtmMachine::depositCallback(){
	std::cout<<"How much do you want to deposit? Insert Money by number"<<std::endl;
	std::cout<<"Money to deposit: ";
	for(int i = 0; i < 5; i++){
		try{
			getValidInteger(insertedDollar);
			break;
		}
		catch(InvalidIntegerException& e){
			if(i == 4){
				clearCardAndAccounts();
				visualizeMainLogoOnly();
				throw TooManyInvalidInputException();
				return;
			}
			else{
				visualizeMainLogoOnly();
				std::cout<<"How much do you want to deposit? Insert Money by number"<<std::endl;
				std::cerr << e.what() << std::endl;
				std::cout<<"Money to deposit: ";
			}
		}
	}
	
	isDollarTaken = false;
	std::cout<<"You Insert "<<insertedDollar<<"$. Are you sure to deposit it? (Y/N) ";

	std::string doDeposit;
	getline(std::cin, doDeposit);
	if(doDeposit=="Y" || doDeposit=="y"){
		depositDollarToAccount();
		viewBalanceCallback();
		enterAnyKey("Press any key to do other task");
	}
	else{
		giveInsertedMoneyBack();
	}
	insertedDollar = 0;
}

void AtmMachine::depositDollarToAccount(){
	try{
		accounts.at(accountIndex).deposit(insertedDollar);
		std::cout<<"Deposit "<<insertedDollar<<"$ to Account "<<accounts.at(accountIndex).getAccountNumber()<<" complete!\n"<<std::endl;
	}
	catch(AccountException& e){
		std::cerr << e.what()<< std::endl;
	}
}

void AtmMachine::giveInsertedMoneyBack(){
	std::string returnStr = std::string("Return ") + std::to_string(insertedDollar) + std::string("$... enter any key to take it");
	enterAnyKey(returnStr.c_str());
	isDollarTaken = true;
}

void AtmMachine::withdrawCallback(){
	std::cout<<"How much will you withdraw? Give me the ammount by number"<<std::endl;
	std::cout<<"Money to withdraw: ";
	int desireDollar = 0;

	for(int i = 0; i < 5; i++){
		try{
			getValidInteger(desireDollar);
			break;
		}
		catch(InvalidIntegerException& e){
			desireDollar = 0;
			if(i == 4){
				clearCardAndAccounts();
				visualizeMainLogoOnly();
				throw TooManyInvalidInputException();
				return;
			}
			else{
				visualizeMainLogoOnly();
				std::cout<<"How much will you withdraw? Give me the ammount by number"<<std::endl;
				std::cerr << e.what() << std::endl;
				std::cout<<"Money to withdraw: ";
			}
		}
	}

	try{
		std::cout<<"Take "<<accounts.at(accountIndex).withdraw(desireDollar)<<"$... enter any key to take it"<<std::endl;
		std::string foo;
		getline(std::cin, foo);
	}
	catch(AccountException& e){
		std::cerr << e.what() <<std::endl;
	}
	viewBalanceCallback();
	enterAnyKey("Press any key to do other task");
	return;
}

void AtmMachine::getValidInteger(int& input){
	std::string temp;
	getline(std::cin, temp);
	try{
		size_t notIntIndex;
		double dinput = std::stod(temp, &notIntIndex);
		if(!temp.substr(notIntIndex).empty()||dinput - floor(dinput) != 0){
			throw InvalidIntegerException();
		}
		else{
			input = dinput;
			return;
		}
	}
	catch(std::invalid_argument& e){
		throw InvalidIntegerException();
		return;
	}
}

void AtmMachine::moveCursor(int x, int y){
	COORD pos;
	pos.X = 2*x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void AtmMachine::visualizeMainLogoOnly(){
	system("cls");
	moveCursor(0,0);
	std::cout<<"|*********************|"<<std::endl;
	std::cout<<"| JOONSEO ATM SERVICE |"<<std::endl;
	std::cout<<"|*********************|"<<std::endl;
	std::cout<<std::endl;
	if(isCardInserted){
		std::cout<<"Hello \""<<card.getUserName()<<"\"!";
		if(accountIndex >=0){
			std::cout<<" Current account is \""<<accounts.at(accountIndex).getAccountNumber()<<"\""<<std::endl;
		}
		else{
			std::cout<<std::endl;
		}
		std::cout<<std::endl;
	}
}

void AtmMachine::enterAnyKey(const char* str){
	std::cout<<str<<std::endl;
	std::string temp;
	getline(std::cin, temp);
}