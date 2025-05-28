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
#include <QModelIndex>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFileDialog>
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
    void initview();
    void initconnect();
    void initMusicList();
    void initMusic();
    void updateMusic(int newMusicIndex);
public slots:
    void NextMusic();
    void PreviewMusic();
    void UpdateMusic(QListWidgetItem *item);
    void AddMusic();
signals:



private:
    Ui::MainWindow* ui;
    MusicListModel *musicListModel;
    QString CurrentMusic;
    int CurrentMusicIndex;
    QMediaPlayer *Music = new QMediaPlayer;
    QAudioOutput *OutPut = new QAudioOutput;
    QTime TotalTime;
    QTime CurrentTime;
    view *view;
    QSortFilterProxyModel *viewModel;

};


#endif // MAINWINDOW_H
