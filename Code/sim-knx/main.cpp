#include <iostream>
#include "Commando.h"

#define GET_PHY_ADDR "dag"
#define SET_PHY_ADDR "das", 0, 1
#define SET_OBJECT_DATA "ods", 1, 1

int main()
{
    Commando command(SET_OBJECT_DATA);
    Commando command2(GET_PHY_ADDR);

    command.setParameter(0);
    command.setData(0b00000001);
    command.send();

    cout << command2.get().data() << endl;
}