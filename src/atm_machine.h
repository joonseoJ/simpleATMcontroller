#ifndef ATM_MACHINE_H
#define ATM_MACHINE_H

#include "card.h"
#include "account.h"
#include <cmath>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

class AtmMachine{
	public:
		AtmMachine();

		void clearCard();
		void clearAccounts();
		void clearCardAndAccounts();

		void askCardInformation();

		void askPinNumber();
		int getFourDigitPinNumber();
		bool isPinCorrect(int pin);
		
		void getEveryAccounts();
		void askToChooseAccount();
		void printEveryAccounts();

		void askTask();

		void viewBalanceCallback();
		int getBalance();
		int getIntMaxNum();

		void depositCallback();
		void askDepositDollar();
		void waitInsertingDollar(){}; // TODO: implement ATM hardware integration
		void depositDollarToAccount();
		void giveInsertedMoneyBack();

		void withdrawCallback();
		void askWithdrawDollar();
		void isWithdrawPossible();
		void giveMoney();

		void getValidInteger(int& input);

		void moveCursor(int x, int y);
		void visualizeMainLogoOnly();
		void enterAnyKey(const char* str);

	private:
		bool isCardInserted_, isDollarTaken_;
		int moneyToDeposit_, moneyToWithdraw_;
		Card card_;
		std::vector<Account> accounts_;
		int accountsNumber_;
		int accountIndex_;
		const int maxTryCount_;
		
};

#endif