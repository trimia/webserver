#include "Socket.hpp"
Socket::Socket() {
    std::cout << "Socket : Default Constructor Called" << std::endl;

}
Socket::Socket(Server server)
{

    server._server_socket._fd_sock = INVALID_SOCKET;
    server._server_socket._fd_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(server._server_socket._fd_sock==INVALID_SOCKET)
    {
        std::cout<<"error in creating socket"<<GETSOCKETERRNO()<<std::endl;
        exit(0);
    }else
        std::cout<<"socket successfully created"<<std::endl;
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
        this->_fd_sock=obj._fd_sock;
        this->_service=obj._service;


        //	this->attributes = obj.attributes;
        //	...
    }
    return (*this);
}

/*
 * setsocketoption:
 * choose what option socket hav to do: keepalive etc... see the link in TODO for differnt option
 */
bool Socket::setSocketOption(Server server) {
    int optval = 1;
    //understand if the cast to char is necessary!!
    if (setsockopt(server._server_socket._fd_sock, SOL_SOCKET, SO_REUSEADDR, (char *) &optval, sizeof(optval)) ==
        SOCKET_ERROR) {
        std::cout << "cannot set socket option" << GETSOCKETERRNO() << std::endl;
        return false;
    } else
        return true;
}

int Socket::getFdSock() const {
    return _fd_sock;
}
//void createSocket(Server server)
//{
//
//    server._server_socket = INVALID_SOCKET;
//    server._server_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
//    if(server._server_socket==INVALID_SOCKET)
//    {
//        std::cout<<"error in creating socket"<<GETSOCKETERRNO()<<std::endl;
//        exit(0);
//    }else
//        std::cout<<"socket successfully created"<<std::endl;
//}
/*
 * probably we have to adapt the variable of the function to pass server and sockaddr_in
 * if _p== "localhost" fix it with 127.0.0.1
 */
bool Socket::bindSocket(Server server) {
//    sockaddr_in service;
    server._server_socket->_service.sin_family=AF_INET;
    //inet_addr or htonl
    server._server_socket->_service.sin_addr.s_addr= inet_addr(server._ip);
    server._server_socket->_service.sin_port= htons(server._port);
    if((int)bind(server._server_socket._fd_sock,(sockaddr*)&server._server_socket->_service, sizeof(server._server_socket->_service)) == SOCKET_ERROR)
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

bool Socket::acceptConnection(Server *server, int epollFd, Webserver *webserver) {
//    SOCKET acceptSocket;
//    acceptSocket= accept(server._fd,server._server_socket._service, sizeof(server._server_socket._service));
//    if(acceptSocket==INVALID_SOCKET)
    Client client;

    if((client._fd=accept(server->_fd,server->_server_socket._service, sizeof(server->_server_socket._service)))==INVALID_SOCKET)
    {
        std::cout<<"accepted failed"<<GETSOCKETERRNO()<<std::endl;
        return false;
    }
    client._event.events=EPOLLIN | EPOLLOUT;
    client._event.data.ptr=&client;
    client._type=CLIENT_SCOK;
    webserver->addClientToList(client);

//    server->_event.events=EPOLLIN | EPOLLOUT;
//    server->_event.data.ptr=&server;
//    server->_type=CLIENT_SCOK;
//    if(epoll_ctl(epollFd,EPOLL_CTL_ADD, server->_server_socket.getFdSock(), &server->_event)<1)
    if(epoll_ctl(epollFd,EPOLL_CTL_ADD, client._fd, &client._event)<1)
            return false;
    std::cout<<"client sock added to epoll instance"<<std::endl;
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

int Socket::sendData(SOCKET connectedSocket, Response msg) {
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
        std::cout<<"receive data, "<<byteCount<<" byte"<<std::endl;
        httpRequest.parseRequest(rcv_buffer,httpRequest);
        return byteCount;
    }
}

