#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <memory>
#include "map.h"
#include "mouse.h"
#include "geometry.h"
#include "qcustomplot.h"
#include "expander.h"
#include "humancontroll.h"
#include <iostream>

#define DEFAULT_FRAMERATE_MS 50

#define RED QColor(255, 0, 0)
#define GREEN QColor(0, 255, 0)
#define BLUE QColor(0, 0, 255)
#define BLACK QColor(0, 0, 0)
#define GRAY QColor(137, 137, 136)
#define YELLOW QColor(255,255,0)

/**
 * @brief Simulator of micromouse experiment environment
 * 
 */
class Simulator
{
public:
    /**
     * @brief Construct a new Simulator object
     * 
     * @param _plot 
     * @param mapFilePath 
     * @param _speed 
     * @param _si_mode 
     */
    Simulator(QCustomPlot *_plot, string mapFilePath, int _speed, int _si_mode);
    /**
     * @brief Construct a new Simulator object
     * 
     */
    Simulator(){};
    /**
     * @brief Destroy the Simulator object
     * 
     */
    ~Simulator();
    /**
     * @brief Start simulation
     * 
     */
    void Start();
    /**
     * @brief Stop simulation
     * 
     */
    void Stop();
    /**
     * @brief Single tick (step) of simulation
     * 
     */
    void Tick();
    /**
     * @brief Set the Speed object
     * 
     * @param _speed 
     */
    void SetSpeed(int _speed);
    /**
     * @brief Get the Timer Elapsed object
     * 
     * @return quint64 
     */
    quint64 GetTimerElapsed();
    /**
     * @brief Human controll set direction
     * 
     * @param d 
     */
    void ControllDirection(Direction d);
    /**
     * @brief Is simulation running?
     * 
     * @return true 
     * @return false 
     */
    bool isRunning(){return running;}

private:
    bool SetMap(string mapFilePath);
    void Loop();
    void PlotMap();
    void PlotMouse(bool init=false);
    void PlotSI();
    void Finish();

    QCPGraph* DrawLine(Line<double> line, const QColor color=GRAY, const int width=2);
    QCPGraph* DrawMouseCircle(QVector<double>&x, QVector<double>&y, const QColor color,const int width);
    QCPGraph* DrawMouseLine(QVector<double>&x, QVector<double>&y, const QColor color,const int width);

    template<typename T>
    vector<QCPGraph*> DrawRectangle(Point<T> point, const QColor color=GRAY, const int width=1, const double margin=0.1, const int step=1);
    bool running;
    shared_ptr<Map> map;
    shared_ptr<Mouse> mouse;

    SI * si;
    HumanControll *controll;
    QCustomPlot *plot;
    shared_ptr<QElapsedTimer> timer;
    quint64 timeElapsed;
    int si_mode;

    QVector<double> mouseBodyX, mouseBodyY;
    QVector<double> mouseHeadX, mouseHeadY;
    QVector<double> mouseTailX, mouseTailY;
    QCPGraph *mouseBody, *mouseHead, *mouseTail;
};

#endif // SIMULATOR_H
