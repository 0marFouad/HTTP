#ifndef CLIENT_COMMANDREADER_H
#define CLIENT_COMMANDREADER_H

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define DEFAULT_PORT "80"

typedef struct{
    string method;
    char* file;
    char* ip;
    char* port = DEFAULT_PORT;
    string extension = "text/plain";
} command;


vector<command> ReadCommands();
string getExtension(char* filename);

#endif
