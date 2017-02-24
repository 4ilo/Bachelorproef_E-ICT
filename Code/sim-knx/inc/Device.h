//
// Created by olivier on 24/02/17.
//

#ifndef SIM_KNX_DEVICE_H
#define SIM_KNX_DEVICE_H

#include "Commando.h"
#include "commands.h"

class Device {

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

};


#endif //SIM_KNX_DEVICE_H
