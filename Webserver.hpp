#ifndef _Webserver_HPP_
#define _Webserver_HPP_

#include "include.h"
#include "Server.hpp"
#include "Client.hpp"

// ******************************************************** //
//                         CLASSES                         //
// ****************************************************** //
class Server;
class Client;
class	Webserver
{
	public	:
		Webserver ();
		Webserver (Webserver const &obj);
		~Webserver ();
		Webserver &operator= (const Webserver &obj);

    const std::vector<Server> &getListOfServer() const;

    void setListOfServer(const std::vector<Server> &listOfServer);

    const std::vector<Client> &getListOfClient() const;

    void setListOfClient(const std::vector<Client> &listOfClient);

    int getEpollFd() const;

    void setEpollFd(int epollFd);

private	:
        std::vector<Server>     _listOfServer;
        std::vector<Client>     _listOfClient;
        int                     _epoll_fd;

		//	DataType	attributes.
};

// ******************************************************** //
//                        FUNCTIONS                        //
// ****************************************************** //

#endif
