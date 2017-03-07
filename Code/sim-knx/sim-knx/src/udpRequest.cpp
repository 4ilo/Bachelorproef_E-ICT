//
// Created by olivier on 7/03/17.
//

#include "../inc/udpRequest.h"

/**
 * Initialize a new udp socket and bind it to the given port
 * @param port
 * @return
 */
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

/**
 * Parse the received data from a udp receive into a vector
 * @param data The buffer with raw data
 * @param vect An empty vector
 */
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

/**
 * Respond to the request received over udp (with a response or with a bus action)
 * @param request   The request vector received from parseRequest
 * @param socket    The open socket
 * @param remoteAddr    The remoteAddr struct received from recvFrom
 */
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
