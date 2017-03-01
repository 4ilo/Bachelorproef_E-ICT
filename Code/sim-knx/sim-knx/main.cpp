#include <iostream>
#include <unistd.h>

#include "inc/Object.h"
#include "inc/Device.h"
#include "inc/datatypes.h"
#include "inc/GenerateObject.h"

int main()
{
    Device sim_knx;
    sim_knx.setAddr(0x1102);        // Set device physical addr

    Object * test = GenerateObject::boolean(1);
    test->setSendingAddr("1/1/1");
    test->sendBool(1);

    Object * test2 = GenerateObject::scene(2);
    test2->setSendingAddr("1/1/2");
    test->sendScene(50);


}