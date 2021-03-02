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
    void Draw(QCustomPlot plot);

private:
    Point GetPoint(string text, string delimiter);
    vector<string> SplitText(string text, string delimiter);
    Path GetPath(string line);
};


#endif // MAP_H
