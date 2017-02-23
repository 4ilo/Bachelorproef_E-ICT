//
// Created by olivier on 23/02/17.
//

#include "../inc/Response.h"

/**
 * Constructor
 * @param data
 */
Response::Response(string data)
{
    if(data != "")
    {
        m_rawData = data;
    }
}

/**
 * Parse stringdata into object
 * @param string data
 */
void Response::parse(string data)
{
    if(data != "")
    {
        m_rawData = data;
    }
}

/**
 * Check if response is empty
 * @return bool
 */
bool Response::isEmpty(void)
{
    if(m_rawData == "")
        return true;

    return false;
}

/**
 * Return the raw output received from the bus
 * @return string
 */
string Response::raw(void)
{
    return m_rawData;
}

/**
 * Convert hexadecimal string into integer
 * @param string data
 * @return int
 */
int Response::toInt(string data)
{
    stringstream stream;
    int intval;

    stream << hex << data;
    stream >> intval;

    return intval;
}

/**
 * Get the integer representation of the response data
 * @return int
 */
int Response::data()
{
    if(m_rawData.front() == '$')
    {
        string substr = m_rawData.substr(1);
        return toInt(substr);
    }
}
