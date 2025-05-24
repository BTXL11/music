#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    //initwindow(this);
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initwindow(QWidget* parent){
    view = new class view(parent);
    QObject::connect(view->player,&QPushButton::clicked,this,[&](){
        if(!Music->isPlaying())
        {
            Music->play();
            view->player->setText("pause");
        }
        else
        {
            Music->pause();
            view->player->setText("start");
        }
    });
    QObject::connect(view->next,&QPushButton::clicked,this,&MainWindow::NextMusic);
    QObject::connect(view->preview,&QPushButton::clicked,this,&MainWindow::PreviewMusic);
    QObject::connect(Music,&QMediaPlayer::durationChanged,[&](){
        view->timeSlider->setRange(0,Music->duration());
    });
    //QObject::connect(&player,&QPushButton::clicked,&w,[&w](){QDialog *D = new QDialog(&w);D->show();});
}

void MainWindow::initMusicList()
{
    addMusicList("E:\\work\\Qt_project\\music\\music_res\\晴天——空匪.mp3");
    addMusicList("E:\\work\\Qt_project\\music\\music_res\\Breathe_-_George_Capon.mp3");
    addMusicList("E:\\work\\Qt_project\\music\\music_res\\Erick_Fill_&amp;_Alwaro_-_You'll_Be_Fine_ft._Crushboys_(Original_Mix)_-_erickfill.mp3");
    addMusicList("E:\\work\\Qt_project\\music\\music_res\\Ocean_-_David_Davis.mp3");
    this->CurrentMusic=&MusicList.first();
    Music->setSource(*CurrentMusic);
    view->currentMusicName->setText(CurrentMusic->fileName());
}

void MainWindow::initMusic()
{
    Music->setAudioOutput(output);
    initMusicList();
    output->setVolume(50);
}


void MainWindow::addMusicList(QString MusicName)
{
    this->MusicList.append(QUrl::fromLocalFile(MusicName));
}

void MainWindow::NextMusic()
{
    if(*CurrentMusic!=MusicList.last())
    {
        CurrentMusic+=1;
    }
    else
    {
        CurrentMusic=&MusicList.first();
    }
    Music->setSource(*CurrentMusic);
    view->currentMusicName->setText(CurrentMusic->fileName());
    qDebug()<<*CurrentMusic;

}

void MainWindow::PreviewMusic()
{
    if(*CurrentMusic!=MusicList.first())
    {
        CurrentMusic-=1;
    }
    else
    {
        CurrentMusic=&MusicList.last();
    }
    Music->setSource(*CurrentMusic);
    view->currentMusicName->setText(CurrentMusic->fileName());
    qDebug()<<*CurrentMusic;
}
