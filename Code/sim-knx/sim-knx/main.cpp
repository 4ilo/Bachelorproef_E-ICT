#include <iostream>

#include "inc/Object.h"
#include "inc/Device.h"
#include "inc/GenerateObject.h"

#include "inc/json.h"
#include <fstream>
#include <vector>

using json = nlohmann::json;

void addObjects(string file);

int main()
{

    addObjects("config.json");

//    Device sim_knx;
//    sim_knx.setAddr(0x1102);        // Set device physical addr

//    Object * test = GenerateObject::boolean(1);
//    test->setSendingAddr("1/1/1");
//    test->sendBool(1);
//
//    Object * test2 = GenerateObject::scene(2);
//    test2->setSendingAddr("1/1/2");
//    test->sendScene(50);


}

void addObjects(string file)
{
    ifstream jsonFile(file);
    json data;

    jsonFile >> data;
    json json_objects = data["objects"];

    vector<Object *> objects(json_objects.size());

    for(int i = 0; i < json_objects.size(); i++)
    {
        switch(json_objects[i]["Type"].get<int>())
        {
            case 1:
                objects[i] = GenerateObject::boolean(i);
                break;

            case 2:
                objects[i] = GenerateObject::dimmer(i);
                break;

            case 3:
                objects[i] = GenerateObject::absoluteValue(i);
                break;

            case 4:
                objects[i] = GenerateObject::scene(i);
                break;
        }

        objects[i]->setSendingAddr(json_objects[i]["SendAddr"]);
        objects[i]->addReveiveAddr(json_objects[i]["RecvAddr"]);
    }
}