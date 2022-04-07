#include "account.h"

Account::Account(){
	balance_ = 0;
	intMaxNum_ = 0;
}

Account::~Account(){
	accountNumber_.clear();
}

void Account::setAccountNumberAndBalance(std::string& _accountNumber, int _balance){
	setAccountNumber(_accountNumber);
	setBalance(_balance);
}

void Account::setAccountNumber(std::string& _accountNumber){
	accountNumber_ = _accountNumber;
}

void Account::setBalance(int _balance){
	if(_balance >= 0){
		balance_ = _balance;
	}
	else{
		throw NegativeBalanceException();
	}
}

void Account::setIntMaxNum(int _intMaxNum){
	intMaxNum_ = _intMaxNum;
}

void Account::clearAccountNumberAndBalance(){
	clearAccountNumber();
	setBalance(0);
}

void Account::clearAccountNumber(){
	accountNumber_.clear();
}

int Account::getBalance(){
	return balance_;
}

int Account::getIntMaxNum(){
	return intMaxNum_;
}

std::string& Account::getAccountNumber(){
	return accountNumber_;
}

void Account::deposit(int dollar){
	if(dollar >= 0){
		if(balance_ + dollar >= balance_ ){
			balance_ += dollar;
		}
		else{
			intMaxNum_++;
			balance_ = dollar - (INT32_MAX - balance_);
		}
	}
	else{
		throw NegativeDollarException();
	}
}

int Account::withdraw(int dollar){
	if(dollar >= 0){
		if(balance_ >= dollar){
			balance_ -= dollar;
			return dollar;
		}
		else if(intMaxNum_ > 0){
			intMaxNum_--;
			balance_ = INT32_MAX - (dollar - balance_);
		}
		else{
			throw NegativeBalanceException();
		}
	}
	else{
		throw NegativeDollarException();
	}
}