#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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


private:
    Ui::MainWindow *ui;
    QVector<double> xv;
    QVector<double> yv;
};
#endif // MAINWINDOW_H
