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
    viewModel = new QSortFilterProxyModel;
    viewModel->setSourceModel(musicListModel);
    view = new class view(viewModel,this);
    this->initMusic();
    this->initconnect();
    //QObject::connect(&player,&QPushButton::clicked,&w,[&w](){QDialog *D = new QDialog(&w);D->show();});
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
    QObject::connect(view->player2,&QPushButton::clicked,this,[&](){
        if(!Music2->isPlaying())
        {
            Music2->play();
            view->player2->setText("pause");
        }
        else
        {
            Music2->pause();
            view->player2->setText("start");
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
}

void MainWindow::initMusicList()
{
    musicListModel->appendPath("E:\\work\\Qt_project\\music\\music_res\\晴天——空匪.mp3");
    musicListModel->appendPath("E:\\work\\Qt_project\\music\\music_res\\Breathe_-_George_Capon.mp3");
    musicListModel->appendPath("E:\\work\\Qt_project\\music\\music_res\\Erick_Fill_&amp;_Alwaro_-_You'll_Be_Fine_ft._Crushboys_(Original_Mix)_-_erickfill.mp3");
    musicListModel->appendPath("E:\\work\\Qt_project\\music\\music_res\\Ocean_-_David_Davis.mp3");
    addMusicList("E:\\work\\Qt_project\\music\\music_res\\晴天——空匪.mp3");
    addMusicList("E:\\work\\Qt_project\\music\\music_res\\Breathe_-_George_Capon.mp3");
    addMusicList("E:\\work\\Qt_project\\music\\music_res\\Erick_Fill_&amp;_Alwaro_-_You'll_Be_Fine_ft._Crushboys_(Original_Mix)_-_erickfill.mp3");
    addMusicList("E:\\work\\Qt_project\\music\\music_res\\Ocean_-_David_Davis.mp3");
    this->CurrentMusic=&MusicList.first();
    if(viewModel->index(0,0).isValid()){
        this->currentMusic=musicListModel->index(0,0).data().toString();
        qDebug()<<"this is valid";
    }
    else{
        qDebug()<<"this is not valid";
    }
    Music->setSource(*CurrentMusic);
    Music2->setSource(QUrl::fromLocalFile(this->currentMusic));
    qDebug()<<QUrl::fromLocalFile(this->currentMusic);
    view->currentMusicName->setText((*CurrentMusic).fileName());
}

void MainWindow::initMusic()
{
    Music->setAudioOutput(OutPut);
    Music->setAudioOutput(OutPut2);
    initMusicList();
    OutPut->setVolume(50);
    OutPut2->setVolume(50);
    view->volumeSlider->setSliderPosition(OutPut->volume());
    view->timeSlider->setMaximum(Music->duration());
    TotalTime = QTime(0,0).addMSecs(Music->duration());
    view->volumeSlider->setSliderPosition(OutPut->volume());
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
    view->player->setText("start");
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
    view->player->setText("start");
}
