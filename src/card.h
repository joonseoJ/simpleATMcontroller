#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

class Card{
	public:
		Card();

		~Card(){
			cardCompany.clear();
			userName.clear();
		}

		void clearCompanyAndUserName();

		void setCompanyAndUserName(std::string& _cardCompany, std::string& _userName);

		void setCardCompany(std::string& _cardCompany);
		void setUserName(std::string& _userName);

		std::string& getCardCompany();
		std::string& getUserName();
	private:
		std::string cardCompany_, userName_;
};

class CardException : public std::exception{
	public:
		virtual const char* what(){}
};

class EmptyStringException : public CardException{
	public:
		const char* what(){
			return "Input string is empty";
		}
};

#endif 