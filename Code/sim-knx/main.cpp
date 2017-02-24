#include <iostream>

#include "inc/Object.h"
#include "inc/Device.h"

int main()
{

    Device sim_knx;
    sim_knx.setAddr(0xffff);        // Set device physical addr

    Object object1(1);
    object1.setData(50);
    object1.setConfiguration();
    object1.setSendingAddr("1/2/3");
    object1.send();
    cout << object1.getData();

}