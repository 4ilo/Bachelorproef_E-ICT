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
    command.setParameter(m_nummer)
           .setData(data)
           .send();
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
    commando.setParameter(m_nummer)
            .send();
}

/**
 * Set the group address for sending
 * @param string addr   Group address in knx-format
 */
void Object::setSendingAddr(string addr)
{
    Commando commando(SET_SENDING_GROUP_ADDR);
    commando.setParameter(m_nummer)
            .setData(addr)
            .send();
}

/**
 * Add a group address to the listning list for the object
 * @param string addr   Group address in knx-format
 */
void Object::addReveiveAddr(string addr)
{
    Commando commando(ADD_GROUP_ADDR);
    commando.setParameter(m_nummer)
            .setData(addr)
            .send();
}

/**
 * Delete a group address from the reveive list
 * @param string addr   Group address in knx-format or "all"
 */
void Object::deleteAddr(string addr)
{
    Commando commando(DELETE_GROUP_ADDR);
    commando.setParameter(m_nummer)
            .setData(addr)
            .send();
}

/**
 * Set the Data Point Type with one of the defined standaard DPT
 * Used for interoperability mode
 * @param int dpt
 */
void Object::setDpt(int dpt)
{
    if((dpt > 0 && dpt < 20) || dpt == 200 || dpt == 201)
    {
        m_dpt = dpt;
        return;
    }

    cerr << "obj " << m_nummer << ": Fout dpt type." << endl;
}

/**
 * Set the group object type for raw mode
 * @param int type
 */
void Object::setObjectType(int type)
{
    if((type > 0 && type < 14))
    {
        m_objectType = type;
        return;
    }

    cerr << "obj " << m_nummer << ": Fout object type." << endl;
}

/**
 * Set the configuration flags
 * @param flags
 */
void Object::setComFlags(int flags)
{
    if((flags&0b00100000) != 0)
    {
        m_comFlags = flags;
        return;
    }

    cerr << "obj " << m_nummer << ": Foute comFlag." << endl;
}

/**
 * Set the configuration settings for sending objects
 * @param int sendConfig    Binary
 */
void Object::setSendConfig(int sendConfig)
{
    if((sendConfig & 0b00111000) != 0)
    {
        m_sendConfig = sendConfig;
        return;
    }

    cerr << "obj " << m_nummer << ": Foute sendconfiguratie." << endl;
}

/**
 * Set the configuration settings for receiving objects
 * @param int recvConfig    Binary
 */
void Object::setRecvConfig(int recvConfig)
{
    m_recvConfig = recvConfig;
}

/**
 * Set the send/receive delay
 * Minutes/seconds needs to be configured via send/recv-configuration
 * @param int time
 */
void Object::setTime(int time)
{
    m_time = time;
}

void Object::setConfiguration(void)
{
    Commando commando(SET_OBJECT_CONFIG);
    commando.setParameter(m_nummer);

    commando.setData(m_dpt)
            .setData(m_objectType)
            .setData(m_comFlags)
            .setData(m_sendConfig)
            .setData(m_sendConfig)
            .setData(m_recvConfig)
            .setData(m_time);

    commando.send();
}
