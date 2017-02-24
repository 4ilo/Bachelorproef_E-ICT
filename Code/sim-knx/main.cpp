#include <iostream>
#include "inc/Object.h"

//#define DEBUG

int main()
{
    Object object1(1);

    object1.setData(50);
    object1.setSendingAddr("1/2/3");
    object1.send();
    cout << object1.getData();

}