#include "card.h"

Card::Card(){

}

void Card::clearCompanyAndUserName(){
	cardCompany_ = "";
	userName_ = "";
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
		cardCompany_ = _cardCompany;
		return;
	}
}

void Card::setUserName(std::string& _userName){
	if(_userName.empty()){
		throw EmptyStringException();
		return;
	}
	else{
		userName_ = _userName;
		return;
	}
}

std::string& Card::getCardCompany(){
	return cardCompany_;
} 

std::string& Card::getUserName(){
	return userName_;
}