#include "si.h"

SI::SI()
{
}

Task SI::Call(SensorData sensorData)
{
    //UpdateMap(position, sensorData);
    return Logic(sensorData);
}

Task SI::Logic(SensorData sensorData){
    return RandomTask(sensorData);
}


void SI::UpdateMap(Position<int> position, SensorData sensorData){
    Path<int> newPath;
    newPath.localization = position.localization;
    if(sensorData.wallDetected)
    {
        newPath.acces[position.direction] = Forbiden;
    }
    else
    {
        newPath.acces[position.direction] = Allowed;
    }
    vector<Path<int>> newPaths = {newPath};
    InsertPaths(newPaths);
    auto path = FindPath<int>(position.localization);
    UpdateConnections(path);
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

