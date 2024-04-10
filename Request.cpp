#include "Request.hpp"

Request::Request()
{
	std::cout << "Request : Default Constructor Called" << std::endl;
}

Request::~Request()
{
	std::cout << "Request : Destructor Called" << std::endl;
}

Request::Request(Request const &obj)
{
	std::cout << "Copy Constructor Called" << std::endl;
	if (this != &obj)
		*this = obj;
}

Request	&Request::operator= (const Request &obj)
{
	std::cout << "Copy Assignment Operator Called" << std::endl;
	if (this != &obj)
	{
		//	this->attributes = obj.attributes;
		//	...
	}
	return (*this);
}
