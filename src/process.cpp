#include<iostream>
#include "process.h"
using namespace std;

void Process::planProcess()
{
    cout << "This is a planning process" << endl;
    my_map.mapInfo();
    cout << "planning success!" << endl;
}