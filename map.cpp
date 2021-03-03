#include "map.h"
#include <iostream>
#include <fstream>
#include <sstream>      // std::stringstream


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
    mapSize = GetPoint(sizeLine, 'x');
    mapStart = GetPoint(startLine, ',');

    mapStop.clear();
    for(auto const& line: stopLines)
        mapStop.push_back(GetPoint(line,','));

    mapPaths.clear();
    for(auto const& line: pathLines)
        mapPaths.push_back(GetPath(line));
}

Map::~Map(){

}

Point Map::GetPoint(string text, char delimiter){
    auto textSplited = SplitText(text, delimiter);
    Point point;
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

Path Map::GetPath(string line){
    auto textSplited = SplitText(line, ' ');
    Path path;
    path.start = GetPoint(textSplited[0], ',');
    path.stop = GetPoint(textSplited[1], ',');
    return path;
}


