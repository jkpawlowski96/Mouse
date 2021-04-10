#ifndef MAP_H
#define MAP_H
#include <stdlib.h>
#include <string>
#include "qcustomplot.h"
#include "geometry.h"
#include <memory>

using namespace std;

#define MAP_SIZE_SIGN "size"
#define MAP_START_SIGN "start"
#define MAP_STOP_SIGN "stop"
#define MAP_PATHS_SIGN "paths"

/**
 * @brief Map representation in mucromouse simulator
 * 
 */
class Map
{
public:
    /**
     * @brief Construct a new Map object
     * 
     * @param mapFilePath 
     */
    Map(string mapFilePath);
    /**
     * @brief Construct a new Map object
     * 
     */
    Map(){};
    /**
     * @brief Destroy the Map object
     * 
     */
    ~Map();
    /**
     * @brief Get const path by localization
     * 
     * @param localization 
     * @return const Path<int> 
     */
    const Path<int> FindPathConst(Point<int> localization);
    /**
     * @brief list of known paths in map
     * 
     */
    vector<Path<int>> mapPaths;
    /**
     * @brief map start point (x,y)
     * 
     */
    Point<int> mapStart;
    /**
     * @brief map size (w,h)
     * 
     */
    Point<int> mapSize;
    /**
     * @brief vector ofmap stop points (x,y)
     * 
     */
    vector<Point<int>> mapStop;

protected:
    /**
     * @brief Get path ptr by localization
     * 
     * @tparam T 
     * @param localization 
     * @return shared_ptr<Path<T>> 
     */
    template<typename T>
    shared_ptr<Path<T>> FindPath(Point<T> localization);
    /**
     * @brief Get vector of paths by localizations in vector
     * 
     * @tparam T 
     * @param localizations 
     * @return vector<shared_ptr<Path<T>>> 
     */
    template<typename T>
    vector<shared_ptr<Path<T>>> FindPaths(vector<Point<T>> localizations);
    /**
     * @brief Insert new path in structure
     * 
     * @param newPaths 
     */
    void InsertPaths(vector<Path<int>> newPaths);
    /**
     * @brief Find near localizations of specyfic localization (x,y)
     * 
     * @tparam T 
     * @param localization 
     * @return vector<Point<T>> 
     */
    template<typename T>
    vector<Point<T>> FindNearLocalizations(Point<T> localization);
    /**
     * @brief Update/refresh connections in specyfic paths
     * 
     * @param path 
     */
    void UpdateConnections(shared_ptr<Path<int>> path);

private:

    template<typename T>
    vector<Path<T>> GetPaths(string line);
    vector<string> SplitText(string text, char delimiter);
    template<typename T>
    Point<T> GetPoint(string text, char delimiter);



};

vector<Line<double>> GetPathLines(Path<int> path);

#endif // MAP_H
