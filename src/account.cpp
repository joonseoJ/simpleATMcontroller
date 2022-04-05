#include "account.h"

Account::Account(){
	balance = 0;
}

Account::~Account(){
	accountNumber.clear();
}

void Account::setAccountNumberAndBalance(std::string& _accountNumber, int dollar){
	setAccountNumber(_accountNumber);
	setBalance(dollar);
}

void Account::setAccountNumber(std::string& _accountNumber){
	accountNumber = _accountNumber;
}

void Account::setBalance(int dollar){
	if(dollar >= 0){
		balance = dollar;
	}
	else{
		throw NegativeBalanceException();
	}
}

void Account::clearAccountNumber(){
	accountNumber.clear();
}

void Account::clearAccountNumberAndBalance(){
	clearAccountNumber();
	setBalance(0);
}

int Account::getBalance(){
	return balance;
}

std::string& Account::getAccountNumber(){
	return accountNumber;
}

void Account::deposit(int dollar){
	if(dollar >= 0){
		balance += dollar;
	}
	else{
		throw NegativeDollarException();
	}
}

int Account::withdraw(int dollar){
	if(dollar >= 0){
		if(balance >= dollar){
			balance -= dollar;
			return dollar;
		}
		else{
			throw NegativeBalanceException();
		}
	}
	else{
		throw NegativeDollarException();
	}
}