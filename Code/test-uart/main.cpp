#include <iostream>
#include <string>

#include "Uart.h"

using namespace std;

int main(void)
{

	Uart * m_uart;

    bool keuze;
    string commando;
    string data;

    while(1)
    {
        m_uart = new Uart(SIM_KNX_UART, SIM_KNX_BAUD,0);
        cout << "Vraag(0) of verstuur(1)" << endl;
        cin >> keuze;


        if(keuze)
        {
            commando = "Send 1 0\n\r";
            m_uart->writeData(commando);
        }
        else
        {
            commando = "Get 1\n\r";
            m_uart->writeData(commando);
            data = m_uart->readData(1000);

            cout << "ontvangen data: " << data << endl;
        }

        delete m_uart;
    }

	return 0;
}