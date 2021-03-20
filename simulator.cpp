#include "simulator.h"

Simulator::Simulator(QCustomPlot *_plot, string mapFilePath, int _speed):
    speed(_speed)
{
    this->plot = _plot;
    SetMap(mapFilePath);
    mouse = make_shared<Mouse>(map->mapStart);
    PlotMap();
    PlotMouse();
    plot->replot();
    plot->update();
}

void Simulator::SetSpeed(int _speed){
    speed=speed;
}

Simulator::~Simulator(){
}

void Simulator::Start(){
    running = true;
    timer = make_shared<QElapsedTimer>();
    timer->start();
}

void Simulator::Stop(){
    //simMutex.lock();
    //closeThread = true;
    //simMutex.unlock();
    //simThread->join();
    timeElapsed = timer->elapsed();
    running = false;
}

void Simulator::Tick(){
    PlotMouse();
    plot->replot();
    plot->update();
}

quint64 Simulator::GetTimerElapsed(){
    if (running){
        auto _res = timer->elapsed();
        timer->restart();
        return _res;
    }
    else
        return 0;
}

bool Simulator::SetMap(string mapFilePath){
    this->map = make_shared<Map>(mapFilePath);
    return true;
}

QCPGraph* Simulator::DrawLine(Line<double> line, const QColor color,const int width){
        QPen pen;
        auto graph = plot->addGraph();
        pen.setColor(color);
        pen.setWidth(width);
        graph->setPen(pen);
        graph->setLineStyle((QCPGraph::LineStyle)1);
        //graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
        //ui->plot->graph(i)->setPen(pen);
        //ui->plot->graph(i)->setLineStyle((QCPGraph::LineStyle)1);
        //ui->plot->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
        QVector<double> x{line.a.x,line.b.x},y{line.a.y,line.b.y};

        graph->setData(x,y);
        return graph;
}

template<typename T>
void Simulator::DrawRectangle(Point<T> point, const QColor color, const int width, const double margin, const int step){
        Point<double> p00(point.x+margin, point.y+margin);
        Point<double> p11(point.x+step-margin, point.y+step-margin);
        Point<double> p01(point.x+margin, point.y+step-margin);
        Point<double> p10(point.x+step-margin, point.y+margin);
        DrawLine(Line<double>(p00,p01),color,width);
        DrawLine(Line<double>(p01,p11),color,width);
        DrawLine(Line<double>(p11,p10),color,width);
        DrawLine(Line<double>(p10,p00),color,width);
}

void Simulator::PlotMap(){
    // borders
    plot->yAxis->setRange(-1,map->mapSize.y+1);
    plot->xAxis->setRange(-1,map->mapSize.x+1);
    plot->xAxis->setScaleRatio(plot->xAxis, 1.0);

    DrawLine(Line<double>(Point<double>(0,0),Point<double>(0,map->mapSize.y)),GRAY);
    DrawLine(Line<double>(Point<double>(0,map->mapSize.y),Point<double>(map->mapSize.x,map->mapSize.y)),GRAY);
    DrawLine(Line<double>(Point<double>(map->mapSize.x,map->mapSize.y),Point<double>(map->mapSize.x, 0)),GRAY);
    DrawLine(Line<double>(Point<double>(map->mapSize.x,0),Point<double>(0,0)),GRAY);


    // paths
    for(auto const& path: map->mapPaths){
        vector<Line<double>> lines = GetPathLines(path);
        for(auto const& line: lines){
            DrawLine(line, BLACK);
        }
    }

    DrawRectangle<int>(map->mapStart, GRAY, 1, 0.2);
    for(auto const& stop: map->mapStop)
        DrawRectangle<int>(stop, GREEN, 1, 0.1);

}

void Simulator::PlotMouse(){
    auto pos = mouse->GetPosition();
    Point<double> head;
    DrawRectangle<int>(pos.localization, BLUE, 2, 0.3);

    switch(pos.direction){
        case Up:
            head = pos.localization + Point<double>(0.5, 0.8);
            break;
        case Down:
            head = pos.localization + Point<double>(0.5, 0.2);
            break;
        case Left:
            head = pos.localization + Point<double>(0.2, 0.5);
            break;
        case Right:
            head = pos.localization + Point<double>(0.8, 0.5);
            break;
        default:
            break;
    }
    DrawRectangle<double>(head, YELLOW, 1, 0.1, 0);
}
