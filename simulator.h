#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <memory>
#include "map.h"
#include "geometry.h"
#include "sensor.h"
#include "qcustomplot.h"


#define DEFAULT_FRAMERATE_MS 33

#define RED QColor(255, 0, 0)
#define GREEN QColor(0, 255, 0)
#define BLUE QColor(0, 0, 255)
#define BLACK QColor(0, 0, 0)
#define GRAY QColor(137, 137, 136)
#define YELLOW QColor(255,255,0)

class Simulator
{
public:
    Simulator(QCustomPlot *_plot, string mapFilePath, int _speed, int _si_mode);
    ~Simulator();
    void Start();
    void Stop();
    void Tick();
    void SetSpeed(int _speed);
    quint64 GetTimerElapsed();

private:
    bool SetMap(string mapFilePath);
    void Loop();
    void PlotMap();
    void PlotMouse();
    void PlotSI();

    QCPGraph* DrawLine(Line<double> line, const QColor color=GRAY, const int width=2);
    template<typename T>
    void DrawRectangle(Point<T> point, const QColor color=GRAY, const int width=1, const double margin=0.1, const int step=1);
    bool running;
    shared_ptr<Map> map;
    shared_ptr<Mouse> mouse;
    shared_ptr<SI> si;
    Sensor sensor;
    QCustomPlot *plot;
    shared_ptr<QElapsedTimer> timer;
    quint64 timeElapsed;
    int speed, si_mode;
};

#endif // SIMULATOR_H
