cmake_minimum_required(VERSION 3.12)
project(Server)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(Server main.cpp Socket.cpp Socket.h HandleGET.cpp HandleGET.h Utils.cpp Utils.h ParseRequest.cpp ParseRequest.h HandlePOST.cpp HandlePOST.h)