#include "mainwindow.h"
#include "simulator.h"
#include <memory>
#include <QApplication>

int main(int argc, char *argv[])
{
    Simulator simulator;
    //shared_ptr<Simulator> simulator;
    QApplication a(argc, argv);
    MainWindow w(nullptr, make_shared<Simulator>(simulator));
    w.show();
    return a.exec();
}
