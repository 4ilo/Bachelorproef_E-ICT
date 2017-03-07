//
// Created by olivier on 24/02/17.
//

#ifndef SIM_KNX_DEVICE_H
#define SIM_KNX_DEVICE_H

#include "Commando.h"
#include "commands.h"
#include "Object.h"
#include "GenerateObject.h"

#include <vector>
#include "json.h"
#include <fstream>

using json = nlohmann::json;

class Device {

private:
    vector<Object *> m_objects;

public:
    Device();
    void setAddr(int addr);
    int getAddr(void);
    bool getProgrammingMode();
    void setProgrammingMode(bool mode);
    void restart(void);
    int getState(void);
    void reset(void);
    void setTransparant(bool status);

    void addObjects(string file);
    vector<Object *> getObjects(void);

};


#endif //SIM_KNX_DEVICE_H
