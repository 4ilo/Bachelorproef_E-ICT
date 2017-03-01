#include <iostream>
#include <unistd.h>

#include "inc/Object.h"
#include "inc/Device.h"
#include "inc/datatypes.h"

int main()
{
    Device sim_knx;
    sim_knx.setAddr(0x1102);        // Set device physical addr

    Object testObject(1);
    testObject.setInteroperability(DPT18_SCENE_CONTROL);
    //testObject.setSendConfig(0b000000000);      // Autosend when value changed
    //testObject.setTime(0);                      // Geen delay
    testObject.setConfiguration();

    testObject.setSendingAddr("1/1/1");
    testObject.addReveiveAddr("1/1/2");         // Send on 1/1/1 + receive on 1/1/2

    //testObject.sendBool(1);
    //testObject.sendDim(0,6);      // Send 1
    //testObject.send();

    usleep(1000000);

    testObject.sendSceneLearn(5);

    //testObject.setData(0,4);      // Send 0
    //testObject.send();

//    cout << "Ik ga sluiten." << endl;

}