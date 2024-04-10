#include "Socket.hpp"

Socket::Socket()
{
    SOCKET serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(serverSocket==INVALID_SOCKET)
    {
        std::cout<<"error in creating socket"<<GETSOCKETERRNO()<<std::endl;
        exit(0);
    }
    else
	    std::cout << "Socket : Default Constructor Called" << std::endl;
}

bool Socket::bindSocket(SOCKET serversocket,uint16_t port) {
    sockaddr_in service;
    service.sin_family=AF_INET;
//    InetPton() is necesary? find something you can use
    service.sin_port= htons(port);
    if(bind(serversocket,(sockaddr*)&service, sizeof(service)) == SOCKET_ERROR)
    {
        std::cout<<"bind failed"<<GETSOCKETERRNO()<<std::endl;
        return (false);
    }
    else{

        return true;
    }
}

bool Socket::listenOnSocket(SOCKET serversocket) {
    //choose how much connection ????
    if(listen(serversocket,MAX_N_CONNECTION))
    {
        std::cout<<"error on listen"<<GETSOCKETERRNO()<<std::endl;
        return false;
    }else{
        std::cout<<"listen is ok waiting for connection"<<std::endl;
        return true;
    }
}

bool Socket::acceptConnection(SOCKET serversocket) {
    SOCKET acceptSocket;
    acceptSocket= accept(serversocket,NULL,NULL);
    if(acceptSocket==INVALID_SOCKET)
    {
        std::cout<<"accepted failed"<<GETSOCKETERRNO()<<std::endl;
        return false;
    }
    return true;
}

Socket::~Socket()
{
	std::cout << "Socket : Destructor Called" << std::endl;
}

Socket::Socket(Socket const &obj)
{
	std::cout << "Copy Constructor Called" << std::endl;
	if (this != &obj)
		*this = obj;
}

Socket	&Socket::operator= (const Socket &obj)
{
	std::cout << "Copy Assignment Operator Called" << std::endl;
	if (this != &obj)
	{
		//	this->attributes = obj.attributes;
		//	...
	}
	return (*this);
}
