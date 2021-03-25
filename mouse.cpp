#include "mouse.h"

Mouse::Mouse(Point<int> start, SI *_si):
    si(_si)
{
    position.localization = doublePoint(start);
    position.direction = Up;
    task = TaskUnnown;
}


Position<double> Mouse::GetPosition(){
    return position;
}

void Mouse::SetSpeed(int _speed){
    speed = (double)_speed / 100;
}

void Mouse::Call(shared_ptr<Map> map){
    Position<double> _loc = GetPosition();
    Position<int> loc = roundPosition(_loc);
    SensorData sensorData = sensor.Measure(map, loc);
    if(task>=0){
        if(task==Forward){
            double _distance = measureDistance(position.localization, moveTarget);
            if(_distance>MOVE_STEP)
            {//move
                position.localization = position.localization + move * MOVE_STEP * speed;
            }
            else{//skip
                position.localization = moveTarget;
                task = TaskUnnown;
            }
        }
        if(task==RotateRight){
            position.direction = RotateDirectionRight(position.direction);
            task=TaskUnnown;
        }
        if(task==RotateLeft){
            position.direction= RotateDirectionLeft(position.direction);
            task=TaskUnnown;
        }
        if(task==TurnAround){
            position.direction=RotateDirectionRight(RotateDirectionRight(position.direction));
            task=TaskUnnown;
        }



    }else{
        //Position<int> _position = roundPosition(position);

        task = si->Call(sensorData);
        if(task==Forward){
            move = Point<double>(0.0,0.0);
            cout << "task: move direction: " << position.direction << endl;
            if(position.direction==Up)
                move.y = 1.0;
            if(position.direction==Down)
                move.y = -1.0;
            if(position.direction==Left)
                move.x = -1.0;
            if(position.direction==Right)
                move.x = 1.0;
            moveTarget = position.localization + move;
        }
    }
}


