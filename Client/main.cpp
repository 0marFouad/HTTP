#include <bits/stdc++.h>
#include "Socket.h"
#include "CommandReader.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Utils.h"
#include "HandlePOST.h"

using namespace std;



int main1() {
    command c;
    c.file = "omar.txt";
    c.port = "8080";
    c.ip = "127.0.0.1";
    c.method = "POST";
    c.extension = "text/plain";
    sendPostRequest(c);
    return 0;
}