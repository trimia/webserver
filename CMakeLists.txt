cmake_minimum_required(VERSION 3.27)
project(webserver)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(webserver
        Client.cpp
        Client.hpp
        config.cpp
        config.hpp
        include.h
        main.cpp
        Parser.cpp
        Parser.hpp
        Request.cpp
        Request.hpp
        Response.cpp
        Response.hpp
        Server.cpp
        Server.hpp
        Socket.cpp
        Socket.hpp
        Location.cpp
        Location.hpp
        Webserver.hpp
        Webserver.cpp)
