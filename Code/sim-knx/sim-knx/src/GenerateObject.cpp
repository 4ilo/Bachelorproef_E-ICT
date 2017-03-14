//
// Created by olivier on 1/03/17.
//

#include "../inc/GenerateObject.h"

/**
 * Generate a boolean object
 * @param objectNumber
 * @return Pointer naar het object
 */
Object* GenerateObject::boolean(int objectNumber)
{
    Object *obj = new Object(objectNumber);
    obj->setInteroperability(DPT1_BOOLEAN);  // A boolean object
    obj->setSendConfig(0b000000000);         // Autosend when value changed
    obj->setTime(0);                         // Geen delay
    obj->sendConfiguration();
    obj->setType(BOOL);

    return obj;
}

/**
 * Generate a dimmer object
 * @param objectNumber
 * @return Pointer to the object
 */
Object* GenerateObject::dimmer(int objectNumber)
{
    Object *obj = new Object(objectNumber);
    obj->setInteroperability(DPT3_3_BIT_CONTROLLED);  // A dimming object
    obj->setSendConfig(0b000000000);         // Autosend when value changed
    obj->setTime(0);                         // Geen delay
    obj->sendConfiguration();
    obj->setType(DIMMER);

    return obj;
}

/**
 * Generate a object with percentage value's
 * @param objectNumber
 * @return Pointer to the object
 */
Object* GenerateObject::absoluteValue(int objectNumber)
{
    Object *obj = new Object(objectNumber);
    obj->setInteroperability(DPT5_8_BIT_SCALING);  // A percentage object
    obj->setSendConfig(0b000000001);         // Autosend when value changed
    obj->setTime(0);                         // Geen delay
    obj->sendConfiguration();
    obj->setType(PERCENTAGE);

    return obj;
}

/**
 * Generate a scene object
 * @param objectNumber
 * @return Pointer to the object
 */
Object* GenerateObject::scene(int objectNumber)
{
    Object *obj = new Object(objectNumber);
    obj->setInteroperability(DPT18_SCENE_CONTROL);  // A scene object
    obj->setSendConfig(0b000000001);         // Autosend when value changed
    obj->setTime(0);                         // Geen delay
    obj->sendConfiguration();
    obj->setType(SCENE);

    return obj;
}
