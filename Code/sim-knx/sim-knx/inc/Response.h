//
// Created by olivier on 23/02/17.
//

#ifndef SIM_KNX_RESPONSE_H
#define SIM_KNX_RESPONSE_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
 * Classe voor het verwerken van responses van de sim-knx
 */
class Response {

private:
    string m_rawData;
    int HexToInt(string data);

public:
    Response(string data = "");

    void parse(string);
    string raw(void);
    float data(void);
    bool mode(void);

    bool isEmpty(void);

};


#endif //SIM_KNX_RESPONSE_H
