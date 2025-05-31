#ifndef DISKSCANNER_H
#define DISKSCANNER_H

#include <QObject>
#include <QWidget>
#include <QStandardPaths>
#include <QFileSystemWatcher>
#include <QDirIterator>
#include <QMap>
#include <QtTest/QSignalSpy>
#include <QTimer>

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
    void scanMusicPath(const QString& path,bool fullScan = false);
    void scanLyricsPath(const QString& path,bool fullScan = false);
    //work with scan() and scanPath(), as scan ache
    //Dir name filter
    static const inline QStringList musicFileFilter = {
        "*.mp3", "*.wav", "*.flac", "*.ogg", "*.m4a",
    };
    static const inline QStringList lyricsFileFilter = {
        "*.lrc",
    };
    //static DiffResult diff(const QStringList oldv,const QStringList newv);
signals:
    void scanMusic(QStringList musicPath);
    void scanLyrics(QStringList lyricsPath);
};

#endif // DISKSCANNER_H
