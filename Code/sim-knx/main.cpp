#include <iostream>
#include "inc/Object.h"

#include "inc/Uart.h"
#include <termios.h>

int main()
{
//    Object object1(1);
//
//    object1.setData(50);
//    object1.setSendingAddr("1/2/3");
//    object1.send();
//    cout << object1.getData();

    Uart uart("/dev/ttyUSB0", B115200, 0);

}