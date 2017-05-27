//
// Created by olivier on 24/02/17.
//

#ifndef SIM_KNX_UART_H
#define SIM_KNX_UART_H

//#include <sys/ioctl.h>
#include <termios.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <time.h>

#define DEBUG 1      // Debug mode for uart komt uit CMakeLists file!!

#define SIM_KNX_UART "/dev/ttymxc4"
#define SIM_KNX_BAUD B9600

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
    string readData(int timeout);

    ~Uart();
};


#endif //SIM_KNX_UART_H
