#include <iostream>

#include "inc/Object.h"
#include "inc/Device.h"

#include "inc/udpRequest.h"
#include <unistd.h>

#include <signal.h>

volatile int stop_app = 0;
void exitApplication(int sig);

Device glob_sim_knx;

int main(int argc, char * argv[])
{
    int portNumber;
    string configFileName;

    if(argc == 3)
    {
        portNumber = atoi(argv[1]);
        configFileName = argv[2];

    } else {
        portNumber = 1234;
        configFileName = "config.json";
    }

    signal(SIGINT,exitApplication);

    glob_sim_knx.reset();
    usleep(1000000);

    cout << "setting device phy adress" << endl;
    glob_sim_knx.setAddr(0x1102);

    cout << "adding device objects" << endl;
    glob_sim_knx.addObjects(configFileName);

    vector<Object *> obs = glob_sim_knx.getObjects();

    cout << "Opening udp socket on port " << portNumber << endl;
    int sock = initSocket(portNumber);

    struct sockaddr_in remaddr;
    socklen_t addrlen = sizeof(remaddr);
    int recvlen;
    char buffer[50];

    vector<string> request;

    cout << "Now waiting for data" << endl;
    while(stop_app != 1)
    {
        recvlen = recvfrom(sock, buffer, 50, 0, (struct sockaddr *)&remaddr, &addrlen);
        if(recvlen > 0)
        {
            request.clear();
            parseRequest(buffer, request);
            respondTo(request, sock, remaddr);
            memset(buffer,0,50);
        }

    }

    // We ontbinden en sluiten de udp-socket
    int one = 1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&one,sizeof(int));
    close(sock);
    cout << "Closing application save." << endl;

    return 0;
}

/**
 * Signal handler om bij ctrl-c de applicatie mooi af te sluiten
 * @param sig
 */
void exitApplication(int sig)
{
    stop_app = 1;
}


