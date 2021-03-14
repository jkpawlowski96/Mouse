#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <memory>
#include "map.h"
#include "geometry.h"
#include "sensor.hpp"
#include "qcustomplot.h"

#define RED QColor(255, 0, 0)
#define GREEN QColor(0, 255, 0)
#define BLUE QColor(0, 0, 255)
#define BLACK QColor(0, 0, 0)
#define GRAY QColor(137, 137, 136)
#define YELLOW QColor(255,255,0)

class Simulator
{
public:
    Simulator(QCustomPlot *_plot, string mapFilePath);
private:
    bool SetMap(string mapFilePath);

    void PlotMap();
    void PlotMouse();
    void PlotSI();

    QCPGraph* DrawLine(Line<double> line, const QColor color=GRAY, const int width=2);
    template<typename T>
    void DrawRectangle(Point<T> point, const QColor color=GRAY, const int width=1, const double margin=0.1, const int step=1);

    shared_ptr<Map> map;
    shared_ptr<Mouse> mouse;
    Sensor sensor;
    QCustomPlot *plot;
};

#endif // SIMULATOR_H
