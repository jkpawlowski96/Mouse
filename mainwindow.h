#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include "simulator.h"
#include <string>
#include <memory>

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


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<double> xv{0.0,1.0};
    QVector<double> yv{1.0,0.0};
    unique_ptr<Simulator> simulator;
    void PlotMap();
    void DrawLine(double x0, double y0, double x1, double y1, int i);
    virtual void paintEvent(QPaintEvent *event);
    void click();
};
#endif // MAINWINDOW_H
