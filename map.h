#ifndef MAP_H
#define MAP_H
#include <stdlib.h>
#include <string>
#include "qcustomplot.h"
#include "geometry.h"
#include <memory>

using namespace std;

#define MAP_SIZE_SIGN "size"
#define MAP_START_SIGN "start"
#define MAP_STOP_SIGN "stop"
#define MAP_PATHS_SIGN "paths"


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
    template<typename T>
    shared_ptr<Path<T>> FindPath(Point<T> localization);
    template<typename T>
    vector<shared_ptr<Path<T>>> FindPaths(vector<Point<T>> localizations);
    void InsertPaths(vector<Path<int>> newPaths);
    template<typename T>
    vector<Point<T>> FindNearLocalizations(Point<T> localization);
};

vector<Line<double>> GetPathLines(Path<int> path);

#endif // MAP_H
