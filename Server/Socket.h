#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#define MAX_POSSIBLE_CONNECTIONS 20

#define SUCCESS 1
#define FAIL 0
#define BUFFERSIZE 1048576

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <thread>
#include <mutex>
#include "Utils.h"
#include "HandleGET.h"
#include "HandlePOST.h"

void accept_client(int &client_socket);
void start_server(unsigned short server_port);
int send(char *buffer, int buffer_size, int client_socket);
void recv(int client_socket);

#endif //SERVER_SOCKET_H
