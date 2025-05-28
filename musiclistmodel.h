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
    QList<QString> path;
    QSet<QString> isFavorite;
    enum Property {Path = 0,IsFavorite = 1};
public:
    MusicListModel( QObject *parent =nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index,const QVariant &value,int role = Qt::EditRole) override;
    void appendPath(QString MusicName);
    QString path_at(int index);
    int pathSize();
    bool contains(QString _path);
};

#endif // MUSICLISTMODEL_H
