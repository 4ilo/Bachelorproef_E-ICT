//
// Created by olivier on 23/02/17.
//

#include "../inc/Object.h"

/**
 * Constructor van een object
 * @param int nummer    Nummer van het object in de sim-knx modue
 */
Object::Object(int nummer)
{
    if(nummer > 0)
        m_nummer = nummer;
}

/**
 * Set object data in raw mode
 * @param int data
 */
void Object::setData(int data)
{
    Commando command(SET_OBJECT_DATA);
    command.setParameter(m_nummer);
    command.setData(data);

    command.send();
}

/**
 * Get the object data in raw mode
 * @return int
 */
int Object::getData(void)
{
    Commando commando(GET_OBJECT_DATA);
    commando.setParameter(m_nummer);

    return commando.get().data();
}

/**
 * Send a group telegram
 */
void Object::send(void)
{
    Commando commando(SEND_GROUP_TELEGRAM);
    commando.setParameter(m_nummer);
    commando.send();
}

/**
 * Set the group address for sending
 * @param string addr   Group address in knx-format
 */
void Object::setSendingAddr(string addr)
{
    Commando commando(SET_SENDING_GROUP_ADDR);
    commando.setParameter(m_nummer);
    commando.setData(addr);
    commando.send();
}
