#include <iostream>
#include <unistd.h>

#include "inc/Object.h"
#include "inc/Device.h"
#include "inc/datatypes.h"

int main()
{
    //cout << DEBUG << endl;
    Device sim_knx;
    sim_knx.setAddr(0xffff);        // Set device physical addr

    Object testObject(1);
    testObject.setInteroperability(DPT1_BOOLEAN);
    testObject.setSendConfig(0b000000001);      // Autosend when value changed
    testObject.setTime(0);                      // Geen delay
    testObject.setConfiguration();

    testObject.setSendingAddr("1/1/1");
    testObject.addReveiveAddr("1/1/2");         // Send on 1/1/1 + receive on 1/1/2

    testObject.setData(1);      // Send 1

    usleep(1000);

    testObject.setData(0);      // Send 0

}