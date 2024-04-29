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
 *  - create a socket per server, bind it and set it as non-blocking
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
    fcntl(server.getServerSock().getFdSock(),F_SETFL,O_NONBLOCK);
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
}

/*
 * run:
 * set al necessary for the select()
 * start the main loop:
 *      choose what to do about sock/fd and server/client
 *
 */
void run_select(){
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

bool Server::_initEpoll() {
    this->_epollFd = epoll_create1(EPOLL_CLOEXEC);
    if (this->_epollFd<0)
        return true;
    std::cout<<"epoll created"<<std::endl;
    return false;
}

bool Server::_addServerToEpoll(std::vector<Server> listOfServer) {

    for (Server &item: listOfServer){
        if(epoll_ctl(item._epollFd,EPOLL_CTL_ADD, item._server_socket.getFdSock(), &item._event)<1)
            return false;
        item._event.events=EPOLLIN;
        item._event.data.ptr=&item;
        item._type=SERVER_SOCK;

    }
    std::cout<<"all server sock added to epoll instance"<<std::endl;
    return true;
}

bool Server::_mainLoop() {
    int eventNumber;
    epoll_event events[MAX_EVENTS];
    do{
        eventNumber= epoll_wait(this->_epollFd,events,MAX_EVENTS,EPOLL_TIMEOUT);
        if(eventNumber>0)
            _handleEpollEvents(eventNumber,events);

    } while (eventNumber<=0);
    return false;
}

bool Server::_handleEpollEvents(int eventNumber, epoll_event (&events)[MAX_EVENTS]) {
    for (int i = 0; i < eventNumber; ++i)
    {
        Server	*ptr = static_cast<Server *>(events[i].data.ptr);
        if(ptr->_type==SERVER_SOCK){
            if(ptr->_server_socket.acceptConnection(ptr))
                return false;
        }
        else if(events[i].events && EPOLLIN | events[i].events && EPOLLOUT)
            _handleEpollin();
//            _handleConnection(events,eventNumber);
        else if ( events[i].events && EPOLLOUT)
                _handleEpollout();

    }
    return true;
}
/*
 * handleConnection:
 * check what to do with connection and
 * call read()? or receiveData() write() or sendData() -see the snippet code in the function-,request, response and parser
 * TODO study and complete _handleconnection understand how we want handle response request etc..
 */
bool Server::_handleConnection(epoll_event (&events)[MAX_EVENTS],int i) {

    int str_len;
    void *buf;
    str_len = read(events[i].data.fd, buf, BUFFER_SIZE);
    if (str_len == 0) // close request!
    {
        epoll_ctl(this->_epollFd, EPOLL_CTL_DEL, events[i].data.fd, nullptr);
        close(events[i].data.fd);
        //printf("closed client: %d \n", epoll_events[i].data.fd);
    }
    else
    {
        write(events[i].data.fd, buf, str_len);   // echo!
    }

//    client.peaksize = recv(client.connection_socket.sock_fd, buffer, MAX_HEADER_SIZE, MSG_PEEK);

    return false;
}

void Server::run_epoll(std::vector<Server> listOfServer) {

    this->_initEpoll();
    this->_addServerToEpoll(listOfServer);
    this->_mainLoop();

// understand if is necessary to allocate event
//    auto epoll_events = (struct epoll_event*) malloc(sizeof(struct epoll_event) * EPOLL_SIZE);
//    struct epoll_event event;
}

