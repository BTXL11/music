#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "musiclistmodel.h"
#include "view.h"
#include <QMainWindow>
#include <QPushButton>
#include <QPixmap>
#include <QDialog>
#include <QMediaPlayer>
#include <QFile>
#include <QUrl>
#include <QAudioOutput>
#include <QStringList>
#include <QDebug>
#include <QLabel>
#include <QTime>
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>
//#include <MediaExample>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void initwindow(QWidget* parent);
    void initconnect();
    void initMusicList();
    void initMusic();
    void addMusicList(QString MusicName);
public slots:
    void NextMusic();
    void PreviewMusic();
signals:



private:
    Ui::MainWindow* ui;
    QList<QUrl> MusicList;
    MusicListModel *musicListModel;
    QUrl *CurrentMusic;
    QString currentMusic;
    QMediaPlayer *Music = new QMediaPlayer;
    QMediaPlayer *Music2 = new QMediaPlayer;
    QAudioOutput *OutPut = new QAudioOutput;
    QAudioOutput *OutPut2 = new QAudioOutput;
    QTime TotalTime;
    QTime CurrentTime;
    view *view;
    QSortFilterProxyModel *viewModel;
};


#endif // MAINWINDOW_H
