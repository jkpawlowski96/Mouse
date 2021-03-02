#include "map.h"
#include <iostream>
#include <fstream>

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
}

Point Map::GetPoint(string text, string delimiter){
    auto textSplited = SplitText(text, delimiter);
    Point point;
    point.x = stoi(textSplited[0]);
    point.y = stoi(textSplited[1]);
    return point;
}

vector<string> Map::SplitText(string text, string delimiter){
    string text_1 = text.substr(0, text.find(delimiter));
    string text_2 = text.substr(1, text.find(delimiter));
    return {text_1, text_2};
}

Path Map::GetPath(string line){
    auto textSplited = SplitText(line, " ");
    Path path;
    path.start = GetPoint(textSplited[0], ",");
    path.stop = GetPoint(textSplited[1], ",");
    return path;
}

