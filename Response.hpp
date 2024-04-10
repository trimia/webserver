#ifndef _Response_HPP_
#define _Response_HPP_

#include <iostream>

// ******************************************************** //
//                         CLASSES                         //
// ****************************************************** //
enum e_resource_type
{
    RT_FILE,
    RT_DIR
};
class	Response
{
	public	:
		Response ();
		Response (Response const &obj);
		~Response ();
		Response &operator= (const Response &obj);

	private	:
    //we have to decide what we need here there were 2 example
    //firt:
        Server    _server;
        std::string     _target_file;
        std::vector<uint8_t> _body;
        size_t          _body_length;
        std::string     _response_body;
        std::string     _location;
        short           _code;
        char            *_res;
        int				_cgi;
        int				_cgi_fd[2];
        size_t			_cgi_response_length;
        bool            _auto_index;
    //second:
        Request					*_request;
        bool					_isFinished;
        int						_statusCode;
        std::string				_resource;
        enum e_resource_type	_resourceType;
        std::string				_content;
        std::string				_contentType;
        std::string				_finalMsg;
        std::string				_index;
		//	DataType	attributes.
};

// ******************************************************** //
//                        FUNCTIONS                        //
// ****************************************************** //

#endif
