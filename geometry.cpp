#include "geometry.h"

Acces operator+(Acces a, Acces b){
    if(a==Allowed || b==Allowed)
        return Allowed;
    if(a==Forbiden || b==Forbiden)
        return Forbiden;
    return Unnown;
};

double measureDistance(Point<double>a, Point<int>b){
    auto _b = doublePoint(b);
    return measureDistance<double>(a,_b);
}

Position<int> roundPosition(Position<double> pos){
    Position<int> _pos;
    _pos.localization = Point<int>((int)(pos.localization.x+0.5),(int)(pos.localization.y+0.5));
    _pos.direction = pos.direction;
    return _pos;
}

Point<double> operator+(Point<double> a, Point<double> b)
{
    Point<double> res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    return res;
}

Point<double> doublePoint(Point<int> p){
    return Point<double>(p.x, p.y);
}

