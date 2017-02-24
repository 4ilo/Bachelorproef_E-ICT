//
// Created by olivier on 23/02/17.
//

#ifndef SIM_KNX_COMMANDO_H
#define SIM_KNX_COMMANDO_H

#include <string>
#include <iostream>
#include "Response.h"
#include "Uart.h"
#include "config.h"

using namespace std;

/**
 * Klasse die verantwoordelijk is voor het opbouwen van een commando
 */
class Commando {

private:
    string m_command;

    string m_parameter;
    int m_hasParam = 0;

    string m_data;
    int m_hasData = 0;

    Response m_response;

    Uart * m_uart;

    bool isParamSet(void);
    bool isDataSet(void);


public:
    Commando(const char * command, int hasParam = 0, int hasData = 0);
    void setParameter(int param);
    void setData(int data);
    void setData(string data);
    void send(void);
    Response get(void);

    ~Commando();
};


#endif //SIM_KNX_COMMANDO_H
