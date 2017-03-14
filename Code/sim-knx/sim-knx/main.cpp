#include <iostream>

#include "inc/Object.h"
#include "inc/Device.h"

#include "inc/udpRequest.h"
#include <unistd.h>

#include <signal.h>

volatile int stop_app = 0;
void exitApplication(int sig);

Device glob_sim_knx;

int main(void)
{

    signal(SIGINT,exitApplication);

    glob_sim_knx.reset();
    cout << "resetting" << endl;
    usleep(1000000);
    cout << "continu" << endl;

    cout << "setting device phy adress" << endl;
    glob_sim_knx.setAddr(0x1102);

    cout << "adding device objects" << endl;
    glob_sim_knx.addObjects("config.json");

    vector<Object *> obs = glob_sim_knx.getObjects();

    cout << "Opening udp socket" << endl;
    int sock = initSocket(1234);

    struct sockaddr_in remaddr;
    socklen_t addrlen = sizeof(remaddr);
    int recvlen;
    char buffer[50];

    vector<string> request;

    cout << "Now waiting for data" << endl;
    while(stop_app != 1)
    {
        //cout << "reading" << endl;
        recvlen = recvfrom(sock, buffer, 50, 0, (struct sockaddr *)&remaddr, &addrlen);
        if(recvlen > 0)
        {
            request.clear();
            parseRequest(buffer, request);
            respondTo(request, sock, remaddr);
            memset(buffer,0,50);
        }

    }

    int one = 1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&one,sizeof(int));
    close(sock);
    cout << "Closing application save." << endl;

    return 0;
}

void exitApplication(int sig)
{
    stop_app = 1;
}


