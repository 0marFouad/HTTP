#include "Utils.h"


bool isHeaderComplete(char* buffer){
    char *search = "\r\n\r\n";
    char *ptr = strstr(buffer, search);
    return (ptr != NULL);
}

void writeToFile(char* body, char* filename,int content_length){ ;
    if(filename[0] == '/'){
        filename++;
    }
    FILE * fp = fopen(filename, "wb");
    if(!fp){
        perror("Can't write to file in server");
        return;
    }
    printf("Client is writing the data content = %d into the file %s\n",content_length, filename);
    fwrite(body, content_length, 1, fp);
    fclose(fp);
}


vector<char> readFromFile(char* filename, long &bufferSize){
    if(filename[0] = '/'){
        filename += 1;
    }
    ifstream file(filename, std::ios::binary | std::ios::ate);
    if(file.fail()){
        perror("Can't find the file\n");
        vector<char> v;
        return v;
    }else{
        streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        vector<char> buffer(size);
        file.read(buffer.data(), size);
        bufferSize = buffer.size();
        return buffer;
    }
}

void writeInFile(char* filename, char* buffer ,int bufferSize){
    if(filename[0] == '/'){
        filename += 1;
    }
    FILE * fp = fopen(filename, "wb");
    if(!fp){
        perror("Server could not write the response to the file");
        return;
    }
    printf("Server is writing the data content = %d into the file %s\n", bufferSize, filename);
    fwrite(buffer, bufferSize, 1, fp);
    fclose(fp);
}

string getString(char* ptr){
    int i=0;
    string res = "";
    while(ptr[i] != '\0'){
        res += ptr[i];
        i++;
    }
    return res;
}

string getFilenameFromRequest(char* buffer, string method){
    string fn = "";
    int i = 4;
    if(method == "POST"){
        i = 5;
    }
    while(buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\0'){
        fn += buffer[i];
        i++;
    }
    return fn;
}

string getContentType(char* filename){
    string ext = "";
    int i=0;
    while(filename[i] != '.'){
        i++;
    }
    i++;
    while(filename[i] != '\0'){
        ext += filename[i];
        i++;
    }
    if(ext == "txt"){
        return "text/plain";
    }else if(ext == "html"){
        return "text/html";
    }else{
        return "image/"+ext;
    }
}