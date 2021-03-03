#ifndef MAP_H
#define MAP_H
#include <stdlib.h>
#include <string>
#include "qcustomplot.h"

using namespace std;

#define MAP_SIZE_SIGN "size"
#define MAP_START_SIGN "start"
#define MAP_STOP_SIGN "stop"
#define MAP_PATHS_SIGN "paths"

struct Point{
    int x,y;
};

struct Path{
    Point start, stop;
};

class Map
{
public:
    Map(string mapFilePath);
    ~Map();
    vector<Path> mapPaths;
    Point mapStart, mapSize;
    vector<Point> mapStop;
private:


    Point GetPoint(string text, char delimiter);
    vector<string> SplitText(string text, char delimiter);
    Path GetPath(string line);
};


#endif // MAP_H
