#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simulator.h"
#include <string>
#include <memory>
#include <sstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_mapsComboBox_textActivated(const QString &arg1);
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void simulator_plot();

    void on_speedSlider_valueChanged(int value);

private:
    void InitSimulator();
    Ui::MainWindow *ui;
    shared_ptr<Simulator> simulator;
    QTimer *timer;

    double time_seconds;

    void PlotMap();
    QCPGraph* DrawLine(double x0, double y0, double x1, double y1);
};
#endif // MAINWINDOW_H
