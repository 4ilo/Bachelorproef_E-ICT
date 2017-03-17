//
// Created by olivier on 23/02/17.
//

#ifndef SIM_KNX_COMMANDO_H
#define SIM_KNX_COMMANDO_H

#include <iostream>
#include <string>

#include "Response.h"
#include "config.h"
#include "Uart.h"

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
    void changeConfig(const char * command, int hasParam = 0, int hasData = 0);

    Commando& setParameter(int param);
    Commando& setData(int data);
    Commando& setData(float data);
    Commando& setData(string data);

    void send(void);
    Response get(void);
    Response get(string testing);   // Only for testing in debug mode

    ~Commando();
};


#endif //SIM_KNX_COMMANDO_H
