#include <iostream>
#include "atm_machine.h"
#include "atm_exception.h"

int main(){
	AtmMachine atmMachine;
	while (true)
	{
		atmMachine.clearCardAndAccounts();

		try{
			atmMachine.askCardInformation();
		}
		catch(ReinitializeException& e){
			std::cerr << e.what() <<std::endl;
			atmMachine.enterAnyKey("Enter any key to reinitialize");
			continue;
		}

		try{
			atmMachine.askPinNumber();
		}
		catch(InvalidPinException& e){
			std::cerr << e.what() << std::endl;
			break;
		}
		catch(TerminalizeException& e){
			break;
		}

		atmMachine.getEveryAccounts();

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
