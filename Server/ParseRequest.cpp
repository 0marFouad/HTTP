#include "ParseRequest.h"


int getContentLength(char* buffer, int idx){
    int num = 0;
    while(buffer[idx] != '\r'){
        int n = buffer[idx] - '0';
        num *= 10;
        num += n;
        idx++;
    }
    return num;
}

string getContentType(char* buffer, int idx){
    string type = "";
    while(buffer[idx] != '/'){
        type += buffer[idx];
        idx++;
    }
    return type;
}

string getContentExtension(char* buffer, int idx){
    string ext = "";
    while(buffer[idx] != '\r'){
        ext += buffer[idx];
        idx++;
    }
    return ext;
}

string getFilename(char* buffer, int idx){
    string filename = "";
    while(buffer[idx] != '\"'){
        filename += buffer[idx];
        idx++;
    }
    return filename;
}



post_request parse_post_request(char* buffer,int &headerSize){
    post_request res;
    while(strncmp(buffer + headerSize, "\r\n\r\n", 4) != 0){
        if(strncmp(buffer + headerSize, "Content-Length: ", 16) == 0){
            res.content_length = getContentLength(buffer,headerSize+16);
            headerSize+=16;
        }
        if(strncmp(buffer + headerSize, "Content-Type: ", 14) == 0){
            res.content_type = getContentType(buffer,headerSize+14);
            headerSize+=14;
        }
        if(strncmp(buffer + headerSize, "/", 1) == 0){
            res.content_extension = getContentExtension(buffer,headerSize+1);
            headerSize+=1;
        }
        if(strncmp(buffer + headerSize, "filename = ", 11) == 0){
            res.filename = getFilename(buffer,headerSize+12);
            headerSize+=10;
        }
        headerSize++;
    }
    res.body = buffer + headerSize;
    int i=0;
    while(res.body[i] == '\r' || res.body[i] == '\n'){
        i++;
    }
    res.body += i;
    return res;
}