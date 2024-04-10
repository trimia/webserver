#ifndef _Socket_HPP_
#define _Socket_HPP_

#include "include.h"


// ******************************************************** //
//                         CLASSES                         //
// ****************************************************** //

class	Socket
{
	public	:
		Socket ();
		Socket (Socket const &obj);
		~Socket ();
		Socket &operator= (const Socket &obj);
        //maybe int is better because of bind listen and accept return an int 0 or errno
        //server side
        bool bindSocket(SOCKET serversocket, uint16_t port);
        bool listenOnSocket(SOCKET serversocket);
        bool acceptConnection(SOCKET serversocket);
        //client side
        bool connectsocket()

	private	:

    //	DataType	attributes.
};

// ******************************************************** //
//                        FUNCTIONS                        //
// ****************************************************** //

#endif
