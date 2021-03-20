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
    //plot
    ui->plot->clearGraphs();
    ui->plot->replot();
    //simulator
    QString text = ui->mapsComboBox->currentText();
    QString path = QDir(MAPS_LOCATION).filePath(text);

    int si_mode = 0;
    if(ui->siButton->isChecked())
        si_mode = 0;
    if(ui->humanButton->isChecked())
        si_mode = 1;

    simulator = make_shared<Simulator>(ui->plot, path.toStdString(), ui->speedSlider->value(), si_mode);
    time_seconds = 0.0;
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
    InitSimulator();
}


void MainWindow::on_startButton_clicked()
{
    simulator->Start();
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(simulator_plot()));
    timer->start(33); //time specified in ms
}

void MainWindow::simulator_plot(){
    //simulator->Tick();

    //timer
    quint64 _miliseconds = simulator->GetTimerElapsed();
    double _seconds = ((double)_miliseconds / 1000);
    _seconds = _seconds * ui->speedSlider->value() / 100;
    time_seconds = time_seconds + _seconds;
    std::ostringstream out;
    out.precision(2);
    out << std::fixed << time_seconds;
    string lcdText = out.str();
    QString qlcdText = QString::fromStdString(lcdText);
    ui->lcdTimer->display(qlcdText);
}

void MainWindow::on_stopButton_clicked()
{
    //simulator->Stop();
    timer->stop();
    InitSimulator();
}

void MainWindow::on_speedSlider_valueChanged(int value)
{
    if(simulator)
        simulator->SetSpeed(value);
}
