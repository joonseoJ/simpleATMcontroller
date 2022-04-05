#include <iostream>
#include <conio.h>
#include "atm_machine.h"
#include "atm_exception.h"

int main(){
	AtmMachine atmMachine;
	while (true)
	{
		atmMachine.clearCardAndAccounts();
		atmMachine.visualizeMainLogoOnly();
		std::cout<<"Hello! This is JOONSEO ATM Service"<<std::endl;

		try{
			atmMachine.askCardInformation();
		}
		catch(ReinitializeException& e){
			std::cerr << e.what() <<std::endl;
			atmMachine.enterAnyKey("Enter any key to reinitialize");
			continue;
		}

		atmMachine.visualizeMainLogoOnly();

		try{
			atmMachine.askPinNumber();
		}
		catch(InvalidPinException& e){
			std::cerr << e.what() << std::endl;
			break;
		}

		atmMachine.getEveryAccounts();
		atmMachine.visualizeMainLogoOnly();
		try{
			atmMachine.askToChooseAccount();
		}
		catch(ReinitializeException& e){
			std::cerr << e.what() << std::endl;
			atmMachine.enterAnyKey("Enter any key to reinitialize");
			continue;
		}
		catch(TerminalizeException& e){
			std::cerr << e.what() << std::endl;
			break;
		}

		bool isEnd = false;
		while(true){
			try{
				atmMachine.askTask();
			}
			catch(TerminalizeException& e){
				std::cerr << e.what() << '\n';
				isEnd = true;
				break;
			}
			catch(ReinitializeException& e){
				std::cerr << e.what() << std::endl;
				atmMachine.enterAnyKey("Enter any key to reinitialize");
				break;
			}
		}
		if(isEnd) break;
	}
	std::cout<<"Enter 'exit' to exit program"<<std::endl;
	std::string exit;
	do{
		exit.clear();
		std::cin>>exit;
	}while(exit != "exit");
	return 0;
}