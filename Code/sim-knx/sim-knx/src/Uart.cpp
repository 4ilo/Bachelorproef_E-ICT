//
// Created by olivier on 24/02/17.
//

#include "../inc/Uart.h"

/**
 * The uart constructor
 * @param string device     The name of the uart device vb: /dev/ttyUSB0
 * @param int speed         The baudrate for the uart (defines from termios.h) vb: B9600
 * @param int pariteit      Set or disable the parity bit
 */
Uart::Uart(string device, int speed, int pariteit)
{
#if DEBUG == 0
    if((m_file = open(device.c_str(), O_RDWR | O_NOCTTY | O_SYNC)) < 0)
    {
        cerr << "Uart kan niet worden geopend." << endl;
        exit(2);
    }
#else
    m_file = 1;     // in debug mode nemen we std-in/out
#endif

    m_pariteit = pariteit;
    m_speed = speed;

#if DEBUG == 0
    setAttributes();
#endif
}

/**
 * Configure the uart with the settings provided in the constructor
 */
void Uart::setAttributes(void)
{

    struct termios tty;

    memset(&tty, 0, sizeof(tty));
    if(tcgetattr(m_file, &tty) != 0)
    {
        cerr << "Cannot get attributes form tty." << endl;
    }

    cfsetospeed(&tty, m_speed);		// Set rx baud
    cfsetispeed(&tty, m_speed);		// Set tx baud

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;		// Set 8-bit per transfer

    tty.c_iflag &= ~IGNBRK;     // Disable break processing
    tty.c_lflag = 0;            // No signal chars, no echo
    tty.c_oflag = 0;            // No remappings, no delay
    tty.c_cc[VMIN] = 1;         // 0,5s blocking mode
    tty.c_cc[VTIME] = 5;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);     // Shut off xon/xoff
    tty.c_cflag |= (CLOCAL | CREAD);            // ignore modem controls

    tty.c_cflag &= ~(PARENB | PARODD);      // pariteit
    tty.c_cflag |= m_pariteit;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if(tcsetattr(m_file, TCSANOW, &tty) != 0)
    {
        cerr << "Instellen uart parameters mislukt." << endl;
        exit(2);
    }
}

/**
 * Write data to the uart
 * @param string data
 */
void Uart::writeData(string data)
{
    write(m_file, data.c_str(), data.length());
    usleep(100000);
}

/**
 * Read a string (to the next \n) from the uart
 * @param timeout The timeout in seconds
 * @return string
 */
string Uart::readData(int timeout)
{
    char tmp;
    string data;
    bool stop = 0;

    time_t start = time(NULL);

    do
    {
        read(m_file, &tmp, 1);
        if(tmp != '\n')
        {
            data += tmp;
        }
        else
        {
            //data.pop_back();
            stop = 1;
        }

        // We stoppen na timeout seconden
        if(time(NULL) > start + timeout)
        {
            stop = 1;
        }

    }while (stop == 0);

    return data;
}

Uart::~Uart()
{
#if DEBUG == 0
    close(m_file);
#endif
}
