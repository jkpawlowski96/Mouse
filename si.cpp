#include "si.h"

SI::SI()
{
}

Task SI::Call(Position<int> position, SensorData sensorData)
{
    //UpdateMap(position, sensorData);
    return RandomTask(position, sensorData);
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

shared_ptr<Path<int>> SI::FirstUnnown(){
    for(auto& path: mapPaths)
        for(int i=0; i<4;i++)
            if(path.acces[i]==Unnown)
                return make_shared<Path<int>>(path);
    return nullptr;
}

Task SI::RandomTask(Position<int> position, SensorData sensorData){
    int n = rand() % 100;
    if(sensorData.wallDetected || n>=50 ){
        vector<Task> possible;
        switch(position.direction){
            case Up:
                possible = {RotateLeft, RotateDown, RotateRight};
            break;
            case Down:
                possible = {RotateLeft, RotateUp, RotateRight};
            break;
            case Left:
                possible = {RotateUp, RotateDown, RotateRight};
            break;
            case Right:
                possible = {RotateLeft, RotateDown, RotateUp};
            break;
            default:
                return RotateUp;
            break;
        }
        n = rand() % 3;
        return possible[n];
    }
    return Forward;
}

