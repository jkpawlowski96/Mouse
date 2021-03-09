#include "map.h"
#include <iostream>
#include <fstream>
#include <sstream>      // std::stringstream

template<typename T>
Point<T> operator+(Point<T> a, Point<T> b)
{
    Point<T> res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    return res;
};

template<typename T>
Point<T> operator-(Point<T> a, Point<T> b)
{
    Point<T> res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    return res;
};

template<typename T>
Point<T> operator/(Point<T> a, T dev)
{
    Point<T> res;
    res.x = (T)(a.x/dev);
    res.y = (T)(a.y/dev);
    return res;
};

template<typename T>
Point<T> operator*(Point<T> a, T mul)
{
    Point<T> res;
    res.x = (T)(a.x*mul);
    res.y = (T)(a.y*mul);
    return res;
};

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
        mapPaths.insert(mapPaths.end(), newPaths.begin(), newPaths.end());
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
    Point<T> step= (stop - start)/steps;
    for(int i=0; i<=steps; i++){
        Path<T> path;
        path.localization = start + (step * i);
        paths.push_back(path);
    }
    return paths;
}


