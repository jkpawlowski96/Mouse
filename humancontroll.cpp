#include "humancontroll.h"

HumanControll::HumanControll(Direction initDirection):
    mouseDirection(initDirection), nextDirection(initDirection)
{}

Task HumanControll::Logic(SensorData sensorData){
    if(nextDirection == DirectionUnnown)
        return TaskUnnown;
    if(nextDirection == mouseDirection)
        if(!sensorData.wallDetected){
           nextDirection = DirectionUnnown;
           return Forward;
        }
        else
           return TaskUnnown;
    else{
        Task task = mouseDirection > nextDirection;
        mouseDirection = nextDirection;
        return task;
    }
}

void HumanControll::SetDirection(Direction d){
    nextDirection = d;
}
