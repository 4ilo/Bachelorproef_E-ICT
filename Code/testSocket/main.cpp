#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

void parseRequest(char * data, vector<string> & vect);
void RespondTo(vector<string> & request, int socket, sockaddr_in remaddr);

int main()
{

    int sock;

    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        cerr << "Cannot create socket!" << endl;
        return 1;
    }
    cout << "SocketNr: " << sock << endl;

    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(1234);

    if(bind(sock, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0)
    {
        cerr << "Bind failed." << endl;
        return 2;
    }

    int recvlen;
    char buf[255];

    struct sockaddr_in remaddr;
    socklen_t addrlen = sizeof(remaddr);

    while(1)
    {
        cout << "Waiting on port 1234" << endl;

        recvlen =  recvfrom(sock, buf, 255, 0, (struct sockaddr *)&remaddr, &addrlen);

        //cout << "Received " << recvlen << " bytes." << endl;
        //cout << "Data: " << buf << endl;

        vector<string> request;
        parseRequest(buf, request);

        string response;
        RespondTo(request, sock, remaddr);
    }

    return 0;
}

void RespondTo(vector<string> & request, int socket, sockaddr_in remoteAddr)
{
    if(request[0] == "type")
    {
        string response = "bool";

        // Send the response
        socklen_t addrlen = sizeof(remoteAddr);
        sendto(socket, response.c_str(), response.length(), 0, (struct sockaddr *)&remoteAddr, addrlen);
    }
    else if(request[0] == "set")
    {
        cout << "Set object " << request[1] << " to " << request[2] << endl;
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