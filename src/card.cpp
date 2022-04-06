#include "card.h"

Card::Card(){

}

void Card::clearCompanyAndUserName(){
	cardCompany = "";
	userName = "";
}

void Card::setCompanyAndUserName(std::string& _cardCompany, std::string& _userName){
	setCardCompany(_cardCompany);
	setUserName(_userName);
}

void Card::setCardCompany(std::string& _cardCompany){
	if(_cardCompany.empty()){
		throw EmptyStringException();
		return;
	}
	else{
		cardCompany = _cardCompany;
		return;
	}
}

void Card::setUserName(std::string& _userName){
	if(_userName.empty()){
		throw EmptyStringException();
		return;
	}
	else{
		userName = _userName;
		return;
	}
}

std::string& Card::getCardCompany(){
	return cardCompany;
} 

std::string& Card::getUserName(){
	return userName;
}