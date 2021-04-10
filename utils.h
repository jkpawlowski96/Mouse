#ifndef UTILS_H
#define UTILS_H
#include <QStringList>
#include <vector>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

#define MAPS_LOCATION "maps"

using namespace std;

/**
 * @brief Get the Map Files list
 * 
 * @param path 
 * @return QStringList 
 */
QStringList GetMapFiles(const char *path=MAPS_LOCATION);


#endif // UTILS_H
