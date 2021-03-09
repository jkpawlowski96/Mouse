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


template <typename T> 
struct Point{
    T x,y;
};

enum Direction{
    Left = 0,
    Right = 1,
    Up = 2,
    Down = 3
};

template <typename T> 
struct Position{
    Point<T> localization;
    Direction direction;
};

template <typename T>
struct Wall
{
    Point<T> start, stop;
};

template <typename T>
struct Path
{
    Point<T> localization;
    bool allowTop, allowBottom,  allowLeft, allowRight;
};


class Map
{
public:
    Map(string mapFilePath);
    ~Map();
    vector<Path<int>> mapPaths;
    Point<int> mapStart, mapSize;
    vector<Point<int>> mapStop;

private:
    vector<string> SplitText(string text, char delimiter);
    template<typename T>
    Point<T> GetPoint(string text, char delimiter);
    template<typename T>
    vector<Path<T>> GetPaths(string line);
};


#endif // MAP_H
