#include "geometry.h"

Acces operator+(Acces a, Acces b){
    if(a==Allowed || b==Allowed)
        return Allowed;
    if(a==Forbiden || b==Forbiden)
        return Forbiden;
    return Unnown;
};
