#include "DiskScanner.h"

DiskScanner::DiskScanner(QObject *parent):QObject(parent)
{
    addPaths(QStandardPaths::standardLocations(QStandardPaths::MusicLocation));
    addPath("E:\\work\\Qt_project\\music\\music_res");
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
        scanMusicPath(path);
    }
    for(auto &path:diskWatcher.directories()){
        scanLyricsPath(path);
    }
}

void DiskScanner::scanMusicPath(const QString &path, bool fullScan)
{
    if(!diskWatcher.directories().contains(path)){
        return;
    }
    qDebug()<<"scan music path:"+path;
    QStringList musicCache;
    auto &&entryInfoList = QDir(path).entryInfoList(musicFileFilter,
                                                    QDir::Files|QDir::NoDotAndDotDot);
    for(auto& entry : entryInfoList){
        musicCache+=entry.absoluteFilePath();
    }
    emit scanMusic(musicCache);


}

void DiskScanner::scanLyricsPath(const QString &path, bool fullScan)
{
    if(!diskWatcher.directories().contains(path)){
        return;
    }
    qDebug()<<"scan lyrics path:"+path;
    QStringList lyricsCache;
    auto &&_entryInfoList = QDir(path).entryInfoList(lyricsFileFilter,
                                                     QDir::Files|QDir::NoDotAndDotDot);
    for(auto& _entry : _entryInfoList){
        lyricsCache+=_entry.absoluteFilePath();
    }
    emit scanLyrics(lyricsCache);
}
