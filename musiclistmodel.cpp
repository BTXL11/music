#include "MusicListModel.h"



void MusicListModel::appendLyrics(QList<QTime> temtime, QList<QString> temlyrics)
{
    lyrics.append(lyricsStruct(temtime,temlyrics));
}

void MusicListModel::replaceLyrics(int index, QList<QTime> temtime, QList<QString> temlyrics)
{
    lyrics.replace(index,lyricsStruct(temtime,temlyrics));
}

void MusicListModel::replaceLyrics(int index, lyricsStruct temlyricsStruct)
{
    lyrics.replace(index,temlyricsStruct);
}

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
        case Property::Lyrics:{
            const lyricsStruct& lsStruct=lyrics[index.row()];
            QString lyricsInfo;
            for(int i=0;i<lsStruct.lyrics.size();i++){
                lyricsInfo+=QString(lsStruct.time[i].toString()+lsStruct.lyrics[i]);
            }
            return lyricsInfo.trimmed();
        }
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
            replaceLyrics(index.row(),{value.toTime()},value.toStringList());
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
        appendLyrics({QTime(0,0)},{"For the moment, there are no lyrics"});
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
    return lyricsPath.at(index);
}

QString MusicListModel::lyric_at(int lyricsIndex, int index) const
{
    return lyrics.at(lyricsIndex).lyrics.at(index);
}

QTime MusicListModel::time_at(int lyricsIndex, int index) const
{
    return lyrics.at(lyricsIndex).time.at(index);
}

int MusicListModel::pathSize() const
{
    return path.size();
}

int MusicListModel::lyricsSize(int index) const
{
    return lyrics.at(index).lyrics.size();
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
    QRegularExpression tim(R"(\d{2}:\d{2}.\d{2})");
    QRegularExpression lyr(R"(\p{Script=Han}+)");
    for(auto&path:lyricsPath){
        if(path!="For the moment, there are no lyrics"){
            QFile file(path);
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
                qWarning() << "Cannot open file for reading:" << path;
                return;
            }
            int index = lyricsPath.indexOf(path);
            lyricsStruct temlyricsStruct;
            QTextStream in(&file);
            QString line;
            //QString title;
            //QString artist;
            QString timeString;
            QString lyric;
            QTime time;
            while(!in.atEnd()){
                line =in.readLine();
                if(tim.match(line).hasMatch()){
                    timeString = tim.match(line).captured();
                    time=QTime::fromString(timeString,"mm:ss.zz");
                    lyric = lyr.match(line).captured();
                    temlyricsStruct.append(time,lyric);
                }
            }
            replaceLyrics(index,temlyricsStruct);
        }
    }
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



void lyricsStruct::append(QTime temtime, QString temlyrics)
{
    time.append(temtime);
    lyrics.append(temlyrics);
}
