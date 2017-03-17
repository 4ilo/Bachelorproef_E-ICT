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
Commando::Commando(const char *command, int hasParam, int hasData)
{
    m_command = command;
    m_hasParam = hasParam;
    m_hasData = hasData;

    m_uart = new Uart(SIM_KNX_UART,SIM_KNX_BAUD,0);
}

/**
 * Command destructor
 */
Commando::~Commando()
{
    delete m_uart;
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
 * Add to the parameter property
 * @param int param
 */
Commando& Commando::setParameter(int param)
{
    m_parameter += to_string(param) + " ";
    return *this;
}

/**
 * Add to the data property with a integer
 * @param int data
 */
Commando& Commando::setData(int data)
{
    m_data += to_string(data) + " ";
    return *this;
}

/**
 * Add to the data property with a integer
 * @param int data
 */
Commando& Commando::setData(float data)
{
    m_data += to_string(data) + " ";
    return *this;
}

/**
 * Add to the data property with a string (knx group addr => 1/2/3)
 * @param string data
 */
Commando& Commando::setData(string data)
{
    m_data += data + " ";
    return *this;
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

    output += "\n\r";

    m_uart->writeData(output);
}

/**
 * Send the command and wait for the response
 * @return Response
 */
Response Commando::get(void)
{
    send();             // Send the request

    string data;
    data = m_uart->readData(1);     // Read data with 1s timeout
    m_response.parse(data);

    return m_response;
}

Response Commando::get(string testing)
{
#ifdef DEBUG
    send();
    m_response.parse(testing);

    return m_response;
#else
    cerr << "Gebruik normaal get commando als niet in debug mode!" << endl;
    exit(3);
#endif
}

void Commando::changeConfig(const char *command, int hasParam, int hasData)
{
    m_command = command;
    m_hasParam = hasParam;
    m_hasData = hasData;
}
