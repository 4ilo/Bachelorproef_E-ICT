//
// Created by olivier on 23/02/17.
//

#ifndef SIM_KNX_OBJECT_H
#define SIM_KNX_OBJECT_H

#include <string>
#include "Commando.h"
#include "commands.h"

using namespace std;

class Object {

private:
    int m_nummer = 0;

public:
    Object(int nummer);
    void setData(int data);
    int getData(void);
    void send(void);
    void setSendingAddr(string addr);
};


#endif //SIM_KNX_OBJECT_H
