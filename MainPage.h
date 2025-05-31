#ifndef MAINPAGE_H
#define MAINPAGE_H

#include "DiskScanner.h"
#include "MusicListModel.h"
#include "qaudiooutput.h"
#include "qdatetime.h"
#include "qmediaplayer.h"
#include "qsortfilterproxymodel.h"
#include <QPushButton>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include <QSlider>
#include <QAbstractListModel>
#include <QListWidget>
#include <QFileDialog>
class MainPage : public QObject{
    Q_OBJECT
public:
    MainPage(QWidget *_parent =nullptr);
    void initMainPage();
    void initconnect();
    void initMusicList();
    void initMusic();
    void updateMusic(int newMusicIndex);

public slots:
    void NextMusic();
    void PreviewMusic();
    void UpdateMusic(QListWidgetItem *item);
    void AddMusic();
    void updateMusicListModel(QStringList newMusic);
private:
    QWidget *parent;
    QPushButton *player;
    QPushButton *next;
    QPushButton *preview;
    QLabel *currentMusicName;
    QSlider *timeSlider;
    QSlider *volumeSlider;
    QPushButton *volumeButton;
    QLabel *time;
    QListWidget *musicList;
    QPushButton *addMusic;
    QPushButton *seachMusic;

    MusicListModel *musicListModel;
    QString CurrentMusic;
    int CurrentMusicIndex;
    QMediaPlayer *Music = new QMediaPlayer;
    QAudioOutput *OutPut = new QAudioOutput;
    QTime TotalTime;
    QTime CurrentTime;
    DiskScanner *diskScanner;
    QSortFilterProxyModel *viewModel;
};

#endif // MAINPAGE_H
