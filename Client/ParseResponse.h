#ifndef CLIENT_PARSERESPONSE_H
#define CLIENT_PARSERESPONSE_H

#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace std;

typedef struct{
    int content_length;
    int status_code;
    string content_type;
    string content_extension;
    string filename;
    char* body;
} response;

string getContentExtension(char* buffer, int idx);
response parse_response(char* buffer,int &headerSize);

#endif
