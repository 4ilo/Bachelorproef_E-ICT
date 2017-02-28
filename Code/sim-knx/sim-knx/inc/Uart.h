//
// Created by olivier on 24/02/17.
//

#ifndef SIM_KNX_UART_H
#define SIM_KNX_UART_H



#include <string>
#include <fcntl.h>
#include <iostream>
#include "config.h"

using namespace std;

/**
 * Class for communication with the uart
 */
class Uart {

private:
    int m_file;
    int m_speed;
    int m_pariteit;

    void setAttributes(void);

public:
    Uart(string device, int speed, int pariteit);

    void writeData(string data);
    string readData(void);

    ~Uart();
};


#endif //SIM_KNX_UART_H
