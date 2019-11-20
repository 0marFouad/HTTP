#include "HandleGET.h"



void handleGetRequest(char* buffer, int client_socket){
    string filename = getFilenameFromRequest(buffer, "GET");
    long fileSize = 0;
    vector<char> file_con = readFromFile(&filename[0],fileSize);
    if(file_con.size() == 0){
        char* response_msg = (char *) malloc(1024*1024);
        memset(response_msg, '\0', sizeof(response_msg));
        string m = "HTTP/1.1 404 Not Found\r\n\r\n";
        char* mm = &m[0];
        int length = sprintf(response_msg,mm,&filename[0]);
        send(response_msg, length,client_socket);
    }else{
        string num = to_string(fileSize);
        string cl = "Content-Length: " + num +"\r\n";
        string ct = "Content-Type: " + getContentType(&filename[0]) + "\r\n";
        string cd = "Content-Disposition: inline; filename = \""+filename+"\"";
        string msg = "HTTP/1.1 200 OK\r\n"+cl+ct+cd+"\r\n\r\n";
        char message[msg.size() + fileSize + 2];
        for(int i=0;i<msg.size();i++){
            message[i] = msg[i];
        }
        for(int i=0;i<fileSize;i++){
            message[i+msg.size()] = file_con[i];
        }
        message[msg.size() + fileSize] = '\r';
        message[msg.size() + fileSize + 1] = '\n';
        send(message, msg.size() + fileSize + 2,client_socket);
    }
}