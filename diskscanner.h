#ifndef DISKSCANNER_H
#define DISKSCANNER_H

#include <QObject>
#include <QWidget>
#include <QStandardPaths>
#include <QFileSystemWatcher>
#include <QDirIterator>
#include <QMap>

class DiskScanner :public QObject{
    Q_OBJECT
public:
DiskScanner(QObject *parent=nullptr);
    void addPath(const QString& path);
    void addPaths(const QStringList& paths);
    void scan(bool fullscan = false);
private:
    QStringList seachPath;
    QFileSystemWatcher diskWatcher;
    //scan special path,path must be a subfolder of searchPath
    QMap<QString,QStringList> cache;
    void scanPath(const QString& path,bool fullScan = false);
    //work with scan() and scanPath(), as scan ache
    QStringList pendingCreate, pendingDeleted;
    //Dir name filter
    static const inline QStringList musicFileFilter = {
        "*.mp3", "*.wav", "*.flac", "*.ogg", "*.m4a"
    };
    //static DiffResult diff(const QStringList oldv,const QStringList newv);
signals:
    void scanNewMusic(QStringList musicPath);

};

#endif // DISKSCANNER_H
