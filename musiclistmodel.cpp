#include "MusicListModel.h"
#include "qfileinfo.h"

MusicListModel::MusicListModel(QObject *parent): QAbstractTableModel(parent){}

int MusicListModel::rowCount(const QModelIndex &parent) const
{
    return path.size();
}

int MusicListModel::columnCount(const QModelIndex &parent) const
{
    return 5;
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
        case Property::Lyrics:
            return lyrics.value(index.row());
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
        case Property::Lyrics:
            lyrics.replace(index.row(),value.toStringList());
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
        QStringList temNewLyricsPath={LyricsPath};
        emit newLyrics(temNewLyricsPath);
    }
}

QString MusicListModel::path_at(int index) const
{
    return path.at(index);
}

QString MusicListModel::lyricsPath_at(int index) const
{
    return path.at(index);
}

int MusicListModel::pathSize() const
{
    return path.size();
}

bool MusicListModel::contains(const QString _path) const
{
    return path.contains(_path);
}

bool MusicListModel::isempty() const
{
    return path.isEmpty();
}

void MusicListModel::loadLyrics()
{

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
}
