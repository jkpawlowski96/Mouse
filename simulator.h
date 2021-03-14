#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <memory>
#include "map.h"
#include "qcustomplot.h"

#define RED QColor(255, 0, 0)
#define GREEN QColor(0, 255, 0)
#define BLACK QColor(0, 0, 0)
#define GRAY QColor(137, 137, 136)

class Simulator
{
public:
    Simulator(QCustomPlot *_plot, string mapFilePath);
    void PlotMap();
    void PlotMouse();
    void PlotSI(); 
private:
    bool SetMap(string mapFilePath);
    QCPGraph* DrawLine(Line<double> line, const QColor color=GRAY, const int width=2);

    shared_ptr<Map> map;
    QCustomPlot *plot;
};

#endif // SIMULATOR_H
