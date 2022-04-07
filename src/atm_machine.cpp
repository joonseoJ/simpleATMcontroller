#include "atm_machine.h"
#include "atm_exception.h"
#include <iostream>
#include <limits>

AtmMachine::AtmMachine():
	isCardInserted_(false),
	isDollarTaken_(true),
	moneyToDeposit_(0),
	moneyToWithdraw_(0),
	accountIndex_(-1),
	maxTryCount_(5),
	accountsNumber_(5)
{
	card_ = Card();
}

void AtmMachine::clearCard(){
	card_.clearCompanyAndUserName();
	isCardInserted_ = false;
}

void AtmMachine::clearAccounts(){
	accounts_.clear();
	accountIndex_ = -1;
}

void AtmMachine::clearCardAndAccounts(){
	clearCard();
	clearAccounts();
}

void AtmMachine::askCardInformation(){
	visualizeMainLogoOnly();

	std::string cardCompany, userName;
	std::cout<<"What's your card company and user name?"<<std::endl;
	std::cout<<"Card Company: ";
	getline(std::cin, cardCompany);
	std::cout<<"User Name: ";
	getline(std::cin, userName);
	try{
		card_.setCompanyAndUserName(cardCompany, userName);
		isCardInserted_ = true;
	}
	catch(CardException& e){
		std::cerr<< e.what()<< std::endl;
		throw NoCardException();
	}
	return;
}

void AtmMachine::askPinNumber(){
		visualizeMainLogoOnly();
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
	if(isCardInserted_ && pin >= 0 && pin < 10000){
		// TODO: implement bank api for pin correction
		return true;
	}
	else{
		return false;
	}
}

void AtmMachine::getEveryAccounts(){
	// TODO: implement bank api for get accounts
	accounts_.clear();
	std::vector<int> accountDisplayCounts = {3,6,2,3};
	Account tempAccount;
	for(int i = 1; i <= accountsNumber_; i++){
		std::string accountCandidate;
		for(int j : accountDisplayCounts){
			for(int k = 0; k < j; k++){
				accountCandidate += std::to_string(i);
			}
			accountCandidate.push_back('-');
		}
		accountCandidate.pop_back();
		tempAccount.setAccountNumberAndBalance(accountCandidate, 0);
		accounts_.push_back(tempAccount);
	}
}

void AtmMachine::askToChooseAccount(){
	if(!isCardInserted_){
		visualizeMainLogoOnly();
		throw NoCardException();
		return;
	}
	if(accounts_.empty()){
		visualizeMainLogoOnly();
		throw NoAccountException();
		return;
	}

		visualizeMainLogoOnly();
	for(int tryCount = 0; tryCount < 5; tryCount++){
		try{
			if(inputIndex <= 0 || inputIndex > accounts_.size()){
			}
			else{
				accountIndex_ = inputIndex - 1;
				return;
			}
				}
				std::cout<<"Account number: ";
			}
			continue;
		}
	}
	throw InvalidAccountException();
}

void AtmMachine::printEveryAccounts(){
	for(int i = 1; i <= accounts_.size(); i++){
		std::cout<<i<<": "<<accounts_[i-1].getAccountNumber()<<std::endl;
	}
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
			visualizeMainLogoOnly()
;			viewBalanceCallback();
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
			visualizeMainLogoOnly();
			throw EndTaskException();
			return;
	}
}

void AtmMachine::viewBalanceCallback(){
	std::cout<<"Current balance of your account is "<<getIntMaxNum()<<"$$, "<<getBalance()<<"$"<<std::endl;
	std::cout<<"(1$$ = 2,147,483,647$)"<<std::endl;
}

int AtmMachine::getBalance(){
	return accounts_.at(accountIndex_).getBalance();
}

int AtmMachine::getIntMaxNum(){
	return accounts_.at(accountIndex_).getIntMaxNum();
}

void AtmMachine::depositCallback(){
	std::cout<<"How much do you want to deposit? Insert Money by number"<<std::endl;
	std::cout<<"Money to deposit: ";
	for(int i = 0; i < 5; i++){
		try{
			getValidInteger(insertedDollar);
			break;
		}
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
	
	isDollarTaken_ = false;
	std::cout<<"You Insert "<<moneyToDeposit_<<"$. Are you sure to deposit it? (Y/N) ";

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
	moneyToDeposit_ = 0;
}
		visualizeMainLogoOnly();
}

void AtmMachine::depositDollarToAccount(){
	try{
		accounts_.at(accountIndex_).deposit(moneyToDeposit_);
		std::cout<<"Deposit "<<moneyToDeposit_<<"$ to Account "<<accounts_.at(accountIndex_).getAccountNumber()<<" complete!\n"<<std::endl;
	}
	catch(AccountException& e){
		std::cerr << e.what()<< std::endl;
	}
}

void AtmMachine::giveInsertedMoneyBack(){
	std::string returnStr = std::string("Return ") + std::to_string(moneyToDeposit_) + std::string("$... enter any key to take it");
	enterAnyKey(returnStr.c_str());
	isDollarTaken_ = true;
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
	moneyToWithdraw_ = 0;

		visualizeMainLogoOnly();
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
	if(isCardInserted_){
		std::cout<<"Hello \""<<card_.getUserName()<<"\"!";
		if(accountIndex_ >=0){
			std::cout<<" Current account is \""<<accounts_.at(accountIndex_).getAccountNumber()<<"\""<<std::endl;
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