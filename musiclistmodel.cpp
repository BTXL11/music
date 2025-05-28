#include "musiclistmodel.h"

MusicListModel::MusicListModel(QObject *parent): QAbstractTableModel(parent){}

int MusicListModel::rowCount(const QModelIndex &parent) const
{
    return path.size();
}

int MusicListModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant MusicListModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid()||index.row()>=rowCount()||index.column()>=columnCount()){
        return {};
    }
    if(role==Qt::DisplayRole||role==Qt::EditRole){
        switch(Property(index.column())){
        case Property::Path:
            return path.value(index.row());
        case IsFavorite:
            return isFavorite.contains(path.value(index.row()));
        }
    }
    return {};
}

bool MusicListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid()||index.row()>=rowCount()||index.column()>=columnCount()){
        return false;
    }
    if(role==Qt::EditRole){
        switch(Property(index.column())){
        case Property::Path:
            path.replace(index.row(),value.toString());
        case Property::IsFavorite:
            if(value.value<bool>()){
                isFavorite.insert(path.value(index.row()));
                dataChanged(index,index);
            }
            else{
                isFavorite.remove(path.value(index.row()));
                dataChanged(index,index);
            }
        }
    }
    return false;
}

void MusicListModel::appendPath(QString MusicName)
{
    path.append(MusicName);
    QStringList temNewMusic={MusicName};
    emit newMusic(temNewMusic);
}

QString MusicListModel::path_at(int index)
{
    return path.at(index);
}

int MusicListModel::pathSize()
{
    return path.size();
}

bool MusicListModel::contains(QString _path)
{
    return path.contains(_path);
}

void MusicListModel::appendPathList(QStringList musicPath)
{
    path+=musicPath;
    emit newMusic(musicPath);
}
