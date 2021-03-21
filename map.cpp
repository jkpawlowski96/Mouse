#include "map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "geometry.h"

template<typename T>
vector<Point<T>> Map::FindNearLocalizations(Point<T> localization){
    vector<Point<T>> res;
    T minPoint = 1;
    if (localization.x >= minPoint)
        res.push_back(Point<T>(localization.x-1, localization.y));
    if (localization.y >= minPoint)
        res.push_back(Point<T>(localization.x, localization.y-1));
    res.push_back(Point<T>(localization.x, localization.y+1));
    res.push_back(Point<T>(localization.x+1, localization.y));
    return res;
}

Map::Map(string mapFilePath)
{
    string line, sizeLine, startLine;
    vector<string> stopLines;
    vector<string> pathLines;
    ifstream mapFile;
    mapFile.open(mapFilePath);
    if (mapFile.is_open())
    {

        getline (mapFile, line);
        if(line==MAP_SIZE_SIGN){
            getline(mapFile, line);
            sizeLine = line;
            getline (mapFile, line);
        }

        if(line==MAP_START_SIGN){
            getline(mapFile, line);
            startLine = line;
            getline (mapFile, line);
        }

        if(line==MAP_STOP_SIGN){
            getline(mapFile, line);
            do{
                stopLines.push_back(line);
                getline(mapFile, line);
            }while (line != MAP_PATHS_SIGN);
        }

        if(line==MAP_PATHS_SIGN){
            while(getline(mapFile, line))
                if(line!="")
                pathLines.push_back(line);
        }
    }
    mapFile.close();
    mapSize = GetPoint<int>(sizeLine, 'x');
    mapStart = GetPoint<int>(startLine, ',');

    mapStop.clear();
    for(auto const& line: stopLines)
        mapStop.push_back(GetPoint<int>(line,','));

    mapPaths.clear();
    for(auto const& line: pathLines){
        auto newPaths = GetPaths<int>(line);
        //mapPaths.insert(mapPaths.end(), newPaths.begin(), newPaths.end());
        InsertPaths(newPaths);
    }

}

template<typename T>
shared_ptr<Path<T>> Map::FindPath(Point<T> localization){
    for(auto& path: mapPaths){
        if(path.localization == localization)
            return make_shared<Path<T>>(path);
    }
    return nullptr;
}

template<typename T>
vector<shared_ptr<Path<T>>> Map::FindPaths(vector<Point<T>> localizations){
    vector<shared_ptr<Path<T>>> res;
    for(auto const& loc: localizations){
        shared_ptr<Path<T>> p = FindPath(loc);
        if (p != nullptr)
            res.push_back(p);
    }
    return res;
}



void Map::InsertPaths(vector<Path<int>> newPaths){
    for(auto& newPath: newPaths){
        bool bussy = false;
        int bussyIndex;
        for(size_t i =0; i<mapPaths.size();i++)
            if(newPath.localization == mapPaths[i].localization){
                bussy=true;
                bussyIndex=i;
            }
        if(bussy){
            mapPaths[bussyIndex].append(newPath);
        }
        else{
            mapPaths.push_back(newPath);
        }

    }

}

Map::~Map(){

}
    
template<typename T>
Point<T> Map::GetPoint(string text, char delimiter){
    auto textSplited = SplitText(text, delimiter);
    Point<T> point;
    point.x = stoi(textSplited[0]);
    point.y = stoi(textSplited[1]);
    return point;
}

vector<string> Map::SplitText(string text, char delimiter){
    stringstream textStream(text);
    string segment;
    vector<string> res;
    while(std::getline(textStream, segment, delimiter))
    {
       res.push_back(segment);
    }
    return res;
}

template<typename T>
vector<Path<T>> Map::GetPaths(string line){
    vector<Path<T>> paths;
    auto textSplited = SplitText(line, ' ');
    Point<T> start = GetPoint<T>(textSplited[0], ',');
    Point<T> stop = GetPoint<T>(textSplited[1], ',');
    int steps = abs((int)(stop.x - start.x) + (int)(stop.y - start.y));
    Point<T> step = (stop - start)/steps;
    for(int i=0; i<=steps; i++){
        Path<T> path;
        path.localization = start + (step * i);
        paths.push_back(path);
    }
    // connections
    for(size_t i=1; i<paths.size(); i++){
        Direction d = paths[i-1].localization >> paths[i].localization;
        Direction _d =paths[i-1].localization << paths[i].localization;
        paths[i-1].acces[d] = Allowed;
        paths[i-1].next[d] = make_shared<Path<int>>(paths[i]);
        paths[i].acces[_d] = Allowed;
        paths[i].next[_d] = make_shared<Path<int>>(paths[i-1]);
    }

    return paths;
}

vector<Line<double>> GetPathLines(Path<int> path){
    vector<Line<double>> res;
    double x = (double)path.localization.x;
    double y = (double)path.localization.y;
    double step = 1.0;
    if (path.acces[Up]==Forbiden)
        res.push_back(Line<double>(Point<double>(x, y+step), Point<double>(x+step,y+step)));
    if (path.acces[Down]==Forbiden)
        res.push_back(Line<double>(Point<double>(x, y), Point<double>(x+step,y)));
    if (path.acces[Left]==Forbiden)
        res.push_back(Line<double>(Point<double>(x, y), Point<double>(x,y+step)));
    if (path.acces[Right]==Forbiden)
        res.push_back(Line<double>(Point<double>(x+step, y), Point<double>(x+step,y+step)));
    return res;
}

void Map::UpdateConnections(shared_ptr<Path<int>> path){
    auto nearLocalizations = FindNearLocalizations<int>(path->localization);
    auto nearPaths = FindPaths(nearLocalizations);
    for(auto& nearPath: nearPaths){
        Direction d = path->localization >> nearPath->localization;
        Direction _d =path->localization << nearPath->localization;
        path->acces[d] = Allowed;
        path->next[d] = nearPath;
        nearPath->acces[_d] = Allowed;
        nearPath->next[_d] = path;
    }

}

const Path<int> Map::FindPathConst(Point<int> localization){
    auto path = FindPath(localization);
    Path<int> res = *path;
    return res;
}
