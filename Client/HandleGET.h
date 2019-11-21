//
// Created by fo2sh on 18/11/19.
//

#ifndef CLIENT_HANDLEGET_H
#define CLIENT_HANDLEGET_H

#include "CommandReader.h";
#include "Socket.h";
#include "Utils.h";

void sendGetRequest(command c);
void receiveGetRequest(char* buffer);

#endif //CLIENT_HANDLEGET_H
