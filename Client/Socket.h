//
// Created by fo2sh on 18/11/19.
//

#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "Utils.h"
#include "ParseResponse.h"

#define SUCCESS 1
#define FAIL 0

int send(char *buffer, int buffer_size);
response recvGet();
void recvPost();
int establish_connection(char* server_ip, int server_port);
void closeConnection();

#endif
