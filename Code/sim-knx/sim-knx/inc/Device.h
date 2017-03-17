//
// Created by olivier on 24/02/17.
//

#ifndef SIM_KNX_DEVICE_H
#define SIM_KNX_DEVICE_H

#include <unistd.h>
#include <fstream>
#include <vector>

#include "json.h"
#include "Object.h"
#include "Commando.h"
#include "commands.h"
#include "GenerateObject.h"


using json = nlohmann::json;

class Device {

private:
    vector<Object *> m_objects;

public:
    Device();
    ~Device();
    void setAddr(int addr);
    int getAddr(void);
    bool getProgrammingMode();
    void setProgrammingMode(bool mode);
    void restart(void);
    int getState(void);
    void reset(void);
    //void setTransparant(bool status);

    void addObjects(string file);
    vector<Object *> getObjects(void);
};


#endif //SIM_KNX_DEVICE_H
