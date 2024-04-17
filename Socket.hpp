#ifndef _Socket_HPP_
#define _Socket_HPP_

#include "include.h"
#include "Response.hpp"
#include "Request.hpp"

// ******************************************************** //
//                         CLASSES                         //
// ****************************************************** //
class Response;
class Request;
class Server;
class	Socket
{
	public	:
		Socket ();
        Socket(Server server);
		Socket (Socket const &obj);
		~Socket ();
		Socket &operator= (const Socket &obj);
        //maybe int is better because of bind listen and accept return an int 0 or errno
        //server side
        //think about pass sokcet to function or the object server;
        bool bindSocket(Server server); //maybe the port is not necessary -> getport
        bool listenOnSocket(SOCKET serverSocket);
        bool acceptConnection(SOCKET serverSocket);
        //client side
        bool connectSocket(SOCKET clientSocket, uint16_t port);
        int sendData(SOCKET connectedSocket, Response msg);
        int receiveData(SOCKET acceptedSocket,Request httpRequest);

	private	:
        Server          *_server;
        sockaddr_in     _service;

    //	DataType	attributes.
};

// ******************************************************** //
//                        FUNCTIONS                        //
// ****************************************************** //

#endif
