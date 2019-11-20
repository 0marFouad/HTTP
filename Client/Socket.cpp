#include "Socket.h"


int client_socket_id;

int establish_connection(char* server_ip, int server_port){
    int sock;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return FAIL;
    }


    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) < 1) {
        perror("\nInvalid address / Address not supported \n");
        return FAIL;
    }

    // Server accepted my connection.
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("\nConnection Failed \n");
        return FAIL;
    }
    client_socket_id = sock;
    return sock;
}


int send(char *buffer, int buffer_size) {
    int sent = 0;
    const int TIMEOUT = 5;
    clock_t curTime = clock();
    while(sent < buffer_size && (clock() - curTime)/CLOCKS_PER_SEC < TIMEOUT) {
        sent += send(client_socket_id, (void *)(buffer + sent), buffer_size - sent, 0);
    }
    if(sent != buffer_size) {
        perror("Not All Characters Were Sent");
        return FAIL;
    }
    return SUCCESS;
}

response recvGet(){
    response res;
    char* buffer = (char *) malloc(52428800);
    int receivedSize = 0;
    while(!isHeaderComplete(buffer)){
        int status = recv(client_socket_id, buffer, 52428800, MSG_PEEK);
        receivedSize += status;
        if(status < 0){
            perror("error receiving messages");
            free(buffer);
            return res;
        }
    }
    int headerSize=0;
    res = parse_response(buffer, headerSize);
    if(res.status_code == 404){
        return res;
    }
    while(receivedSize - headerSize < res.content_length){
        int status = recv(client_socket_id, buffer, 52428800, MSG_PEEK);
        receivedSize += status;
        if(status < 0){
            perror("error receiving messages");
            free(buffer);
            return res;
        }
    }
    if(!buffer){
        free(buffer);
    }
    return res;
}

void recvPost(){
    char* buffer = (char *) malloc(1024);
    while(!isHeaderComplete(buffer)){
        int status = recv(client_socket_id, buffer, 1024, MSG_PEEK);
        if(status < 0){
            perror("error receiving messages");
            free(buffer);
            return;
        }
    }
}

void closeConnection(){
    close(client_socket_id);
}