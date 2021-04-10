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
/**
 * @brief Application main window
 * 
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Main Window object
     * 
     * @param parent 
     * @param _simulator 
     */
    MainWindow(QWidget *parent = nullptr, shared_ptr<Simulator> _simulator = nullptr);
    /**
     * @brief Destroy the Main Window object
     * 
     */
    ~MainWindow();


private slots:
    void on_mapsComboBox_textActivated(const QString &arg1);
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void simulator_plot();

    void on_speedSlider_valueChanged(int value);

protected:
    /**
     * @brief keyboard key events handles
     * 
     * @param event 
     */
    void keyPressEvent(QKeyEvent *event) override;


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
