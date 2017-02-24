//
// Created by olivier on 24/02/17.
//

#include "../inc/Device.h"

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
