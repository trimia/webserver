#include "Server.hpp"

Server::Server()
{
	std::cout << "Server : Default Constructor Called" << std::endl;
}

Server::~Server()
{
	std::cout << "Server : Destructor Called" << std::endl;
}

Server::Server(Server const &obj)
{
	std::cout << "Copy Constructor Called" << std::endl;
	if (this != &obj)
		*this = obj;
}

Server	&Server::operator= (const Server &obj)
{
	std::cout << "Copy Assignment Operator Called" << std::endl;
	if (this != &obj)
	{
		//	this->attributes = obj.attributes;
		//	...
	}
	return (*this);
}
