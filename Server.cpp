#include "Server.hpp"

Server::Server()
{
    this->_autoindex="";

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
/*
 * getter and setter
 */

uint16_t Server::getPort() const {
    return _port;
}


const std::string &Server::getServerName() const {
    return _server_name;
}

const std::string &Server::getRoot() const {
    return _root;
}

unsigned long Server::getClientMaxBodySize() const {
    return _client_max_body_size;
}

const std::string &Server::getIndex() const {
    return _index;
}

bool Server::isAutoindex() const {
    return _autoindex;
}

const std::map<short, std::string> &Server::getErrorPages() const {
    return _error_pages;
}

const std::vector<Location> &Server::getLocations() const {
    return _locations;
}


int Server::getFd() const {
    return _fd;
}

Socket Server::getServerSock() const {
    return _server_socket;
}

void Server::setPort(uint16_t port) {
    _port = port;
}



void Server::setServerName(const std::string &serverName) {
    _server_name = serverName;
}

void Server::setRoot(const std::string &root) {
    _root = root;
}

void Server::setClientMaxBodySize(unsigned long clientMaxBodySize) {
    _client_max_body_size = clientMaxBodySize;
}

void Server::setIndex(const std::string &index) {
    _index = index;
}

void Server::setAutoindex(bool autoindex) {
    _autoindex = autoindex;
}

void Server::setErrorPages(const std::map<short, std::string> &errorPages) {
    _error_pages = errorPages;
}

void Server::setLocations(const std::vector<Location> &locations) {
    _locations = locations;
}


void Server::setFd(int fd) {
    _fd = fd;
}

Server::Server(uint16_t port, char *ip, const std::string &serverName, const std::string &root,
               const std::string &index, unsigned long clientMaxBodySize, bool autoindex,
               const std::map<short, std::string> &errorPages, const std::vector<Location> &locations) :
                                             _port(port), _ip(ip), _server_name(serverName), _root(root), _index(index),
                                             _client_max_body_size(clientMaxBodySize), _autoindex(autoindex),
                                             _error_pages(errorPages), _locations(locations){}

/*
 * function
 */
/*
 * setup server:
 *  - call server constructor
 *  - create a socket per server and bind it
 */
Server    setupServer(config conf)
{
    Server server(
            conf.getPort(),conf.getIp(),conf.getServerName(),
            conf.getRoot(),conf.getIndex(),conf.getClientMaxBodySize(),
            conf.isAutoindex(),conf.getErrorPages(),conf.getLocations());
    Socket sock(server);
    sock.setSocketOption(server);
    sock.bindSocket(server);
    fcntl(server.getServerSock(),F_SETFL,O_NONBLOCK);
    return server;
    //build server objetc with parser info
    //    Server server(infobyparser);
}

/*
 * setup:
 */
std::vector<Server>setup(std::vector<config> allConf)
{

/*
 * create client and all is necessary to run the server
 * maybe both client and server go on the same list ???
 * if end without error go on on main
 */
    std::vector<Server> listOfServer;
    listOfServer.reserve(allConf.size());
for (const auto &item: allConf){
        listOfServer.push_back(setupServer(item));
    }
    return listOfServer;



    std::cout << std::endl;
//    Logger::logMsg(LIGHTMAGENTA, CONSOLE_OUTPUT, "Initializing  Servers...");
//    _servers = servers;
    char buf[INET_ADDRSTRLEN];
    bool    serverDub;
    for (std::vector<Server>::iterator it = listOfServer.begin(); it != listOfServer.end(); ++it)
    {
        serverDub = false;
        for (std::vector<Server>::iterator it1 = listOfServer.begin(); it1 != it; ++it1)
        {
            if (it1->getHost() == it->getHost() && it1->getPort() == it->getPort())
            {
                it->setFd(it1->getFd());
                serverDub = true;
            }
        }
//        if (!serverDub)
//            it->setupServer();
//        Logger::logMsg(LIGHTMAGENTA, CONSOLE_OUTPUT, "Server Created: ServerName[%s] Host[%s] Port[%d]",it->getServerName().c_str(),inet_ntop(AF_INET, &it->getHost(), buf, INET_ADDRSTRLEN), it->getPort());
    }
}

/*
 * run:
 * set al necessary for the select()
 * start the main loop:
 *      choose what to do about sock/fd and server/client
 *
 */
void run(){
    fd_set  recv_set_cpy;
    fd_set  write_set_cpy;
    fd_set  _recv_fd_pool;
    fd_set  _write_fd_pool;
    int     select_ret;


    //start main loop
//    _biggest_fd = 0;
//    initializeSets();
//    struct timeval timer;
//    while (true)
//    {
//        timer.tv_sec = 1;
//        timer.tv_usec = 0;
//        recv_set_cpy = _recv_fd_pool;
//        write_set_cpy = _write_fd_pool;
//
//        if ( (select_ret = select(_biggest_fd + 1, &recv_set_cpy, &write_set_cpy, NULL, &timer)) < 0 )
//        {
////            Logger::logMsg(RED, CONSOLE_OUTPUT, "webserv: select error %s   Closing ....", strerror(errno));
//            exit(1);
//            continue ;
//        }
//        for (int i = 0; i <= _biggest_fd; ++i)
//        {
//            if (FD_ISSET(i, &recv_set_cpy) && _servers_map.count(i)) {
//                acceptNewConnection(_servers_map.find(i)->second);
//            }
//            else if (FD_ISSET(i, &recv_set_cpy) && _clients_map.count(i)) {
//                readRequest(i, _clients_map[i]);
//            }
//            else if (FD_ISSET(i, &write_set_cpy) && _clients_map.count(i))
//            {
//                int cgi_state = _clients_map[i].response.getCgiState(); // 0->NoCGI 1->CGI write/read to/from script 2-CGI read/write done
//                if (cgi_state == 1 && FD_ISSET(_clients_map[i].response._cgi_obj.pipe_in[1], &write_set_cpy)) {
//                    sendCgiBody(_clients_map[i], _clients_map[i].response._cgi_obj);
//                }
//                else if (cgi_state == 1 && FD_ISSET(_clients_map[i].response._cgi_obj.pipe_out[0], &recv_set_cpy)) {
//                    readCgiResponse(_clients_map[i], _clients_map[i].response._cgi_obj);
//                }
//                else if ((cgi_state == 0 || cgi_state == 2)  && FD_ISSET(i, &write_set_cpy)) {
//                    sendResponse(i, _clients_map[i]);
//                }
//            }
//        }
//        checkTimeout();
//    }


}