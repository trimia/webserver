#ifndef _config_HPP_
#define _config_HPP_

#include "include.h"
#include "Location.hpp"

// ******************************************************** //
//                         CLASSES                         //
// ****************************************************** //

class	config
{
	public	:
		config ();
		config (config const &obj);

    config(uint16_t port, char *ip, const std::string &serverName, const std::string &root, const std::string &index,
           unsigned long clientMaxBodySize, bool autoindex, const std::map<short, std::string> &errorPages,
           const std::vector<Location> &locations);

    ~config ();
		config &operator= (const config &obj);

    uint16_t getPort() const;

    void setPort(uint16_t port);

    char *getIp() const;

    void setIp(char *ip);

    const std::string &getServerName() const;

    void setServerName(const std::string &serverName);

    const std::string &getRoot() const;

    void setRoot(const std::string &root);

    const std::string &getIndex() const;

    void setIndex(const std::string &index);

    unsigned long getClientMaxBodySize() const;

    void setClientMaxBodySize(unsigned long clientMaxBodySize);

    bool isAutoindex() const;

    void setAutoindex(bool autoindex);

    const std::map<short, std::string> &getErrorPages() const;

    void setErrorPages(const std::map<short, std::string> &errorPages);

    const std::vector<Location> &getLocations() const;

    void setLocations(const std::vector<Location> &locations);

private	:
        uint16_t						_port;
        char *                          _ip;
        std::string						_server_name;
        std::string						_root;
        std::string						_index;
        unsigned long					_client_max_body_size;
        bool							_autoindex;
        std::map<short, std::string>	_error_pages;
        std::vector<Location> 			_locations;
		//	DataType	attributes.
};

// ******************************************************** //
//                        FUNCTIONS                        //
// ****************************************************** //

#endif
