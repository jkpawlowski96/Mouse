#include "simulator.h"

Simulator::Simulator(QCustomPlot *_plot, string mapFilePath)
{
    this->plot = _plot;
    SetMap(mapFilePath);
    PlotMap();
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

    plot->replot();
    plot->update();
}
