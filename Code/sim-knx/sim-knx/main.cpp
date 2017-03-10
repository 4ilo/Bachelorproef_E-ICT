#include <iostream>

#include "inc/Object.h"
#include "inc/Device.h"

#include "inc/udpRequest.h"
#include <unistd.h>

Device glob_sim_knx;

int main(void)
{

    glob_sim_knx.reset();
    cout << "resetting" << endl;
    usleep(1000000);
    cout << "continu" << endl;
    glob_sim_knx.setAddr(0x1102);
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

    return 0;
}


