#include "si.h"

SI::SI()
{
}

Task SI::Call(SensorData sensorData)
{
    return Logic(sensorData);
}

Task SI::Logic(SensorData sensorData){
    return RandomTask(sensorData);
}

Task SI::RandomTask(SensorData sensorData){
    int n = rand() % 100;
    if(sensorData.wallDetected || n>=50 ){
        vector<Task> possible = {RotateLeft, RotateRight, TurnAround};
        n = rand() % 3;
        return possible[n];
    }
    return Forward;
}

Task operator>(Direction a, Direction b){
    int d = a-b;
    if(d==3)
        return RotateRight;
    if(d == 2)
        return TurnAround;
    if(d == 1)
        return RotateLeft;
    if(d == 0)
        return Forward;
    if(d == -1)
        return RotateRight;
    if(d == -2)
        return TurnAround;
    if(d == -3)
        return RotateLeft;
    return RotateLeft;
}

