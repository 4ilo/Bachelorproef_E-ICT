#include <iostream>
#include <unistd.h>

#include "inc/Object.h"
#include "inc/Device.h"
#include "inc/datatypes.h"

int main()
{
//    cout << "test" << endl;
//    Device sim_knx;
//    sim_knx.setAddr(0x1102);        // Set device physical addr
//
//    Object testObject(1);
//    testObject.setInteroperability(DPT1_BOOLEAN);
//    //testObject.setRaw(OBJ_1_BYTE);
//    testObject.setSendConfig(0b000000000);      // Autosend when value changed
//    testObject.setTime(0);                      // Geen delay
//    testObject.setConfiguration();
//
//    testObject.setSendingAddr("1/1/1");
//    testObject.addReveiveAddr("1/1/2");         // Send on 1/1/1 + receive on 1/1/2
//
//    //testObject.setData(1);      // Send 1
//    //testObject.send();
//
//    usleep(1000000);
//
//    int test = testObject.getData();
//    cout << "testobj: " << test << endl;
//
//    testObject.setData(0);      // Send 0
//    testObject.send();
//
//    cout << "Ik ga sluiten." << endl;

    Commando cmd(GET_OBJECT_VALUE);
    cmd.setParameter(1);
    cout << cmd.get("!error $0102 <iud>").data() << endl;


}