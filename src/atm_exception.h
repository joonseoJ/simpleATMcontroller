#ifndef ATM_EXCEPTION_H
#define ATM_EXCEPTION_H

#include <exception>

class AtmException : public std::exception{
	
	public:
		virtual const char * what(){};
	
};

class ReinitializeException : public AtmException{
	public:
		virtual const char* what(){}
		const char* errorMsg(){
			return "Reinitialize ATM Machine";
		}
};

class TerminalizeException : public AtmException{
	public:
		virtual const char* what(){};
};

class InvalidPinException : public TerminalizeException{
	public:
		const char* what(){
			return "You enter too many wrong pin numbers... End for security";
		}
};

class InvalidAccountException : public TerminalizeException{
	public:
		const char* what(){
			return "You enter too many invalid account numbers... End for security";
		}
};

class TooManyInvalidInputException : public TerminalizeException{
	public:
		const char* what(){
			return "You enter too many invalid inputs... End for security";
		}
};

class EndTaskException : public TerminalizeException{
	public:
		const char* what(){
			return "End Service... Thank you for using JOONSEO ATM";
		}
};

class NoCardException : public ReinitializeException{
	public:
		const char* what(){
			return "No Card detected... please insert card first";
		}
};

class NoAccountException : public TerminalizeException{
	public:
		const char* what(){
			return "No accounts detected for this card... End Service";
		}
};

class InvalidIntegerException : public AtmException{
	public:
		const char* what(){
			return "Please enter number";
		}
};



#endif