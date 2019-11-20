cmake_minimum_required(VERSION 3.12)
project(Client)

set(CMAKE_CXX_STANDARD 14)

add_executable(Client main.cpp Socket.cpp Socket.h CommandReader.cpp CommandReader.h HandleGET.cpp HandleGET.h Utils.cpp Utils.h ParseResponse.cpp ParseResponse.h HandlePOST.cpp HandlePOST.h Starter.cpp Starter.h)