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
	cardCompany = _cardCompany;
}

void Card::setUserName(std::string& _userName){
	userName = _userName;
}

std::string& Card::getCardCompany(){
	return cardCompany;
} 

std::string& Card::getUserName(){
	return userName;
}