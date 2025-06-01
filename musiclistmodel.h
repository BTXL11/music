#ifndef MUSICLISTMODEL_H
#define MUSICLISTMODEL_H

#include "qdatetime.h"
#include <QObject>
#include <QWidget>
#include <QAbstractTableModel>
#include <QString>
#include <QList>
#include <QUrl>
#include <QRegularExpression>
#include <QFileInfo>
struct lyricsStruct
{
    lyricsStruct(QList<QTime> temtime,QList<QString> temlyrics){
        time=temtime;
        lyrics=temlyrics;
    }
    lyricsStruct(){};
    void append(QTime temtime,QString temlyrics);
    QList<QTime> time;
    QList<QString> lyrics;
};
class MusicListModel : public QAbstractTableModel{
    Q_OBJECT

    QList<QString> name;
    QList<QString> path;
    QList<QString> lyricsPath;
    QList<lyricsStruct> lyrics;
    QSet<QString> isFavorite;
    enum Property {Name=0,Path = 1,LyricsPath=2,Lyrics=3,IsFavorite = 4};
    void appendLyrics(QList<QTime> temtime,QList<QString> temlyrics);
    void replaceLyrics(int index, QList<QTime> temtime,QList<QString> temlyrics);
    void replaceLyrics(int index, lyricsStruct temlyricsStruct);
public:
    MusicListModel( QObject *parent =nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index,const QVariant &value,int role = Qt::EditRole) override;
    void appendMusicPath(QString MusicPath);
    void appendLyricsPath(QString LyricsPath);
    QString path_at(int index) const;
    QString lyricsPath_at(int index) const;
    int pathSize() const;
    bool contains(const QString _path) const;
    bool isempty() const;
    void loadLyrics();


public slots:
    void appendMusicPathList(QStringList musicPath);
    void appendLyricsPathList(QStringList lyricsPath);
signals:
    void newMusic(QStringList newMusic);
    void newLyrics(QStringList newLyrics);
};

#endif // MUSICLISTMODEL_H
