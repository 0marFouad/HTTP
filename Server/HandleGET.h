//
// Created by fo2sh on 19/11/19.
//

#ifndef SERVER_HANDLEGET_H
#define SERVER_HANDLEGET_H
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "Utils.h"
#include "Socket.h"

void handleGetRequest(char* buffer, int client_socket);

#endif
