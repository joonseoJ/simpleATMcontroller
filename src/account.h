#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account{
	public:
		Account();
		~Account();

		void setAccountNumberAndBalance(std::string& _accountNumber, int dollar);
		void setAccountNumber(std::string& _accountNumber);
		void setBalance(int dollar);
		void clearAccountNumber();
		void clearAccountNumberAndBalance();

		int getBalance();
		std::string& getAccountNumber();
		void deposit(int dollar);
		int withdraw(int dollar);
	private:
		std::string accountNumber;
		int balance;
		
};

class AccountException : public std::exception{
	public:
		virtual const char* what(){}
};

class NegativeBalanceException : public AccountException{
	public:
		const char* what(){
			return "Balance should not be negative value";
		}
};

class NegativeDollarException : public AccountException{
	public:
		const char* what(){
			return "Dollar should not be negative value";
		}
};

#endif