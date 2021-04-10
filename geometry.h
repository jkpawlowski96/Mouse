#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <vector>
#include <stdlib.h>
#include <memory>

using namespace std;

/**
 * @brief Point representation
 * 
 * @tparam T 
 */
template <typename T>
struct Point{
    T x,y;
    Point(T _x, T _y): x(_x),y(_y){};
    Point(){};
};

/**
 * @brief Mouse direction
 * 
 */
enum Direction{
    Left = 0,
    Up = 1,
    Right = 2,
    Down = 3,
    DirectionUnnown = -1
};

/**
 * @brief Acces to path
 * 
 */
enum Acces{
    Unnown = -1,
    Allowed = 0,
    Forbiden = 1
};

/**
 * @brief Position of mouse
 * 
 * @tparam T 
 */
template <typename T>
struct Position{
    Point<T> localization;
    Direction direction;
    Position(){direction=Up;}
};

/**
 * @brief Line 2D
 * 
 * @tparam T 
 */
template <typename T>
struct Line{
    Point<T> a, b;
    Line(Point<T> _a, Point<T>_b):a(_a), b(_b){}
    Line(){}
};

/**
 * @brief Map path
 * 
 * @tparam T 
 */
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

/**
 * @brief Point equality
 * 
 * @tparam T 
 * @param a 
 * @param b 
 * @return true 
 * @return false 
 */
template<typename T>
bool operator==(Point<T> a, Point<T> b)
{
    if ((a.x==b.x)&&(a.y==b.y))
        return true;
    else
        return false;
}

/**
 * @brief Direction to point
 * 
 * @tparam T 
 * @param a 
 * @param b 
 * @return Direction 
 */
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

/**
 * @brief Inverse direction to point
 * 
 * @tparam T 
 * @param a 
 * @param b 
 * @return Direction 
 */
template<typename T>
Direction operator<<(Point<T> a, Point<T> b){
    return b>>a;
}

/**
 * @brief Point add do point
 * 
 * @tparam T 
 * @param a 
 * @param b 
 * @return Point<T> 
 */
template<typename T>
Point<T> operator+(Point<T> a, Point<T> b)
{
    Point<T> res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    return res;
}

/**
 * @brief Substract point from point
 * 
 * @tparam T 
 * @param a 
 * @param b 
 * @return Point<T> 
 */
template<typename T>
Point<T> operator-(Point<T> a, Point<T> b)
{
    Point<T> res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    return res;
}

/**
 * @brief Devide point by number
 * 
 * @tparam T 
 * @param a 
 * @param dev 
 * @return Point<T> 
 */
template<typename T>
Point<T> operator/(Point<T> a, T dev)
{
    Point<T> res;
    res.x = (T)(a.x/dev);
    res.y = (T)(a.y/dev);
    return res;
}

/**
 * @brief Multiply point by number
 * 
 * @tparam T 
 * @param a 
 * @param mul 
 * @return Point<T> 
 */
template<typename T>
Point<T> operator*(Point<T> a, T mul)
{
    Point<T> res;
    res.x = (T)(a.x*mul);
    res.y = (T)(a.y*mul);
    return res;
}

/**
 * @brief Append acces
 * 
 * @param a 
 * @param b 
 * @return Acces 
 */
Acces operator+(Acces a, Acces b);

/**
 * @brief Point double and int addition
 * 
 * @tparam T 
 * @param i 
 * @param d 
 * @return Point<double> 
 */
template <typename T>
Point<double> operator+(Point<T> i, Point<double> d){
    return Point<double>((double)i.x+d.x, (double)i.y+d.y);
}

/**
 * @brief Distance from point to point
 * 
 * @tparam T 
 * @return T 
 */
template <typename T>
T measureDistance(Point<T>a, Point<T>b){
    Point<T> d = a-b;
    T _d = abs(d.x) + abs(d.y);
    return _d;
}

/**
 * @brief Point of double from point of int
 * 
 * @param p 
 * @return Point<double> 
 */
Point<double> doublePoint(Point<int> p);

/**
 * @brief Distance from double point to int point
 * 
 * @return double 
 */
double measureDistance(Point<double>a, Point<int>b);

/**
 * @brief Point<int> from Point<double>
 * 
 * @param pos 
 * @return Position<int> 
 */
Position<int> roundPosition(Position<double> pos);

/**
 * @brief Point<double> addition
 * 
 * @param a 
 * @param b 
 * @return Point<double> 
 */
Point<double> operator+(Point<double> a, Point<double> b);

/**
 * @brief Rotate direction to left
 * 
 * @param d 
 * @return Direction 
 */
Direction RotateDirectionLeft(Direction d);

/**
 * 
 * @brief Rotate direction to right
 * 
 * @param d 
 * @return Direction 
 */
Direction RotateDirectionRight(Direction d);

/**
 * @brief Rotate direction of 180 degree
 * 
 * @param d 
 * @return Direction 
 */
Direction TurnAroundDirection(Direction d);

/**
 * @brief Get Direction form int representation
 * 
 * @param x 
 * @return Direction 
 */
Direction DirectionFromInt(int x);
#endif // GEOMETRY_H
