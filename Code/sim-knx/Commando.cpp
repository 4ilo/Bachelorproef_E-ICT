//
// Created by olivier on 23/02/17.
//

#include <iostream>
#include "Commando.h"

Commando::Commando(const char *command, bool hasParam, bool hasData)
{
    m_command = command;
    m_hasParam = hasParam;
    m_hasData = hasData;
}


bool Commando::isParamSet(void)
{
    if (m_hasParam == 0)
        return false;

    if (m_parameter != "")
        return true;

    cerr << m_command << ": Parameter is niet verwerkt!" << endl;
    exit(1);

}

bool Commando::isDataSet(void)
{
    if (m_hasData == 0)
        return false;

    if (m_data != "")
        return true;

    cerr << m_command << ": Data is niet verwerkt!" << endl;
    exit(1);
}

void Commando::setParameter(int param)
{
    m_parameter = to_string(param);
}

void Commando::setData(int data)
{
    m_data = to_string(data);
}

bool Commando::send(void)
{
    string output;

    output += m_command;

    if (isParamSet()) {
        output += " (" + m_parameter + ")";
    }

    if (isDataSet()) {
        output += " " + m_data;
    }

    output += '\r';

    cout << output << endl;
}

Response Commando::get(void)
{
    send();
    string data;
    cin >> data;

    m_response.parse(data);

    return m_response;
}

Response Commando::response(void)
{
    if(!m_response.isEmpty())
        return m_response;

    cerr << m_command << ": Nog geen response ontvangen";
}