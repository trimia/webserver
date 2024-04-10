#include "Location.hpp"

Location::Location()
{
	std::cout << "Location : Default Constructor Called" << std::endl;
}

Location::~Location()
{
	std::cout << "Location : Destructor Called" << std::endl;
}

Location::Location(Location const &obj)
{
	std::cout << "Copy Constructor Called" << std::endl;
	if (this != &obj)
		*this = obj;
}

Location	&Location::operator= (const Location &obj)
{
	std::cout << "Copy Assignment Operator Called" << std::endl;
	if (this != &obj)
	{
		//	this->attributes = obj.attributes;
		//	...
	}
	return (*this);
}
