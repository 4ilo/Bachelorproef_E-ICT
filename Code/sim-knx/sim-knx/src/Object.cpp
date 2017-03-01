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
 * Set object data
 * @param int data
 */
void Object::setData(int data)
{
    Commando command(SET_OBJECT_VALUE);

    if(m_isRaw)
    {
        command.changeConfig(SET_OBJECT_DATA);
    }


    command.setParameter(m_nummer)
           .setData(data)
           .send();
}

/**
 * Set object data
 * @param float data
 */
void Object::setData(float data)
{
    Commando command(SET_OBJECT_VALUE);

    if(m_isRaw)
    {
        command.changeConfig(SET_OBJECT_DATA);
    }


    command.setParameter(m_nummer)
           .setData(data)
           .send();
}

/**
 * Set object data voor dimmer value
 * @param int data
 */
void Object::setData(bool onof, int value)
{
    Commando command(SET_OBJECT_VALUE);

    if(m_isRaw)
    {
        cerr << "Object: " << m_nummer << " Functie setData niet ondersteund in raw mode." << endl;
        return;
    }

    if(value > 7)
    {
        cerr << "Object: " << m_nummer << " Value is te groot." << endl;
        return;
    }

    command.setParameter(m_nummer)
           .setData(onof)
           .setData(value)
           .send();
}

/**
 * Get the object data in raw mode
 * @return int
 */
float Object::getData(void)
{
    Commando commando(GET_OBJECT_VALUE);

    if(m_isRaw)
    {
        commando.changeConfig(GET_OBJECT_DATA);
    }

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
        m_dpt = to_string(dpt);
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
        m_objectType = to_string(type);
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
        m_comFlags = to_string(flags);
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
    if((sendConfig & 0b00111000) == 0)
    {
        m_sendConfig = to_string(sendConfig);
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
    m_recvConfig = to_string(recvConfig);
}

/**
 * Set the send/receive delay
 * Minutes/seconds needs to be configured via send/recv-configuration
 * @param int time
 */
void Object::setTime(int time)
{
    m_time = to_string(time);
}

void Object::sendConfiguration(void)
{
    Commando commando(SET_OBJECT_CONFIG);
    commando.setParameter(m_nummer);

    commando.setData(m_dpt)
            .setData(m_objectType)
            .setData(m_comFlags)
            .setData(m_sendConfig)
            .setData(m_recvConfig)
            .setData(m_time);

    commando.send();
}

/**
 * Configure the object in raw mode
 * @param int objectType        Type from defines
 */
void Object::setRaw(int objectType)
{
    m_isRaw = true;
    m_dpt = "0";
    m_objectType = to_string(objectType);
}

/**
 * Configure the object in Interoperability mode
 * @param int dpt       Type from defines
 */
void Object::setInteroperability(int dpt)
{
    m_isRaw = false;
    m_dpt = to_string(dpt);
    m_objectType = "0";
}

/**
 * Send a boolean value to the bus
 * @param value
 */
void Object::sendBool(bool value)
{
    this->setData(value);
    this->send();
}

/**
 * Send a dimming commando to the bus
 * @param status On/Of
 * @param value The dimming value
 */
void Object::sendDim(bool status, int value)
{
    this->setData(status, value);
    this->send();
}

/**
 * Get the value of a boolean object
 * @return bool
 */
bool Object::getBool(void)
{
    return (bool) this->getData();
}

/**
 * Get the data from a dimming object
 * @param status pointer to a status boolean
 * @param value pointer to a value int
 */
void Object::getDim(bool *status, int *value)
{
    Commando commando(GET_OBJECT_VALUE);

    if(m_isRaw)
    {
        cerr << "Object: " << m_nummer << " Functie getDim niet ondersteund in raw mode." << endl;
    }

    commando.setParameter(m_nummer);

    // Er zit een spatie in de response, deze halen we weg
    string data = commando.get().raw();

    // We pakken de waardes, en zetten deze om naar ints
    *status = (bool) stoi(data.substr(0,1));
    *value =  stoi(data.substr(2,1));

}

/**
 * Send a temp for a temperature object
 * @param float temp
 */
void Object::sendTemp(float temp)
{
    this->setData(temp);
    this->send();
}

/**
 * Get the temp from the object
 * @return float temperature
 */
float Object::getTemp(void)
{
    return this->getData();
}

/**
 * Send a percentage to the bus via a object
 * @param value
 */
void Object::sendPercentage(int value)
{
    if(value < 0 || value > 100)
    {
        cerr << "Object: " << m_nummer << " Gelieve een percentage te geven" << endl;
        return;
    }

    this->setData(value);
    this->send();
}

/**
 * Get a percentage from the object
 * @return int percentage
 */
int Object::getPercentage(void)
{
    return (int) this->getData();
}

/**
 * Activate a scene
 * @param int scene-number
 */
void Object::sendScene(int scene)
{
    this->setData(0,scene);
    this->send();
}

/**
 * Send the scene learn command
 * @param int scene-number
 */
void Object::sendSceneLearn(int scene)
{
    this->setData(1,scene);
    this->send();
}
