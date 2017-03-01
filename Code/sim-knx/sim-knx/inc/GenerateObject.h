//
// Created by olivier on 1/03/17.
//

#ifndef SIM_KNX_GENERATEOBJECT_H
#define SIM_KNX_GENERATEOBJECT_H

#include <iostream>
#include "Object.h"
#include "datatypes.h"

using namespace std;

class GenerateObject {

public:

    static Object* boolean(int objectNumber);
    static Object* dimmer(int objectNumber);
    static Object* absoluteValue(int objectNumber);
    static Object* scene(int objectNumber);
};


#endif //SIM_KNX_GENERATEOBJECT_H
