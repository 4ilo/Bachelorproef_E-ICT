//
// Created by olivier on 23/02/17.
//

#include "../inc/Commando.h"

/**
 * Commando constructor dient ingevuld te worden met 1 van de defines in commands.h
 * @param const char * command
 * @param bool hasParam
 * @param bool hasData
 */
Commando::Commando(const char *command, bool hasParam, bool hasData)
{
    m_command = command;
    m_hasParam = hasParam;
    m_hasData = hasData;
}

/**
 * Check if parameters are required and if filled
 * @return bool
 */
bool Commando::isParamSet(void)
{
    if (m_hasParam == 0)
        return false;

    if (m_parameter != "")
        return true;

    cerr << m_command << ": Parameter is niet verwerkt!" << endl;
    exit(1);

}

/**
 * Check if data is required and filled
 * @return bool
 */
bool Commando::isDataSet(void)
{
    if (m_hasData == 0)
        return false;

    if (m_data != "")
        return true;

    cerr << m_command << ": Data is niet verwerkt!" << endl;
    exit(1);
}

/**
 * Set the parameter property
 * @param int param
 */
void Commando::setParameter(int param)
{
    m_parameter = to_string(param);
}

/**
 * Set the data property with a integer
 * @param int data
 */
void Commando::setData(int data)
{
    m_data = to_string(data);
}

/**
 * Set the data property with a string (knx group addr => 1/2/3)
 * @param string data
 */
void Commando::setData(string data)
{
    m_data = data;
}

/**
 * Send the command
 */
void Commando::send(void)
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

/**
 * Send the command and wait for the response
 * @return Response
 */
Response Commando::get(void)
{
    send();
    string data;
    cin >> data;

    m_response.parse(data);

    return m_response;
}