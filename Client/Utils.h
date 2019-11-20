//
// Created by fo2sh on 19/11/19.
//

#ifndef CLIENT_UTILS_H
#define CLIENT_UTILS_H
#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <memory>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h>

using namespace std;

bool isHeaderComplete(char* buffer);
void writeToFile(char* body, char* filename,int content_length);
vector<char> readFromFile(char* filename, long &bufferSize);
string getString(char* ptr);
string getContentType(char* filename);

#endif
