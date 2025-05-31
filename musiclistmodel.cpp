#include "MusicListModel.h"
#include "qfileinfo.h"

MusicListModel::MusicListModel(QObject *parent): QAbstractTableModel(parent){}

int MusicListModel::rowCount(const QModelIndex &parent) const
{
    return path.size();
}

int MusicListModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant MusicListModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid()||index.row()>=rowCount()||index.column()>=columnCount()){
        return {};
    }
    if(role==Qt::DisplayRole||role==Qt::EditRole){
        switch(Property(index.column())){
        case Property::Name:
            return name.value(index.row());
        case Property::Path:
            return path.value(index.row());
        case Property::LyricsPath:
            return lyricsPath.value(index.row());
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
        case Property::Name:
            path.replace(index.row(),value.toString());
        case Property::Path:
            path.replace(index.row(),value.toString());
        case Property::LyricsPath:
            lyricsPath.replace(index.row(),value.toString());
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

void MusicListModel::appendMusicPath(QString MusicPath)
{
    if(!path.contains(MusicPath)){
        path.append(MusicPath);
        lyricsPath.append("For the moment, there are no lyrics");
        QFileInfo file(MusicPath);
        name.append(file.baseName());
        QStringList temNewMusic={file.baseName()};
        emit newMusic(temNewMusic);
    }
}

void MusicListModel::appendLyricsPath(QString LyricsPath)
{
    if(!lyricsPath.contains(LyricsPath)){
        QFileInfo file(LyricsPath);
        lyricsPath.replace(name.indexOf(file.baseName()),LyricsPath);
        qDebug()<<name.indexOf(file.baseName());
        qDebug()<<LyricsPath;
        QStringList temNewLyricsPath={LyricsPath};
        emit newLyrics(temNewLyricsPath);
    }
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

bool MusicListModel::isempty()
{
    return path.isEmpty();
}

void MusicListModel::appendLyricsPathList(QStringList lyricsPath)
{
    for(auto& path: lyricsPath){
        appendLyricsPath(path);
    }
}

void MusicListModel::appendMusicPathList(QStringList musicPath)
{
    for(auto&path:musicPath){
        this->appendMusicPath(path);
    }
    qDebug()<<path.size();
}
