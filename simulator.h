#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <memory>
#include "map.h"
#include "qcustomplot.h"


class Simulator
{
public:
    Simulator(QCustomPlot *_plot);
    bool SetMap(string mathFilePath);

    shared_ptr<Map> map;
    shared_ptr<QCustomPlot> plot;

private:

};

#endif // SIMULATOR_H
