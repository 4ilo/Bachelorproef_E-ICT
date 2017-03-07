#include <iostream>

#include "inc/Object.h"
#include "inc/Device.h"
#include "inc/GenerateObject.h"

#include "inc/json.h"
#include <fstream>
#include <vector>

#include <sys/socket.h>
#include <netinet/in.h>



void addObjects(string file, vector<Object *> &objects);

int initSocket(uint16_t port);
void parseRequest(char * data, vector<string> & vect);
void respondTo(vector<string> & request, int socket, sockaddr_in remaddr);

Device glob_sim_knx;

int main(void)
{

    glob_sim_knx.addObjects("config.json");

    vector<Object *> obs = glob_sim_knx.getObjects();

    int sock = initSocket(1234);

    struct sockaddr_in remaddr;
    socklen_t addrlen = sizeof(remaddr);
    int recvlen;
    char buffer[50];

    vector<string> request;

    while(1)
    {
        recvlen = recvfrom(sock, buffer, 50, 0, (struct sockaddr *)&remaddr, &addrlen);
        if(recvlen != 0)
        {
            request.clear();
            parseRequest(buffer, request);
            respondTo(request, sock, remaddr);
            memset(buffer,0,50);
        }

    }

    return 0;
}

int initSocket(uint16_t port)
{
    int sock;

    // Create a socket
    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        cerr << "Cannot create socket!" << endl;
        return 1;
    }

    // Set a ip and port to listen on
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(port);

    if(bind(sock, (struct sockaddr *) &myaddr, sizeof(myaddr)) < 0)
    {
        cerr << "Failed to bind socket to port " << port << endl;
        return 2;
    }

    return sock;
}

void respondTo(vector<string> & request, int socket, sockaddr_in remoteAddr)
{
    static vector<Object *> objects = glob_sim_knx.getObjects();
    int objectNr = stoi(request[1]) - 1;

    if(request[0] == "type")
    {
        string response = to_string(objects[objectNr]->getType());

        // Send the response
        socklen_t addrlen = sizeof(remoteAddr);
        sendto(socket, response.c_str(), response.length(), 0, (struct sockaddr *)&remoteAddr, addrlen);
    }
    else if(request[0] == "set")
    {
        switch (objects[objectNr]->getType())
        {
            case BOOL:
                objects[objectNr]->sendBool((bool) stoi(request[2]));
                break;
            case DIMMER:
                objects[objectNr]->sendDim((bool) stoi(request[2]), stoi(request[3]));
                break;
            case PERCENTAGE:
                objects[objectNr]->sendPercentage(stoi(request[2]));
                break;
            case SCENE:
                objects[objectNr]->sendScene(stoi(request[2]));
                break;
        }
    }


}

void parseRequest(char * data, vector<string> & vect)
{
    char * part;
    part = strtok(data," ");

    while (part != NULL)
    {
        vect.push_back(string(part));
        part = strtok(NULL, " ");
    }
}