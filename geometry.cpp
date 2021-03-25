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

Direction RotateDirectionLeft(Direction d){
    if(d==Left)
        return Down;
    if(d==Up)
        return Left;
    if(d==Right)
        return Up;
    if(d==Down)
        return Right;
    return DirectionUnnown;
}

Direction RotateDirectionRight(Direction d){
    if(d==Left)
        return Up;
    if(d==Up)
        return Right;
    if(d==Right)
        return Down;
    if(d==Down)
        return Left;
    return DirectionUnnown;
}
Direction TurnAroundDirection(Direction d){
    return RotateDirectionRight(RotateDirectionRight(d));
}

Direction DirectionFromInt(int x){
    if(x==0)
        return Left;
    if(x==1)
        return Up;
    if(x==2)
        return Right;
    if(x==3)
        return Down;
}



