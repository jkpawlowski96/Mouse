#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot->xAxis->setVisible(false);
    ui->plot->yAxis->setVisible(false);

    //maps
    auto mapFiles = GetMapFiles();
    ui->mapsComboBox->addItems(mapFiles);
    //simulator

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startButton_clicked()
{
    xv.append(0);
    yv.append(0);
    xv.append(1);
    yv.append(2);
    ui->plot->graph(0)->setData(xv,yv);
    ui->plot->replot();
    ui->plot->update();
}

void MainWindow::on_mapsComboBox_activated(const QString &arg1)
{
}

void MainWindow::on_mapsComboBox_textActivated(const QString &arg1)
{
    QString text = ui->mapsComboBox->currentText();
    QString path = QDir(MAPS_LOCATION).filePath(text);
    simulator.SetMap(path.toStdString());
}
