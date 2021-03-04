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


    //simulator
    simulator.reset(new Simulator());

    //maps
    auto mapFiles = GetMapFiles();
    if(mapFiles.size()>0)
    {
        ui->mapsComboBox->addItems(mapFiles);
        on_mapsComboBox_textActivated("");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_mapsComboBox_textActivated(const QString &arg1)
{
    QString text = ui->mapsComboBox->currentText();
    QString path = QDir(MAPS_LOCATION).filePath(text);
    simulator->SetMap(path.toStdString());
    PlotMap();
}

void MainWindow::PlotMap(){
    shared_ptr<Map> map(simulator->map);
    ui->plot->yAxis->setRange(-1,map->mapSize.y+1);
    ui->plot->xAxis->setRange(-1,map->mapSize.x+1);

    DrawLine(0,0,0,map->mapSize.y);
    DrawLine(0,map->mapSize.y,map->mapSize.x,map->mapSize.y);
    DrawLine(map->mapSize.x,map->mapSize.y, map->mapSize.x, 0);
    DrawLine(map->mapSize.x,0,0,0);


    ui->plot->replot();
    ui->plot->update();

}

QCPGraph* MainWindow::DrawLine(double x0, double y0, double x1, double y1){
        QPen pen;
        auto graph = ui->plot->addGraph();
        pen.setColor(QColor(255, 0, 0));
        graph->setPen(pen);
        graph->setLineStyle((QCPGraph::LineStyle)1);
        //graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
        //ui->plot->graph(i)->setPen(pen);
        //ui->plot->graph(i)->setLineStyle((QCPGraph::LineStyle)1);
        //ui->plot->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
        QVector<double> x{x0,x1},y{y0,y1};
        //dataX.push_back(x);
        //dataY.push_back(y);
        //ui->plot->graph(i)->setData(x,y);
        graph->setData(x,y);
        return graph;
}

void MainWindow::on_startButton_clicked()
{
    DrawLine(0.0,0.0,10.0,10.0);
    ui->plot->replot();
    ui->plot->update();
}


void MainWindow::on_stopButton_clicked()
{
    ui->plot->clearGraphs();
    ui->plot->replot();
}
