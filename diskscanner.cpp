#include "diskscanner.h"

DiskScanner::DiskScanner(QObject *parent):QObject(parent)
{
    addPaths(QStandardPaths::standardLocations(QStandardPaths::MusicLocation));

}

void DiskScanner::addPath(const QString &path)
{
    if(seachPath.contains(path)){
        return;
    }
    seachPath.append(path);
    QStringList pendingPath;
    pendingPath.append(path);
    QDirIterator it(path,QDir::Dirs | QDir::NoDotAndDotDot,QDirIterator::Subdirectories);
    while(it.hasNext()){
        pendingPath.append(it.next());
    }
    for(auto& path:pendingPath){
        if(diskWatcher.directories().contains(path)){
            continue;
        }
        diskWatcher.addPath(path);
        qInfo()<<path;
    }

}

void DiskScanner::addPaths(const QStringList &paths)
{
    for(const auto& path:paths){
        addPath(path);
    }
}

void DiskScanner::scan(bool fullScan)
{
    bool isInitScan = true;
    fullScan = fullScan||isInitScan;
    isInitScan = false;
    for(auto &path:diskWatcher.directories()){
        scanPath(path);
    }

}

void DiskScanner::scanPath(const QString &path, bool fullScan)
{
    if(!diskWatcher.directories().contains(path)){
        //run remove
        pendingDeleted += cache.take(path);
        return;
    }
    qDebug()<<path;
    //QStringList oldCache = fullScan?QString {}:cache.value(path);
    QStringList newCache;
    auto &&entryInfoList = QDir(path).entryInfoList(musicFileFilter,
                                                    QDir::Files|QDir::NoDotAndDotDot);
    for(auto& entry : entryInfoList){
        newCache+=entry.absoluteFilePath();
    }
    emit scanNewMusic(newCache);
    //cache.insert(path,newCache);
    //auto&& [added,removed]=diff(oldCache,newCache);
}
