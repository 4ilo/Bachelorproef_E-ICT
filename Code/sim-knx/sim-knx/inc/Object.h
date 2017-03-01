//
// Created by olivier on 23/02/17.
//

#ifndef SIM_KNX_OBJECT_H
#define SIM_KNX_OBJECT_H

#include <string>
#include "Commando.h"
#include "commands.h"
#include <algorithm>

using namespace std;

/**
 * Classe voor de communicatie met communicatie objecten in de sim-knx module
 */
class Object {

private:
    int m_nummer = 0;
    bool m_isRaw = false;

    string m_dpt = "*";
    string m_objectType = "*";
    string m_comFlags = "*";
    string m_sendConfig = "*";
    string m_recvConfig = "*";
    string m_time = "*";

    void setData(int data);
    void setData(float data);
    void setData(bool onof, int value);
    float getData(void);
    void send(void);

public:
    Object(int nummer);

    void setSendingAddr(string addr);
    void addReveiveAddr(string addr);
    void deleteAddr(string addr);

    void setRaw(int objectType);
    void setInteroperability(int dpt);

    void setConfiguration(void);
    void setDpt(int dpt);
    void setObjectType(int type);
    void setComFlags(int flags);
    void setSendConfig(int sendConfig);
    void setRecvConfig(int recvConfig);
    void setTime(int time);

    void sendBool(bool value);
    bool getBool(void);
    void sendDim(bool status, int value);
    void getDim(bool *status, int *value);
    void sendTemp(float temp);
    float getTemp(void);
};


#endif //SIM_KNX_OBJECT_H
