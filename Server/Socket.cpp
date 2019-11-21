#include "Socket.h"

struct sockaddr_in server_addr;
int server_socket;
int connected_clients;
int timeout;
mutex connection_lock;

void handle_connection(int client_socket) {
    recv(client_socket);
}

void add_connection(){
    connection_lock.lock();
    connected_clients++;
    connection_lock.unlock();
    cout << "Connection Increase: " << connected_clients << endl;
}

void remove_connection(){
    connection_lock.lock();
    connected_clients--;
    connection_lock.unlock();
    cout << "Connection Decrease: " << connected_clients << endl;
}

void get_timeout(){
    cout << "Timeout :" << timeout << endl;
    connection_lock.lock();
    timeout = MAX_POSSIBLE_CONNECTIONS - connected_clients;
    connection_lock.unlock();
}

void start_server(unsigned short server_port){
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(server_port);

    if((server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        perror("socket() failed");
        exit(1);
    }

    if(bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
        perror("bind() failed");
        exit(1);
    }

    if(listen(server_socket, MAX_POSSIBLE_CONNECTIONS) < 0){
        perror("listen() failed");
        exit(1);
    }

    while(1) {
        int client_socket = 0;
        accept_client(client_socket);
        printf("Thread Started for the new client.\n");
        if(connected_clients == MAX_POSSIBLE_CONNECTIONS){
            printf("Reached the max limit number of connections, So server can't handle that client connection\n");
            continue;
        }
        add_connection();
        thread t(handle_connection,client_socket);
        t.detach();
    }
}

void accept_client(int &client_socket){
    struct sockaddr_in client_addr;
    unsigned int client_length = sizeof(client_addr);
    if((client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_length)) < 0){
        perror("failed to accept client:");
        exit(1);
    }
}

void close_connection(int client_socket){
    remove_connection();
    close(client_socket);
}

int send(char *buffer, int buffer_size, int client_socket) {
    int sent = 0;
    while(sent < buffer_size) {
        sent += send(client_socket, buffer + sent, buffer_size, 0);
    }
    if(sent != buffer_size) {
        perror("Not All Characters Were Sent");
        return FAIL;
    }
    return SUCCESS;
}

void recv(int client_socket){
    struct timeval tv;
    get_timeout();
    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    char* buffer = (char *) malloc(BUFFERSIZE);
    int receivedSize = 0;
    int headerSize = 0;
    int status = -1;
    while(status = recv(client_socket, buffer + receivedSize, 100, 0)){
        if(status == -1){
            if(receivedSize > 0){
                if(buffer[0] == 'G'){
                    handleGetRequest(buffer, client_socket);
                }else{
                    handlePostRequest(buffer,client_socket);
                }
            }
            close_connection(client_socket);
            break;
        }
        receivedSize += status;
        int content_length = 0;
        if(isHeaderComplete(buffer, receivedSize, headerSize) && !isThereContentLength(buffer, headerSize, content_length)){
            handleGetRequest(buffer, client_socket);
            buffer = &buffer[headerSize];
            receivedSize -= (headerSize);
        }else if(isHeaderComplete(buffer, receivedSize, headerSize) && isThereContentLength(buffer, headerSize, content_length)){
            if(receivedSize >= headerSize + content_length){
                handlePostRequest(buffer,client_socket);
                buffer = &buffer[headerSize + content_length + 2];
                receivedSize -= (headerSize + content_length + 2);
            }
        }
        if(status < 100 && receivedSize > 0){
            if(buffer[0] == 'G'){
                handleGetRequest(buffer, client_socket);
                receivedSize = 0;
                headerSize = 0;
            }else{
                handlePostRequest(buffer,client_socket);
                receivedSize = 0;
                headerSize = 0;
            }
        }
    }
    if(status == 0){
        close_connection(client_socket);
    }
}