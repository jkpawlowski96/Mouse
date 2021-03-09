#include "simulator.h"

Simulator::Simulator(QCustomPlot *_plot)
{
    this->plot = make_shared<QCustomPlot>(_plot);
}

bool Simulator::SetMap(string mapFilePath){
    this->map = make_shared<Map>(mapFilePath);
    return true;
}
