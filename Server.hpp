#ifndef _Server_HPP_
#define _Server_HPP_

#include "include.h"
#include "Location.hpp"
#include "Socket.hpp"

// ******************************************************** //
//                         CLASSES                         //
// ****************************************************** //

class	Server
{
	public	:
		Server();
		Server(Server const &obj);

    Server(uint16_t port, in_addr_t host, const std::string &serverName, const std::string &root,
           unsigned long clientMaxBodySize, const std::string &index, bool autoindex,
           const std::map<short, std::string> &errorPages, const std::vector<Location> &locations,
           const sockaddr_in &serverAddress, int fd);


    ~Server();
		Server  &operator= (const Server &obj);
        void    run();
        void    setup(std::vector<Server> listOfServer);
        void    setupServer();

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

private	:
//        std::vector<Server>             _listOfServer;
        uint16_t						_port;
        in_addr_t						_host;
        std::string						_server_name;
        std::string						_root;
        unsigned long					_client_max_body_size;
        std::string						_index;
        bool							_autoindex;
        std::map<short, std::string>	_error_pages;
        std::vector<Location> 			_locations;
        struct sockaddr_in 				_server_address;
        //understand if _socket is necessary or _fd is good maybe have to change socket function return
        Socket                          _server_sock;
        int     						_fd;
		//	DataType	attributes.
};

// ******************************************************** //
//                        FUNCTIONS                        //
// ****************************************************** //

#endif
