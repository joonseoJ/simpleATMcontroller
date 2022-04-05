#ifndef ATM_MACHINE_H
#define ATM_MACHINE_H

#include "Card.h"
#include "Account.h"
#include <windows.h>
#include <conio.h>

class AtmMachine{
	public:
		AtmMachine();

		void clearCard();
		void clearAccounts();
		void clearCardAndAccounts();

		void askCardInformation();
		void cardInsertedCallback();
		void askPinNumber();
		bool isPinCorrect(int pin);
		
		void getEveryAccounts();
		void askToChooseAccount();

		void askTask();

		void viewBalanceCallback();
		int getBalance();

		void depositCallback();
		void waitInsertingDollar(){}; // TODO: implement ATM hardware integration
		void depositDollarToAccount();
		void giveInsertedMoneyBack();

		void withdrawCallback();
		void isWithdrawPossible();
		void giveMoney();

		void getValidInteger(int& input);

		void moveCursor(int x, int y);
		void visualizeMainLogoOnly();
		void enterAnyKey(const char* str);

	private:
		bool isCardInserted, isDollarTaken;
		int insertedDollar;
		Card card;
		std::vector<Account> accounts;
		int accountIndex;
		
};

#endif