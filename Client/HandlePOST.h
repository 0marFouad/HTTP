//
// Created by fo2sh on 19/11/19.
//

#ifndef CLIENT_HANDLEPOST_H
#define CLIENT_HANDLEPOST_H

#include "CommandReader.h";
#include "Socket.h";
#include "Utils.h";
#include "ParseResponse.h";


void sendPostRequest(command c);
void receivePostRequest();

#endif //CLIENT_HANDLEPOST_H
