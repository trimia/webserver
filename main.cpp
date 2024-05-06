//#include "Client.hpp"
#include "Server.hpp"
#include "Webserver.hpp"
//#include "include.h"
int main(int argc, char** argv)
{

    std::cout<<"bella"<<std::endl;
    std::map<short,std::string> err;
    err[404]="not found";
    err[104]="magari";
    err[404]="not found";
    config pippo("8080","127.0.0.1","prova","","",1000,true,err);

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
