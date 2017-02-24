//
// Created by olivier on 24/02/17.
//

#include "../inc/Uart.h"

#include <termios.h>
#include <unistd.h>

Uart::Uart(string device, int speed, int pariteit)
{
    if((m_file = open(device.c_str(), O_RDWR | O_NOCTTY | O_SYNC)) < 0)
    {
        cerr << "Uart kan niet worden geopend." << endl;
        exit(2);
    }

    m_pariteit = pariteit;
    m_speed = speed;

    setAttributes();
}

void Uart::setAttributes(void)
{
    struct termios tty;

    cfsetospeed(&tty, m_speed);		// Set rx baud
    cfsetispeed(&tty, m_speed);		// Set tx baud

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;		// Set 8-bit per transfer

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); 	// geen xon/xoff ctrl

    // We stellen de pariteit in
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag |= m_pariteit;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if(tcsetattr(m_file, TCSANOW, &tty) != 0)
    {
        cerr << "Instellen uart parameters mislukt." << endl;
        exit(2);
    }

}

void Uart::writeData(string data)
{
    write(m_file, data.c_str(), data.length());
}
