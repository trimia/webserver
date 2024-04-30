#include "Client.hpp"
#include "Server.hpp"
#include "Webserver.hpp"

int main(int argc, char** argv)
{

    std::cout<<"bella"<<std::endl;
    /*
     * check arg error
     * check config file ?
     * call parser to take info from config file and create server object to fullfill --> std::vector<Server> listOfServer
     * call setup function to  initialize everything
     * call run (function with main loop)---
     * */
    Webserver webserver;
    std::vector<Server> listOfServer;
    //example
//    TODO maybe this function could be implemented in Webserver class
//    Server server1;
//    server1.setupServer();
//    listOfServer.push_back(server1);
    //end
//
//    Server webserver;
//
//    webserver.setup(listOfServer);
//    webserver.run(listOfServer);



	return (0);
}
