#include "Starter.h"

void startClient(char* server_ip, char* server_port, char* commands_file) {
    printf("Trying to connect to %s on port %s\n",server_ip, server_port);
    int status = establish_connection(server_ip, atoi(server_port));
    if(status == 0){
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
    for(int i=0;i<commands.size();i++){
        command cur = commands[i];
        if(cur.method == "GET"){
            receiveGetRequest();
        }else{
            receivePostRequest();
        }
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
