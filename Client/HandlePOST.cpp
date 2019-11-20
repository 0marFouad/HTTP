#include "HandlePOST.h"


void sendPostRequest(command c){
    string filename = c.file;
    long fileSize = 0;
    vector<char> file_con = readFromFile(&filename[1],fileSize);
    string num = to_string(fileSize);
    string cl = "Content-Length: " + num +"\r\n";
    string ct = "Content-Type: " + getContentType(&filename[0]) + "\r\n";
    string cd = "Content-Disposition: inline; filename = \""+filename+"\"";
    string msg = "POST "+filename+" HTTP/1.1\r\n"+cl+ct+cd+"\r\n\r\n";
    char message[msg.size() + fileSize + 2];
    for(int i=0;i<msg.size();i++){
        message[i] = msg[i];
    }
    for(int i=0;i<fileSize;i++){
        message[i+msg.size()] = file_con[i];
    }
    message[msg.size() + fileSize] = '\r';
    message[msg.size() + fileSize + 1] = '\n';
    send(message, msg.size() + fileSize + 2);
}

void receivePostRequest(){
    recvPost();
}