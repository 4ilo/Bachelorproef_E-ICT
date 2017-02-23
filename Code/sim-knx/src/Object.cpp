//
// Created by olivier on 23/02/17.
//

#include "../inc/Object.h"

Object::Object(int nummer)
{
    if(nummer > 0)
        m_nummer = nummer;
}

void Object::setData(int data)
{
    Commando command(SET_OBJECT_DATA);
    command.setParameter(m_nummer);
    command.setData(data);

    command.send();
}

int Object::getData(void)
{
    Commando commando(GET_OBJECT_DATA);
    commando.setParameter(m_nummer);

    return commando.get().data();
}

void Object::send(void)
{
    Commando commando(SEND_GROUP_TELEGRAM);
    commando.setParameter(m_nummer);
    commando.send();
}

void Object::setSendingAddr(string addr)
{
    Commando commando(SET_SENDING_GROUP_ADDR);
    commando.setParameter(m_nummer);
    commando.setData(addr);
    commando.send();
}
