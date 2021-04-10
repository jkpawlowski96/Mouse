#ifndef SENSOR_H
#define SENSOR_H
#include "geometry.h"
#include "map.h"
#include <memory>
#include "sensor_data.h"

/**
 * @brief Sensor device for wall detection
 * 
 */
class Sensor{
    public:
        /**
         * @brief Measure distance to wall to make detection
         * 
         * @param map 
         * @param loc 
         * @return SensorData 
         */
        SensorData Measure(shared_ptr<Map> map, Position<int> loc){
            SensorData res;
            auto path = map->FindPathConst(loc.localization);
            Direction d = loc.direction;
            if(path.acces[d]==Forbiden)
                res.wallDetected = true;
            else
                res.wallDetected = false;
            return res;
        }

};

#endif // SENSOR_H
