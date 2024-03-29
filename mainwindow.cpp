#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"


MainWindow::MainWindow(QWidget *parent, shared_ptr<Simulator> _simulator)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , simulator(_simulator)
{
    ui->setupUi(this);
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
    if(ui->humanButton->isChecked())
        si_mode = -1;
    if(ui->siButton->isChecked())
        si_mode = 0;
    if(ui->expanderButton->isChecked())
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
    if(!simulator->isRunning())
        InitSimulator();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
     if(event->key() == Qt::Key_Up)
     {
         simulator->ControllDirection(Up);
     }
     if(event->key() == Qt::Key_Down)
     {
         simulator->ControllDirection(Down);
     }
     if(event->key() == Qt::Key_Left)
     {
         simulator->ControllDirection(Left);
     }
     if(event->key() == Qt::Key_Right)
     {
         simulator->ControllDirection(Right);
     }
}

void MainWindow::on_startButton_clicked()
{
    InitSimulator();
    simulator->Start();
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(simulator_plot()));
    timer->start(33); //time specified in ms
}

void MainWindow::simulator_plot(){
    simulator->Tick();

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
    timer->stop();
    InitSimulator();
}

void MainWindow::on_speedSlider_valueChanged(int value)
{
    if(simulator)
        simulator->SetSpeed(value);
}
