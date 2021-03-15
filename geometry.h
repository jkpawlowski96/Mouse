#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <vector>
#include <stdlib.h>
#include <memory>

using namespace std;

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


template <typename T>
struct Position{
    Point<T> localization;
    Direction direction;
    Position(){direction=Up;}
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
    shared_ptr<Path> next[4];
    Path(Acces a=Forbiden){acces[0]=a; acces[1]=a; acces[2]=a, acces[3]=a;}
    void append(Path<T> _path){
        for(int i=0;i<4;i++){
            acces[i] = acces[i] + _path.acces[i];
            if (_path.next[i]!=nullptr)
                next[i]=_path.next[i];
        }
    }
};


template<typename T>
bool operator==(Point<T> a, Point<T> b)
{
    if ((a.x==b.x)&&(a.y==b.y))
        return true;
    else
        return false;
}


template<typename T>
Direction operator>>(Point<T> a, Point<T> b){
    if(b.x > a.x)
        return Right;
    if(b.x < a.x)
        return Left;
    if(b.y > a.y)
        return Up;
    if(b.y < a.y)
        return Down;
    return DirectionUnnown;
}

template<typename T>
Direction operator<<(Point<T> a, Point<T> b){
    return b>>a;
}

template<typename T>
Point<T> operator+(Point<T> a, Point<T> b)
{
    Point<T> res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    return res;
}

template<typename T>
Point<T> operator-(Point<T> a, Point<T> b)
{
    Point<T> res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    return res;
}

template<typename T>
Point<T> operator/(Point<T> a, T dev)
{
    Point<T> res;
    res.x = (T)(a.x/dev);
    res.y = (T)(a.y/dev);
    return res;
}

template<typename T>
Point<T> operator*(Point<T> a, T mul)
{
    Point<T> res;
    res.x = (T)(a.x*mul);
    res.y = (T)(a.y*mul);
    return res;
}

Acces operator+(Acces a, Acces b);

template <typename T>
Point<double> operator+(Point<T> i, Point<double> d){
    return Point<double>((double)i.x+d.x, (double)i.y+d.y);
}


#endif // GEOMETRY_H
