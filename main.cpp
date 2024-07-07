#include<iostream>
#include"process.h"
#include"shortestpath_map.h"
using namespace std;

int main()
{
    cout << "planning start" << endl;
    Process pro;
    pro.planProcess();
    cout << "planning end" << endl;
    ShortEstPath_Map* shortestpath_map = new ShortEstPath_Map();
    shortestpath_map->printinmap();
    shortestpath_map->getshortestpath();
    shortestpath_map->printoutmap();
    return 0;
}