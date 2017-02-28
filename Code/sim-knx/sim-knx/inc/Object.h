//
// Created by olivier on 23/02/17.
//

#ifndef SIM_KNX_OBJECT_H
#define SIM_KNX_OBJECT_H

#include <string>
#include "Commando.h"
#include "commands.h"

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

public:
    Object(int nummer);
    void setData(int data);
    int getData(void);
    void send(void);
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
};


#endif //SIM_KNX_OBJECT_H
