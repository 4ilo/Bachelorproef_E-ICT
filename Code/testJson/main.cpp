#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;
using namespace std;

int main()
{

    ifstream i("file.json");
    json j;
    i >> j;

    json objects = j["objects"];

    for(int i=0; i< objects.size(); i++)
    {
        cout << "DPT: " << objects[i]["DPT"] << endl;
        cout << "Send addr: " << objects[i]["sendAddr"] << endl;
        cout << "Recv addr: " << objects[i]["recvAddr"] << endl;
        cout << endl;
    }

    cout << j.dump() << endl;
}