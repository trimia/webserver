#ifndef _Client_HPP_
#define _Client_HPP_

#include "include.h"
#include "Socket.hpp"
#include "Request.hpp"
#include "Response.hpp"

// ******************************************************** //
//                         CLASSES                         //
// ****************************************************** //

class	Client
{
	public	:
		Client ();
		Client (Client const &obj);
		~Client ();
		Client &operator= (const Client &obj);

	private	:



        int             _id;
        Socket			_clientSock;
        Server          *_server;
        Request		    *_request;
        Response        *_response;

        int				_method;
        bool			_isFirstLine;
        bool			_isQuery;
        bool			_recvHeader;
        std::string		_cgiBody;
        size_t			_headerSize;
        size_t			_totSize;
        bool			_isContentLen;
        bool			_recvBlockSize;
        size_t			_readBlock;
        size_t			_blockSize;
        bool			_hasBeenClosed;
        //	DataType	attributes.
};

// ******************************************************** //
//                        FUNCTIONS                        //
// ****************************************************** //

#endif
