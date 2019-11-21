#include "CommandReader.h"

command ParseCommand(string str_command) {
    static const string REGEX_GET_POST_PORT = "((GET|POST)\\s(.+)\\s(.+)\\s(.+)(\n)*)";
    static const string REGEX_GET_POST_NO_PORT = "((GET|POST)\\s(.+)\\s(.+)(\n)*)";
    regex rx(REGEX_GET_POST_PORT);
    regex rxp(REGEX_GET_POST_NO_PORT);
    string extractedSubmatchPath = { "" };
    command parsedCommand;

    smatch pieces_match;
    if (regex_match(str_command, pieces_match, rx)) {
        ssub_match sub_match = pieces_match[2];
        parsedCommand.method = sub_match.str();
        sub_match = pieces_match[3];
        parsedCommand.file = strdup(sub_match.str().c_str());
        sub_match = pieces_match[4];
        parsedCommand.ip = strdup(sub_match.str().c_str());
        sub_match = pieces_match[5];
        parsedCommand.port = strdup(sub_match.str().c_str());
    }else if(regex_match(str_command, pieces_match, rxp)){
        ssub_match sub_match = pieces_match[2];
        parsedCommand.method = sub_match.str();
        sub_match = pieces_match[3];
        parsedCommand.file = strdup(sub_match.str().c_str());
        sub_match = pieces_match[4];
        parsedCommand.ip = strdup(sub_match.str().c_str());
    }
    return parsedCommand;
}

vector<command> ReadCommands() {
    vector<command> commands;
    FILE *fp;
    fp = fopen("/home/fo2sh/CLionProjects/HTTP/Client/commands.txt" ,"r");
    if (fp == nullptr) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    char buf[1000];
    while(fgets(buf, sizeof(buf), fp) != nullptr){
        string s(buf);
        cout << s << endl;
        command cur = ParseCommand(s);
        cur.extension = getExtension(cur.file);
        commands.push_back(cur);
    }
    return commands;
}

string getExtension(char* filename){
    string ext = "";
    int i=0;
    while(strncmp(filename + i, ".", 1) != 0){
        i++;
    }
    i++;
    while(filename[i] != '\0'){
        ext += filename[i];
        i++;
    }

    if(ext == "txt"){
        return "text/plain";
    }
    if(ext == "html"){
        return "text/html";
    }
    return "image/" + ext;
}
