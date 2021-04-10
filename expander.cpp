#include "expander.h"

Expander::Expander()
{
    Path<int> path(Unnown);
    path.localization.x=0;
    path.localization.y=0;
    nowPath = make_shared<Path<int>>(path);
    pathList.push_back(nowPath);
    nowDireciton = Up;
}

Task Expander::Logic(SensorData sensorData){
    if(sensorData.wallDetected){
        nowPath->acces[nowDireciton] = Forbiden;
    }
    else{
        if(nowPath->next[nowDireciton] == nullptr){
            //new path ahead
            auto newLoc = nowPath->localization;
            if(nowDireciton==Up)
                newLoc.y += 1;
            if(nowDireciton==Down)
                newLoc.y -= 1;
            if(nowDireciton==Left)
                newLoc.x -= 1;
            if(nowDireciton==Right)
                newLoc.x += 1;
            shared_ptr<Path<int>> newPath = GetPathByLoc(newLoc);
            if(newPath == nullptr){
                newPath = make_shared<Path<int>>(Unnown);
                newPath->localization = newLoc;
                pathList.push_back(newPath);
            }
            Direction _d = TurnAroundDirection(nowDireciton);
            nowPath->acces[nowDireciton] = Allowed;
            newPath->acces[_d] = Allowed;
            nowPath->next[nowDireciton] = newPath;
            newPath->next[_d]= nowPath;
            nowPath = newPath;
            return Forward;
        }
    }
    auto taskDirection = NearestPathToUnnown();
    if(taskDirection == DirectionUnnown)
        for(int i=0;i<4;i++){
            if(nowPath->acces[i]==Unnown)
                taskDirection=DirectionFromInt(i);
    }

    if(nowDireciton == taskDirection){
        nowPath = nowPath->next[taskDirection];
        return Forward;
    }

    Task task = nowDireciton > taskDirection;
    if(task==RotateLeft)
        nowDireciton = RotateDirectionLeft(nowDireciton);
    if(task==RotateRight)
        nowDireciton = RotateDirectionRight(nowDireciton);
    if(task==TurnAround)
        nowDireciton = TurnAroundDirection(nowDireciton);
    return task;
}

shared_ptr<Path<int>> Expander::FirstUnnown(){
    for(auto& path: pathList)
        for(int i=0; i<4;i++)
            if(path->acces[i]==Unnown)
                return path;
    return nullptr;
}

Direction Expander::NearestPath(shared_ptr<Path<int>> target){
    if(target->localization == nowPath->localization)
        return DirectionUnnown;

    vector<ExpanderPath> nodes;
    for(int d=0; d<4; d++){
        if(nowPath->next[d] != nullptr){
            ExpanderPath _ep;
            _ep.path = nowPath->next[d];
            _ep.origin = DirectionFromInt(d);
            nodes.push_back(_ep);
        }}

    while(true){
        // find target
        vector<ExpanderPath> newNodes;
        // new nodes
        for(auto &ep : nodes){
            for(int d=0; d<4; d++){
                if(ep.path->next[d] != nullptr){
                    ExpanderPath _ep;
                    _ep.path = ep.path->next[d];
                    _ep.origin = ep.origin;
                    newNodes.push_back(_ep);
                }
            }
        }

        for(auto &ep : nodes){
            if(ep.path->localization == target->localization){
                return ep.origin;
            }
        }
        nodes = newNodes;
    }
}

Direction Expander::NearestPathToUnnown(){
    ExpanderPath ep;
    ep.path = nowPath;
    ep.origin = DirectionUnnown;
    vector<ExpanderPath> nodes ={ep};
    for(int d=0; d<4; d++){
        if(nowPath->next[d] != nullptr){
            ExpanderPath _ep;
            _ep.path = nowPath->next[d];
            _ep.origin = DirectionFromInt(d);
            nodes.push_back(_ep);
        }}

    while(true){
        // find target
        vector<ExpanderPath> newNodes;
        // new nodes
        for(auto &ep : nodes){
            for(int d=0; d<4; d++){
                if(ep.path->next[d] != nullptr){
                    ExpanderPath _ep;
                    _ep.path = ep.path->next[d];
                    _ep.origin = ep.origin;
                    newNodes.push_back(_ep);
                }
            }
        }

        for(auto &ep : nodes){
            for(int i=0; i<4;i++)
                if(ep.path->acces[i]==Unnown){
                    return ep.origin;
                }
        }
        nodes = newNodes;
    }
}

shared_ptr<Path<int>> Expander::GetPathByLoc(Point<int> loc){
    for(auto& path: pathList)
        if(path->localization == loc)
            return path;
    return nullptr;
}



