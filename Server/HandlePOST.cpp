#include "HandlePOST.h"

void handlePostRequest(char* buffer, int client_socket){
    string Ok = "HTTP/1.1 200 OK\r\n\r\n";
    send(strdup(Ok.c_str()), Ok.size(),client_socket);
    int headerSize=0;
    post_request res = parse_post_request(buffer, headerSize);
    writeToFile(res.body,&res.filename[0],res.content_length);
}