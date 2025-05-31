#ifndef MUSICLISTMODEL_H
#define MUSICLISTMODEL_H

#include <QObject>
#include <QWidget>
#include <QAbstractTableModel>
#include <QString>
#include <QList>
#include <QUrl>

class MusicListModel : public QAbstractTableModel{
    Q_OBJECT
    QList<QString> name;
    QList<QString> path;
    QList<QString> lyricsPath;
    QList<QStringList> lyrics;
    QSet<QString> isFavorite;
    enum Property {Name=0,Path = 1,LyricsPath=2,Lyrics=3,IsFavorite = 4};
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
