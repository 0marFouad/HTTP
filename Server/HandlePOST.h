//
// Created by fo2sh on 20/11/19.
//

#ifndef SERVER_HANDLEPOST_H
#define SERVER_HANDLEPOST_H
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "Utils.h"
#include "Socket.h"
#include "ParseRequest.h"

void handlePostRequest(char* buffer, int client_socket,int receivedSize);

#endif //SERVER_HANDLEPOST_H
