#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initwindow(QWidget* parent){
    musicListModel = new MusicListModel;
    diskScanner = new DiskScanner;
    view = new class view(this);
    initconnect();
    initMusic();
    initview();
    //QObject::connect(&player,&QPushButton::clicked,&w,[&w](){QDialog *D = new QDialog(&w);D->show();});
}

void MainWindow::initview()
{
    view->volumeSlider->setSliderPosition(OutPut->volume());
    view->timeSlider->setMaximum(Music->duration());
    TotalTime = QTime(0,0).addMSecs(Music->duration());
    view->volumeSlider->setSliderPosition(OutPut->volume());
}

void MainWindow::initconnect()
{
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
        view->timeSlider->setMaximum(Music->duration());
    });
    QObject::connect(Music,&QMediaPlayer::positionChanged,[&](){
        view->timeSlider->setSliderPosition(Music->position());
    });
    QObject::connect(Music,&QMediaPlayer::durationChanged,[&](){
        TotalTime = QTime(0,0).addMSecs(Music->duration());
        view->time->setText("00:00:00/"+TotalTime.toString());
    });
    QObject::connect(Music,&QMediaPlayer::positionChanged,[&](){
        CurrentTime = QTime(0,0).addMSecs((Music->position()));
        view->time->setText(CurrentTime.toString()+"/"+TotalTime.toString());
    });
    QObject::connect(view->timeSlider,&QSlider::sliderMoved,[&](){
        Music->setPosition(view->timeSlider->sliderPosition());
    });
    QObject::connect(view->timeSlider,&QSlider::sliderPressed,[&](){
        Music->setPosition(view->timeSlider->sliderPosition());
    });
    QObject::connect(Music,&QMediaPlayer::mediaStatusChanged,[&](){
        if(Music->mediaStatus()==QMediaPlayer::EndOfMedia){
            view->next->click();
        }
    });
    QObject::connect(view->volumeSlider,&QSlider::sliderMoved,[&](){
        OutPut->setVolume(view->volumeSlider->sliderPosition());
    });
    QObject::connect(view->volumeButton,&QPushButton::clicked,[&](){
        if(view->volumeSlider->isHidden()){
            view->volumeSlider->show();
        }
        else{
            view->volumeSlider->hide();
        }
    });
    QObject::connect(view->musicList,&QListWidget::itemClicked,this,&MainWindow::UpdateMusic);
    QObject::connect(view->addMusic,&QPushButton::clicked,this,&MainWindow::AddMusic);
    QObject::connect(diskScanner,&DiskScanner::scanNewMusic,musicListModel,&MusicListModel::appendPathList);
    QObject::connect(musicListModel,&MusicListModel::newMusic,this,&MainWindow::updateMusicListModel);

}

void MainWindow::initMusicList()
{
    musicListModel->appendPath("E:\\work\\Qt_project\\music\\music_res\\晴天——空匪.mp3");
    musicListModel->appendPath("E:\\work\\Qt_project\\music\\music_res\\Breathe_-_George_Capon.mp3");
    musicListModel->appendPath("E:\\work\\Qt_project\\music\\music_res\\Erick_Fill_&amp;_Alwaro_-_You'll_Be_Fine_ft._Crushboys_(Original_Mix)_-_erickfill.mp3");
    musicListModel->appendPath("E:\\work\\Qt_project\\music\\music_res\\Ocean_-_David_Davis.mp3");
}

void MainWindow::initMusic()
{
    Music->setAudioOutput(OutPut);
    initMusicList();
    updateMusic(0);
    OutPut->setVolume(50);
}

void MainWindow::updateMusic(int newMusicIndex)
{
    CurrentMusicIndex=newMusicIndex;
    CurrentMusic=musicListModel->path_at(newMusicIndex);
    Music->setSource(QUrl::fromLocalFile(musicListModel->path_at(newMusicIndex)));
    view->currentMusicName->setText((QUrl::fromLocalFile(CurrentMusic)).fileName());
}

void MainWindow::NextMusic()
{
    if(CurrentMusicIndex!=musicListModel->pathSize()-1)
    {
        CurrentMusicIndex+=1;
    }
    else
    {
        CurrentMusicIndex=0;
    }
    updateMusic(CurrentMusicIndex);
    view->player->setText("start");
}

void MainWindow::PreviewMusic()
{
    if(CurrentMusicIndex!=musicListModel->pathSize()-1)
    {
        CurrentMusicIndex-=1;
    }
    else
    {
        CurrentMusicIndex=musicListModel->pathSize()-1;
    }
    updateMusic(CurrentMusicIndex);
    view->player->setText("pause");
}

void MainWindow::UpdateMusic(QListWidgetItem *item )
{
    int newMusicIndex=view->musicList->row(item);
    CurrentMusicIndex=newMusicIndex;
    CurrentMusic=musicListModel->path_at(newMusicIndex);
    Music->setSource(QUrl::fromLocalFile(musicListModel->path_at(newMusicIndex)));
    view->currentMusicName->setText((QUrl::fromLocalFile(CurrentMusic)).fileName());
    view->player->setText("start");
}

void MainWindow::AddMusic()
{
    QString newMusic = QFileDialog::getOpenFileName(this,"choose music","/home","(*.mp3)");
    if(!musicListModel->contains(newMusic)){
        musicListModel->appendPath(newMusic);
    }
}


void MainWindow::updateMusicListModel(QStringList newMusic)
{
    for(auto& path:newMusic){
        view->musicList->addItem(QUrl::fromLocalFile(path).fileName());
    }
}
