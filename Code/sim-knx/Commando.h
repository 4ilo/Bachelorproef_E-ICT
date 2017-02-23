//
// Created by olivier on 23/02/17.
//

#ifndef SIM_KNX_COMMANDO_H
#define SIM_KNX_COMMANDO_H

#include <string>
#include "Response.h"

using namespace std;

class Commando {

private:
    string m_command;

    string m_parameter;
    int m_hasParam = 0;

    string m_data;
    bool m_hasData = 0;

    Response m_response;

    bool isParamSet(void);
    bool isDataSet(void);


public:
    Commando(const char * command, bool hasParam = 0, bool hasData = 0);
    void setParameter(int param);
    void setData(int data);
    bool send(void);
    Response get(void);
    Response response(void);
};


#endif //SIM_KNX_COMMANDO_H
