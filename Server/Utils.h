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
#include <sys/stat.h>
#include "ParseRequest.h"

using namespace std;

bool isHeaderComplete(char* buffer,int len,int &headerSize);
bool isThereContentLength(char* buffer, int size, int &content_length);
void writeToFile(char* body, char* filename,int content_length);
vector<char> readFromFile(char* filename, long &bufferSize);
string getString(char* ptr);
string getContentType(char* filename);
void writeInFile(char* filename, char* buffer ,int bufferSize);
string getFilenameFromRequest(char* buffer, string method);

#endif //CLIENT_UTILS_H
