#include "HandlePOST.h"

void handlePostRequest(char* buffer, int client_socket,int receivedSize){
    string Ok = "HTTP/1.1 200 OK\r\n\r\n";
    send(strdup(Ok.c_str()), Ok.size(),client_socket);

    int headerSize=0;
    post_request res = parse_post_request(buffer, headerSize);
    while(receivedSize - headerSize < res.content_length){
        int status = recv(client_socket, buffer, 52428800, MSG_PEEK);
        receivedSize += status;
        if(status < 0){
            perror("error receiving messages");
            free(buffer);
            return;
        }
    }
    if(!buffer){
        free(buffer);
    }
    writeToFile(res.body,&res.filename[0],res.content_length);
}