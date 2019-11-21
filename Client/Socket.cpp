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
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) < 1) {
        perror("\nInvalid address / Address not supported \n");
        return FAIL;
    }
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


response recvGet(char* buffer){
    response res;
    res = parse_response(buffer);
    if(res.status_code == 404){
        return res;
    }
    return res;
}


void closeConnection(){
    close(client_socket_id);
}