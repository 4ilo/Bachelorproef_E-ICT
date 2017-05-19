//
// Created by olivier on 7/03/17.
//

#ifndef SIM_KNX_UDPREQUEST_H
#define SIM_KNX_UDPREQUEST_H

#include <iostream>
#include <vector>
#include <string>
//#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include "Object.h"
#include "Device.h"

using namespace std;

extern Device glob_sim_knx;

int initSocket(uint16_t port);
void parseRequest(char * data, vector<string> & vect);
void respondTo(vector<string> & request, int socket, sockaddr_in remoteAddr);

#endif //SIM_KNX_UDPREQUEST_H
