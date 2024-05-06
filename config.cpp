#include "config.hpp"

config::config()
{
	std::cout << "config : Default Constructor Called" << std::endl;
}

config::config(uint16_t port, char *ip, const std::string &serverName, const std::string &root,
               const std::string &index, unsigned long clientMaxBodySize, bool autoindex,
               const std::map<short, std::string> &errorPages, const std::vector<Location> &locations) :
               _port(port),_ip(ip),_server_name(serverName),_root(root),_index(index),
               _client_max_body_size(clientMaxBodySize),_autoindex(autoindex),
               _error_pages(errorPages){}
//               ,_locations(locations) {}

config::~config()
{
	std::cout << "config : Destructor Called" << std::endl;
}

config::config(config const &obj)
{
	std::cout << "Copy Constructor Called" << std::endl;
	if (this != &obj)
		*this = obj;
}

config	&config::operator= (const config &obj)
{
	std::cout << "Copy Assignment Operator Called" << std::endl;
	if (this != &obj)
	{
		//	this->attributes = obj.attributes;
		//	...
	}
	return (*this);
}

uint16_t config::getPort() const {
    return _port;
}

void config::setPort(uint16_t port) {
    _port = port;
}

char *config::getIp() const {
    return _ip;
}

void config::setIp(char *ip) {
    _ip = ip;
}

const std::string &config::getServerName() const {
    return _server_name;
}

void config::setServerName(const std::string &serverName) {
    _server_name = serverName;
}

const std::string &config::getRoot() const {
    return _root;
}

void config::setRoot(const std::string &root) {
    _root = root;
}

const std::string &config::getIndex() const {
    return _index;
}

void config::setIndex(const std::string &index) {
    _index = index;
}

unsigned long config::getClientMaxBodySize() const {
    return _client_max_body_size;
}

void config::setClientMaxBodySize(unsigned long clientMaxBodySize) {
    _client_max_body_size = clientMaxBodySize;
}

bool config::isAutoindex() const {
    return _autoindex;
}

void config::setAutoindex(bool autoindex) {
    _autoindex = autoindex;
}

const std::map<short, std::string> &config::getErrorPages() const {
    return _error_pages;
}

void config::setErrorPages(const std::map<short, std::string> &errorPages) {
    _error_pages = errorPages;
}

const std::vector<Location> &config::getLocations() const {
    return _locations;
}

void config::setLocations(const std::vector<Location> &locations) {
    _locations = locations;
}
