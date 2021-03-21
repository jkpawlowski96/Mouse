#ifndef SENSOR_H
#define SENSOR_H
#include "geometry.h"
#include "map.h"
#include "mouse.h"
#include <memory>
#include "sensor_data.h"

class Sensor{
    public:
        SensorData Measure(shared_ptr<Map> map, shared_ptr<Mouse> mouse){
            SensorData res;
            Position<double> loc = mouse->GetPosition();
            Position<int> _loc = roundPosition(loc);
            auto path = map->FindPathConst(_loc.localization);
            Direction d = loc.direction;
            if(path.acces[d]==Forbiden)
                res.wallDetected = true;
            else
                res.wallDetected = false;
            return res;
        }

};

#endif // SENSOR_H
