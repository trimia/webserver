#ifndef _Server_HPP_
#define _Server_HPP_

#include "include.h"
#include "Location.hpp"

// ******************************************************** //
//                         CLASSES                         //
// ****************************************************** //

class	Server
{
	public	:
		Server ();
		Server (Server const &obj);
		~Server ();
		Server &operator= (const Server &obj);

	private	:
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
        int     						_listen_fd;
		//	DataType	attributes.
};

// ******************************************************** //
//                        FUNCTIONS                        //
// ****************************************************** //

#endif
