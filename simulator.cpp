#include "simulator.h"

Simulator::Simulator(QCustomPlot *_plot, string mapFilePath, int _speed, int _si_mode):
    si_mode(_si_mode)
{
    //assing plot
    this->plot = _plot;
    //map
    SetMap(mapFilePath);
    //si
    if(_si_mode==0)
        si = new SI();
    //si
    if(_si_mode==1){
        //SI *ex = new Expander();
        si = new Expander();

    }
        //Expander ex;
    //mouse
    mouse = make_shared<Mouse>(map->mapStart, si);
    mouse->SetSpeed(_speed);
    //plot
    PlotMap();
    PlotMouse(true);
    plot->replot();
    plot->update();
}

void Simulator::SetSpeed(int _speed){
    mouse->SetSpeed(_speed);
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
    if(running){
        if (mouse->Call(map))
            Finish();
        PlotMouse();
        plot->replot();
        plot->update();
    }
}

void Simulator::Finish(){
    timeElapsed = timer->elapsed();
    running = false;
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

QCPGraph* Simulator::DrawMouseCircle(QVector<double>&x, QVector<double>&y, const QColor color,const int width){
    QPen pen;
    auto graph = plot->addGraph();
    pen.setColor(color);
    pen.setWidth(width);
    graph->setPen(pen);
    graph->setScatterStyle(QCPScatterStyle::ssCircle);
    //ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    graph->setLineStyle((QCPGraph::LineStyle)0);
    graph->setData(x,y);
    return graph;
}

QCPGraph* Simulator::DrawMouseLine(QVector<double>&x, QVector<double>&y, const QColor color,const int width){
    QPen pen;
    auto graph = plot->addGraph();
    pen.setColor(color);
    pen.setWidth(width);
    graph->setPen(pen);
    graph->setLineStyle((QCPGraph::LineStyle)1);
    graph->setData(x,y);
    return graph;
}

template<typename T>
vector<QCPGraph*> Simulator::DrawRectangle(Point<T> point, const QColor color, const int width, const double margin, const int step){
        vector<QCPGraph*> res;
        Point<double> p00(point.x+margin, point.y+margin);
        Point<double> p11(point.x+step-margin, point.y+step-margin);
        Point<double> p01(point.x+margin, point.y+step-margin);
        Point<double> p10(point.x+step-margin, point.y+margin);
        res.push_back(DrawLine(Line<double>(p00,p01),color,width));
        res.push_back(DrawLine(Line<double>(p01,p11),color,width));
        res.push_back(DrawLine(Line<double>(p11,p10),color,width));
        res.push_back(DrawLine(Line<double>(p10,p00),color,width));
        return res;
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

void Simulator::PlotMouse(bool init){
    /*for(auto graph: bodyGraphs)
        plot->removeGraph(graph);
    for(auto graph: headGraphs)
        plot->removeGraph(graph);
    auto pos = mouse->GetPosition();
    Point<double> head;
    bodyGraphs = DrawRectangle<double>(pos.localization, BLUE, 2, 0.3);

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
    //headGraphs = DrawRectangle<double>(head, YELLOW, 1, 0.1, 0);
    */
    mouseBodyX.clear();
    mouseBodyY.clear();
    mouseHeadX.clear();
    mouseHeadY.clear();
    mouseTailX.clear();
    mouseTailY.clear();
    auto pos = mouse->GetPosition();
    mouseBodyX.append(pos.localization.x+0.5);
    mouseBodyY.append(pos.localization.y+0.5);
    double eye_x0 = pos.localization.x + 0.3;
    double eye_x1 = pos.localization.x + 0.7;
    double eye_y0 = pos.localization.y + 0.3;
    double eye_y1 = pos.localization.y + 0.7;
    double tail_s = 0.1;
    double cx = pos.localization.x + 0.5;
    double cy = pos.localization.y + 0.5;

    switch(pos.direction){
        case Up:
            mouseHeadX = {eye_x0, eye_x1};
            mouseHeadY = {eye_y1, eye_y1};
            mouseTailX = {cx, cx};
            mouseTailY = {pos.localization.y + tail_s, cy - tail_s};
            break;
        case Down:
            mouseHeadX = {eye_x0, eye_x1};
            mouseHeadY = {eye_y0, eye_y0};
            mouseTailX = {cx, cx};
            mouseTailY = {cy + tail_s, pos.localization.y + 1 - tail_s};
            break;
        case Left:
            mouseHeadX = {eye_x0, eye_x0};
            mouseHeadY = {eye_y0, eye_y1};
            mouseTailX = {cx + tail_s, pos.localization.x + 1 - tail_s};
            mouseTailY = {cy, cy};
            break;
        case Right:
            mouseHeadX = {eye_x1, eye_x1};
            mouseHeadY = {eye_y0, eye_y1};
            mouseTailX = {cx - tail_s, pos.localization.x + tail_s};
            mouseTailY = {cy, cy};
            break;
        default:
            break;
    }

    if(init){
        mouseBody = DrawMouseCircle(mouseBodyX, mouseBodyY, BLUE, 10);
        mouseHead = DrawMouseCircle(mouseHeadX, mouseHeadY, BLUE, 5);
        mouseTail = DrawMouseLine(mouseTailX, mouseTailY, GRAY, 3);
    }
    else{
        mouseBody->data()->clear();
        mouseBody->setData(mouseBodyX, mouseBodyY);
        mouseHead->data()->clear();
        mouseHead->setData(mouseHeadX, mouseHeadY);
        mouseTail->data()->clear();
        mouseTail->setData(mouseTailX, mouseTailY);
    }
    cout <<"mouse.loc x: "<<pos.localization.x << " y: "<<pos.localization.y << endl;
}
