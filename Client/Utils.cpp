#include "Utils.h"


bool isHeaderComplete(char* buffer, int len, int &headerSize){
    int i = 0;
    while(i+4<len){
        if(strncmp(buffer + i, "\r\n\r\n", 4) == 0){
            headerSize = i + 4;
            return true;
        }
        i++;
    }
    return false;
}


bool isThereContentLength(char* buffer, int size, int &content_length){
    int i = 0;
    while(i+16<size){
        if(strncmp(buffer + i, "Content-Length: ", 16) == 0){
            content_length = getContentLength(buffer,i+16);
            return true;
        }
        i++;
    }
    return false;
}

void writeToFile(char* body, char* filename,int content_length){
    if(filename[0] == '/'){
        filename++;
    }
    FILE * fp = fopen(filename, "wb");
    if(!fp){
        perror("Client could not write the response to the file");
        return;
    }
    printf("Client is writing the data content = %d into the file %s\n",content_length, filename);
    fwrite(body, content_length, 1, fp);
    fclose(fp);
}

vector<char> readFromFile(char* filename, long &bufferSize){
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



//char* readFromFile(char* filename, long &bufferSize){
//    FILE *file = fopen(filename, "rb");
//    if(!file){
//        perror("Can't find the file\n");
//        return nullptr;
//    }
//    fseek(file, 0, SEEK_END);
//    bufferSize = ftell(file);
//    rewind(file);
//    fclose(file);
//    char* bufferedFile = (char *) malloc(bufferSize);
//    memset(bufferedFile, '\0', sizeof(bufferedFile));
//    int numRead = fread(bufferedFile, sizeof(char), bufferSize, file);
//    return bufferedFile;
//}

string getString(char* ptr){
    int i=0;
    string res = "";
    while(ptr[i] != '\0'){
        res += ptr[i];
        i++;
    }
    return res;
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