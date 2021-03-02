#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simulator.h"
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addPoint(float x, float y);
    void plot();

private slots:
    void on_startButton_clicked();

    void on_mapsComboBox_activated(const QString &arg1);

    void on_mapsComboBox_textActivated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QVector<double> xv;
    QVector<double> yv;
    Simulator simulator;

};
#endif // MAINWINDOW_H
