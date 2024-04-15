#ifndef _Location_HPP_
#define _Location_HPP_

#include "include.h"

// ******************************************************** //
//                         CLASSES                         //
// ****************************************************** //

class	Location
{
	public	:
		Location ();
		Location (Location const &obj);
		~Location ();
		Location &operator= (const Location &obj);

	private	:
    //check if is all necessary and to do what?
        std::string					_path;
        std::string					_root;
        bool						_autoindex;
        std::string					_index;
        std::vector<short>			_methods; // GET+ POST- DELETE- PUT- HEAD-
        std::string					_return;
        std::string					_alias;
        std::vector<std::string>	_cgi_path;
        std::vector<std::string>	_cgi_ext;
        unsigned long				_client_max_body_size;

    //	DataType	attributes.
};

// ******************************************************** //
//                        FUNCTIONS                        //
// ****************************************************** //

#endif
