#include "Starter.h"

#define BUFFERSIZE 1048576


void startClient(char* server_ip, char* server_port) {
    printf("Trying to connect to %s on port %s\n",server_ip, server_port);
    int client_socket = establish_connection(server_ip, atoi(server_port));
    if(client_socket == 0){
        perror("Failed to connect to the server");
        exit(EXIT_FAILURE);
    }
    printf("Connected Successfully to the server\n");
    vector<command> commands = ReadCommands();
    auto t1 = std::chrono::high_resolution_clock::now();
    for(int i=0;i<commands.size();i++){
        command cur = commands[i];
        if(cur.method == "GET"){
            sendGetRequest(cur);
        }else{
            sendPostRequest(cur);
        }
    }

    char* buffer = (char *) malloc(BUFFERSIZE);
    int receivedSize = 0;
    int headerSize = 0;
    int status = 0;
    while(status = recv(client_socket, buffer + receivedSize, 100, 0)){
        if(status == -1){
            if(receivedSize > 0 && buffer[0] == 'G'){
                receiveGetRequest(buffer);
            }
            closeConnection();
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
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout << "Duration" << duration << endl;
    closeConnection();
}

int main(int argc, char** argv){
    if(argc != 3){
        printf("Invalid number of arguments\n");
        return -1;
    }
    char* server_ip = argv[1];
    char* server_port = argv[2];
    startClient(server_ip, server_port);
    return 0;
}
