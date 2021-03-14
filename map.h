#ifndef MAP_H
#define MAP_H
#pragma once
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
    Point(T _x, T _y): x(_x),y(_y){};
    Point(){};
};

enum Direction{
    Left = 0,
    Right = 1,
    Up = 2,
    Down = 3,
    DirectionUnnown = -1
};

enum Acces{
    Unnown = -1,
    Allowed = 0,
    Forbiden = 1
};

Acces operator+(Acces a, Acces b);

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
struct Line{
    Point<T> a, b;
    Line(Point<T> _a, Point<T>_b):a(_a), b(_b){}
    Line(){}
};

template <typename T>
struct Path
{
    Point<T> localization;
    Acces acces[4];
    Path(Acces a=Forbiden){acces[0]=a; acces[1]=a; acces[2]=a, acces[3]=a;}
    void append(Path<T> _path){
        for(int i=0;i<4;i++)
            acces[i] = acces[i] + _path.acces[i];
    }
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
