//
// Created by olivier on 24/02/17.
//

#include "../inc/Device.h"
#include <unistd.h>

Device::Device()
{

}

/**
 * Set the devices physical address
 * @param int addr      The physical address
 */
void Device::setAddr(int addr)
{
    Commando commando(SET_PHY_ADDR);
    commando.setData(addr);
    commando.send();
}

/**
 * Get the devices physical address
 * @return int      The address
 */
int Device::getAddr(void)
{
    Commando commando(GET_PHY_ADDR);
    return commando.get().data();
}

/**
 * Get the devices programming mode state
 * @return bool
 */
bool Device::getProgrammingMode()
{
    Commando commando(GET_PROGRAM_MODE);
    return commando.get().mode();
}

/**
 * Set the devices programming mode
 * @param mode
 */
void Device::setProgrammingMode(bool mode)
{
    Commando commando(SET_PROGRAM_MODE);
    commando.setData(mode);
    commando.send();
}

/**
 * Restart the device
 */
void Device::restart(void)
{
    Commando commando(RESTART);
    commando.send();
}

/**
 * Get the state of the device
 * @return int
 */
int Device::getState(void)
{
    Commando commando(GET_DEVICE_STATE);
    return commando.get().data();
}

/**
 * Reset the device to factory settings
 */
void Device::reset(void)
{
    Commando commando(FACTORY_RESET);
    commando.send();
}

/**
 * Set the device in transparant or normal mode
 * @param bool status
 */
void Device::setTransparant(bool status)
{
    Commando commando(DEVICE_TRANSPARANT_SET);
    if(status)
    {
        commando.setData(0b00010011);   // Set transparant, send ack, no confirm, 3level-addr
    }
    else
    {
        commando.setData(0b00010010);   // Disable transparant, send ack, no confirm, 3level-addr
    }

    commando.send();
}

void Device::addObjects(string file)
{
    ifstream jsonFile(file);
    json data;

    jsonFile >> data;
    json json_objects = data["objects"];

    m_objects.resize(json_objects.size());

    for(int i = 0; i < json_objects.size(); i++)
    {
        switch(json_objects[i]["Type"].get<int>())
        {
            case BOOL:
                m_objects[i] = GenerateObject::boolean(i + 1);
                break;

            case DIMMER:
                m_objects[i] = GenerateObject::dimmer(i + 1);
                break;

            case PERCENTAGE:
                m_objects[i] = GenerateObject::absoluteValue(i + 1);
                break;

            case SCENE:
                m_objects[i] = GenerateObject::scene(i + 1);
                break;
        }

        m_objects[i]->setSendingAddr(json_objects[i]["SendAddr"]);
        //m_objects[i]->addReveiveAddr(json_objects[i]["RecvAddr"]);
        usleep(1000000);
    }
}

vector<Object *> Device::getObjects(void)
{
    return m_objects;
}
