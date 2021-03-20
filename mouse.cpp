#include "mouse.h"

Mouse::Mouse(Point<int> start, shared_ptr<SI> _si):
    si(_si)
{
    position.localization = doublePoint(start);
}


Position<double> Mouse::GetPosition(){
    return position;
}


void Mouse::Call(SensorData sensorData){
    if(task){
        double _distance = measureDistance(position.localization, task->destination);
        if(_distance>MOVE_STEP)
        {//move
            //Point<double> move = task->
        }
        else{//skip
            position.localization = doublePoint(task->destination);
            task = nullptr;
        }

    }else{

        Position<int> _position = roundPosition(position);

        auto _task = si->Call(_position, sensorData);
        task = make_shared<Task>(_task);
    }
}


