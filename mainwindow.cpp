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


void MainWindow::click()
{
    xv.append(1);
    yv.append(2);
    ui->plot->graph(0)->setData(xv,yv);
    ui->plot->replot();
    ui->plot->update();
}


void MainWindow::on_mapsComboBox_textActivated(const QString &arg1)
{
    QString text = ui->mapsComboBox->currentText();
    QString path = QDir(MAPS_LOCATION).filePath(text);
    simulator->SetMap(path.toStdString());
    PlotMap();
}
/*
 * int i=1;
    QPen pen;
    ui->plot->addGraph();
    pen.setColor(QColor(255, 0, 0));
    ui->plot->graph(1)->setPen(pen);
    ui->plot->graph(1)->setLineStyle((QCPGraph::LineStyle)i);
    ui->plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    QVector<double> x{0.0},y{0.0};
    Point p = simulator->map->mapSize;
    x.push_back((double)p.x);
    y.push_back((double)p.y);

    ui->plot->graph(1)->setData({0.0, (double)p.x},{0.0,(double)p.y});
 *
 */
void MainWindow::PlotMap(){

}

void MainWindow::DrawLine(double x0, double y0, double x1, double y1, int i){
        QPen pen;
        ui->plot->addGraph();
        pen.setColor(QColor(255, 0, 0));
        ui->plot->graph(i)->setPen(pen);
        ui->plot->graph(i)->setLineStyle((QCPGraph::LineStyle)1);
        ui->plot->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
        QVector<double> x{x0,x1},y{y0,y1};
        xv.append(x0);
        yv.append(y0);
        ui->plot->graph(i)->setData(xv,yv);

}
int ii =2.0;
void MainWindow::on_pushButton_clicked()
{
    ii = ii + 1.0;
    DrawLine(ii,0.0,10.0,10.0,0);
    //DrawLine(3.0,10.0,10.0,0.0,1);
    ui->plot->replot();
    ui->plot->update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.setBrush(Qt::DiagCrossPattern);


    QPen pen;

    pen.setColor(Qt::green);
    pen.setWidth(5);

    painter.setPen(pen);
    painter.drawRect(QRect(80,120,200,100));
}
