#include "mainwindow.h"
#include "simulator.h"
#include <memory>
#include <QApplication>

int main(int argc, char *argv[])
{
    shared_ptr<Simulator> simulator = make_shared<Simulator>();
    QApplication a(argc, argv);
    MainWindow w(nullptr, simulator);
    w.show();
    return a.exec();
}
