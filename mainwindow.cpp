#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->plot->addGraph();
    //ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    //ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot->xAxis->setVisible(false);
    ui->plot->yAxis->setVisible(false);

    //maps
    auto mapFiles = GetMapFiles();
    if(mapFiles.size()>0)
    {
        ui->mapsComboBox->addItems(mapFiles);
    }

    InitSimulator();
}

void MainWindow::InitSimulator(){
    //simulator
    QString text = ui->mapsComboBox->currentText();
    QString path = QDir(MAPS_LOCATION).filePath(text);
    simulator.reset(new Simulator(ui->plot, path.toStdString()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_mapsComboBox_textActivated(const QString &arg1)
{
    //QString text = ui->mapsComboBox->currentText();
    //QString path = QDir(MAPS_LOCATION).filePath(text);
    //simulator->SetMap(path.toStdString());
}



void MainWindow::on_startButton_clicked()
{
    InitSimulator();
}


void MainWindow::on_stopButton_clicked()
{
    ui->plot->clearGraphs();
    ui->plot->replot();
}
