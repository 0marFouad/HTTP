//
// Created by fo2sh on 19/11/19.
//

#ifndef SERVER_PARSEREQUEST_H
#define SERVER_PARSEREQUEST_H

#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace std;

typedef struct{
    int content_length;
    string content_type;
    string content_extension;
    string filename;
    char* body;
} post_request;

post_request parse_post_request(char* buffer,int &headerSize);
int getContentLength(char* buffer, int idx);


#endif //SERVER_PARSEREQUEST_H
