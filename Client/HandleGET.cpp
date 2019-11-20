#include "HandleGET.h"

void sendGetRequest(command c){
    char* request_msg = (char *) malloc(1024);
    memset(request_msg, '\0', sizeof(request_msg));

    int length = sprintf(request_msg,"GET %s HTTP/1.1\r\nHOST: %s:%s\r\n\r\n",c.file, c.ip, c.port);
    puts(request_msg);
    if(send(request_msg,length) == SUCCESS){
        cout << "GET Request Sent!";
    }else{
        perror("error sending messages");
    }
    if(!request_msg){
        free(request_msg);
    }
}

void receiveGetRequest(){
    response res = recvGet();
    string complete_name = res.filename;
    writeToFile(res.body,&complete_name[0],res.content_length);
}

