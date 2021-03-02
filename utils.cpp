#include "utils.h"

QStringList GetMapFiles(const char *path){
    QStringList forbiden = {".",".."};
    QStringList files;
    struct dirent *entry;
    DIR *dir = opendir(path);
    if (dir == NULL) {
        return files;
    }
    while ((entry = readdir(dir)) != NULL) {
        QString file = entry->d_name;
        if(!forbiden.contains(file))
            files.push_back(entry->d_name);
    }
    closedir(dir);
    return files;
}
