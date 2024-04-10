#include "Parser.hpp"

Parser::Parser()
{
	std::cout << "Parser : Default Constructor Called" << std::endl;
}

Parser::~Parser()
{
	std::cout << "Parser : Destructor Called" << std::endl;
}

Parser::Parser(Parser const &obj)
{
	std::cout << "Copy Constructor Called" << std::endl;
	if (this != &obj)
		*this = obj;
}

Parser	&Parser::operator= (const Parser &obj)
{
	std::cout << "Copy Assignment Operator Called" << std::endl;
	if (this != &obj)
	{
		//	this->attributes = obj.attributes;
		//	...
	}
	return (*this);
}
