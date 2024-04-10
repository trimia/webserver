#include "config.hpp"

config::config()
{
	std::cout << "config : Default Constructor Called" << std::endl;
}

config::~config()
{
	std::cout << "config : Destructor Called" << std::endl;
}

config::config(config const &obj)
{
	std::cout << "Copy Constructor Called" << std::endl;
	if (this != &obj)
		*this = obj;
}

config	&config::operator= (const config &obj)
{
	std::cout << "Copy Assignment Operator Called" << std::endl;
	if (this != &obj)
	{
		//	this->attributes = obj.attributes;
		//	...
	}
	return (*this);
}
