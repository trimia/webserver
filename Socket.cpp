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
//probably we have to adapt the variable of the function to pass server and sockaddr_in
bool Socket::bindSocket(SOCKET serverSocket,uint16_t port) {
    sockaddr_in service;
    service.sin_family=AF_INET;
//    InetPton() is necesary? find something you can use --> inet_addr() maybe this in servre function
    service.sin_port= htons(port);
    if(bind(serverSocket,(sockaddr*)&service, sizeof(service)) == SOCKET_ERROR)
    {
        std::cout<<"bind failed"<<GETSOCKETERRNO()<<std::endl;
        return (false);
    }
    else{

        return true;
    }
}

bool Socket::listenOnSocket(SOCKET serverSocket) {
    //choose how much connection ????
    if(listen(serverSocket,MAX_N_CONNECTION))
    {
        std::cout<<"error on listen"<<GETSOCKETERRNO()<<std::endl;
        return false;
    }else{
        std::cout<<"listen is ok waiting for connection"<<std::endl;
        return true;
    }
}

bool Socket::acceptConnection(SOCKET serverSocket) {
    SOCKET acceptSocket;
    acceptSocket= accept(serverSocket,NULL,NULL);
    if(acceptSocket==INVALID_SOCKET)
    {
        std::cout<<"accepted failed"<<GETSOCKETERRNO()<<std::endl;
        return false;
    }
    return true;
}

bool Socket::connectSocket(SOCKET clientSocket, uint16_t port) {
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    inet_pton(AF_INET,"127.0.0.1",&clientService.sin_addr.s_addr);
//    InetPton() is necesary? find something you can use
    clientService.sin_port = htons(port);
    if(connect(clientSocket,(sockaddr*)&clientService, sizeof(clientService))==SOCKET_ERROR)
    {
        std::cout<<"connection to socket failed"<<GETSOCKETERRNO()<<std::endl;
        return false;
    }else
    {
        std::cout<<"client connect can start sending and receiving data"<<std::endl;
        return true;
    }
}

int Socket::sendData(SOCKET connectedSocket,Response msg) {
    int byteCount = (int)send(connectedSocket,(char*)&msg.getContent() , sizeof(msg), 0);
    if(byteCount==SOCKET_ERROR)
    {
        std::cout<<"send error"<<GETSOCKETERRNO()<<std::endl;
        return SOCKET_ERROR;
    }else
    {
        std::cout<<"send "<<byteCount<<" byte"<<std::endl;
        return byteCount;
    }
}

int Socket::receiveData(SOCKET acceptedSocket, Request httpRequest) {
    char rcv_buffer[RCV_BUF_SIZE];
    memset(rcv_buffer,0,RCV_BUF_SIZE);
    int byteCount=(int)recv(acceptedSocket,rcv_buffer, RCV_BUF_SIZE,0);
    if(byteCount<=0)
    {
        std::cout<<"receive data error"<<GETSOCKETERRNO()<<std::endl;
        return SOCKET_ERROR;
    }else
    {
        std::cout<<"receive data, "<<byteCount<<"byte"<<std::endl;
        httpRequest.str.append(rcv_buffer,RCV_BUF_SIZE);

        return byteCount;
    }
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
