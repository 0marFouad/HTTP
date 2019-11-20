#include <iostream>
#include "Utils.h"
#include "HandleGET.h"

//int main() {
//    string m = "GET ahmed/omar4.txt HTTP/1.1\r\nHOST: 127.0.0.1:8080\r\n";
//    handleGetRequest(&m[0],0);
//    string s = "omar.txt";
//    return 0;
//}


int main(int argc, char** argv){
//    string filename = "omar.txt";
//    long fileSize = 0;
//    vector<char> v = readFromFile(&filename[0],fileSize);
//    char m[fileSize];
//    for(int i=0;i<fileSize;i++){
//        m[i] = v[i];
//    }
//    cout << getString(m);


    if(argc != 2){
        printf("Invalid number of arguments\n");
        return -1;
    }
    printf("Starting Server, Server is waiting now for client connections\n");
    start_server(atoi(argv[1]));
}