#ifndef _Server_HPP_
#define _Server_HPP_

#include "include.h"
#include "Location.hpp"
#include "Socket.hpp"
#include "config.hpp"

// ******************************************************** //
//                         CLASSES                         //
// ****************************************************** //
class Socket;
class	Server
{
	public	:
        Server();
		Server(Server const &obj);


    Server(uint16_t port, char *ip, const std::string &serverName, const std::string &root, const std::string &index,
           unsigned long clientMaxBodySize, bool autoindex, const std::map<short, std::string> &errorPages,
           const std::vector<Location> &locations);

    ~Server();
		Server  &operator= (const Server &obj);
        void    run_select();
        void    run_epoll(std::vector<Server> listOfServer);
        Server    setupServer(config conf);
        std::vector<Server> setup(std::vector<config> allConf);

    uint16_t getPort() const;

    in_addr_t getHost() const;

    const std::string &getServerName() const;

    const std::string &getRoot() const;

    unsigned long getClientMaxBodySize() const;

    const std::string &getIndex() const;

    bool isAutoindex() const;

    const std::map<short, std::string> &getErrorPages() const;

    const std::vector<Location> &getLocations() const;

    const sockaddr_in &getServerAddress() const;

    int getFd() const;

    void setPort(uint16_t port);

    void setHost(in_addr_t host);

    void setServerName(const std::string &serverName);

    void setRoot(const std::string &root);

    void setClientMaxBodySize(unsigned long clientMaxBodySize);

    void setIndex(const std::string &index);

    void setAutoindex(bool autoindex);

    void setErrorPages(const std::map<short, std::string> &errorPages);

    void setLocations(const std::vector<Location> &locations);

    void setServerAddress(const sockaddr_in &serverAddress);

    void setFd(int fd);

    Socket getServerSock() const;


private	:
        friend class Socket;
//        std::vector<Server>             _listOfServer;
        uint16_t						_port;
        char *                          _ip;
        std::string						_server_name;
        std::string						_root;
        std::string						_index;
        unsigned long					_client_max_body_size;
        bool							_autoindex;
        std::map<short, std::string>	_error_pages;
        std::vector<Location> 			_locations;
//        in_addr_t						_host;
//        struct sockaddr_in 				_server_address;
        //understand if _socket is necessary or _fd is good maybe have to change socket function return
        Socket                          _server_socket;
        int     						_fd;
        int                             _epollFd;
        int                             _type;
        epoll_event                     _event;
        bool _initEpoll();
        bool _addServerToEpoll(std::vector<Server> listofserver);
        bool _mainLoop();
        bool _handleEpollEvents(int eventNumber, epoll_event (&events)[MAX_EVENTS]);
        bool _handleConnection(epoll_event (&events)[MAX_EVENTS], int i);
		//	DataType	attributes.
};

// ******************************************************** //
//                        FUNCTIONS                        //
// ****************************************************** //

#endif
