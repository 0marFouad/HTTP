#include "Starter.h"

#define BUFFERSIZE 1048576


int waiting_for_request(int client_socket){
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(client_socket, &rfds);
    int retval = select(1, &rfds, NULL, NULL, &tv);
    return retval;
}

void startClient(char* server_ip, char* server_port, char* commands_file) {
    printf("Trying to connect to %s on port %s\n",server_ip, server_port);
    int client_socket = establish_connection(server_ip, atoi(server_port));
    if(client_socket == 0){
        perror("Failed to connect to the server");
        exit(EXIT_FAILURE);
    }
    printf("Connected Successfully to the server\n");
    vector<command> commands = ReadCommands();
    for(int i=0;i<commands.size();i++){
        command cur = commands[i];
        if(cur.method == "GET"){
            sendGetRequest(cur);
        }else{
            sendPostRequest(cur);
        }
    }

    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    char* buffer = (char *) malloc(5000);
    int receivedSize = 0;
    int headerSize = 0;
    int status = 0;
    while(status = recv(client_socket, buffer + receivedSize, 20, 0)){
        if(status == -1){
            break;
        }
        receivedSize += status;
        int content_length = 0;
        if(isHeaderComplete(buffer, receivedSize, headerSize) && !isThereContentLength(buffer, headerSize, content_length)){
            buffer = &buffer[headerSize];
            receivedSize -= (headerSize);
        }else if(isHeaderComplete(buffer, receivedSize, headerSize) && isThereContentLength(buffer, headerSize, content_length)){
            if(receivedSize >= headerSize + content_length){
                receiveGetRequest(buffer);
                buffer = &buffer[headerSize + content_length + 2];
                receivedSize -= (headerSize + content_length + 2);
            }
        }
    }
    if(buffer[0] == 'G'){
        receiveGetRequest(buffer);
    }
    closeConnection();
}

int main(int argc, char** argv){
    if(argc != 3){
        printf("Invalid number of arguments\n");
        return -1;
    }
    char* server_ip = argv[1];
    char* server_port = argv[2];
    startClient(server_ip, server_port, "commands.txt");
    return 0;
}
