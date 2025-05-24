#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void initMusicList();
    void initMusic();
    void addMusicList(QString MusicName);
public slots:
    void NextMusic();
    void PreviewMusic();

private:
    Ui::MainWindow* ui;
    QList<QUrl> MusicList;
    QUrl* CurrentMusic;
    QMediaPlayer *Music = new QMediaPlayer;
    QAudioOutput *output = new QAudioOutput;
    view *view;
};


#endif // MAINWINDOW_H
