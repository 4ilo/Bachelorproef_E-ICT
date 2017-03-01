//
// Created by olivier on 1/03/17.
//

#include "../inc/GenerateObject.h"

Object* GenerateObject::boolean(int objectNumber)
{
    Object *obj = new Object(objectNumber);
    obj->setInteroperability(DPT1_BOOLEAN);  // A boolean object
    obj->setSendConfig(0b000000000);         // Autosend when value changed
    obj->setTime(0);                         // Geen delay
    obj->sendConfiguration();

    return obj;
}

Object* GenerateObject::dimmer(int objectNumber)
{
    Object *obj = new Object(objectNumber);
    obj->setInteroperability(DPT3_3_BIT_CONTROLLED);  // A boolean object
    obj->setSendConfig(0b000000000);         // Autosend when value changed
    obj->setTime(0);                         // Geen delay
    obj->sendConfiguration();

    return obj;
}

Object* GenerateObject::absoluteValue(int objectNumber)
{
    Object *obj = new Object(objectNumber);
    obj->setInteroperability(DPT5_8_BIT_SCALING);  // A boolean object
    obj->setSendConfig(0b000000000);         // Autosend when value changed
    obj->setTime(0);                         // Geen delay
    obj->sendConfiguration();

    return obj;
}

Object* GenerateObject::scene(int objectNumber)
{
    Object *obj = new Object(objectNumber);
    obj->setInteroperability(DPT18_SCENE_CONTROL);  // A boolean object
    obj->setSendConfig(0b000000000);         // Autosend when value changed
    obj->setTime(0);                         // Geen delay
    obj->sendConfiguration();

    return obj;
}
