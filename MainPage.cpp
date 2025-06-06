#include "MainPage.h"
#include "DiskScanner.h"

MainPage::MainPage(QWidget *_parent) :parent(_parent){
    musicListModel = new MusicListModel;
    diskScanner = new DiskScanner();
    initMainPage();
    initconnect();
    initMusic();

}

void MainPage::initMainPage()
{
    player = new QPushButton(parent);
    player->move(200,200);
    player->setText("start");
    next = new QPushButton(parent);
    next->move(300,200);
    next->setText("next");
    preview = new QPushButton(parent);
    preview->setText("preview");
    preview->move(100,200);
    currentMusicName = new QLabel(parent);
    currentMusicName->move(200,150);
    currentMusicName->resize(200,50);
    timeSlider = new QSlider(Qt::Horizontal,parent);
    timeSlider->move(100,250);
    timeSlider->resize(300,50);
    time = new QLabel(parent);
    time->move(325,300);
    time->resize(200,50);
    volumeSlider = new QSlider(parent);
    volumeSlider->setMaximum(100);
    volumeSlider->setMinimum(0);
    volumeSlider->move(425,200);
    volumeSlider->resize(10,100);
    volumeSlider->hide();
    volumeButton = new QPushButton(parent);
    volumeButton->move(425,300);
    volumeButton->setText("volume");
    musicList = new QListWidget(parent);
    musicList->resize(200,400);
    musicList->move(500,0);
    addMusic = new QPushButton("addMusic",parent);
    seachMusic = new QPushButton("seachMusic",parent);
    seachMusic->move(100,0);
    volumeSlider->setSliderPosition(OutPut->volume());
    timeSlider->setMaximum(Music->duration());
    TotalTime = QTime(0,0).addMSecs(Music->duration());
    volumeSlider->setSliderPosition(OutPut->volume());
    lyricsDisplay = new QLabel("lyricsDisplay",parent);
    lyricsDisplay->move(150,400);
    lyricsDisplay->resize(500,100);
    lyricsDisplay->setTextFormat(Qt::RichText);
    QFont font("lyrics",20,QFont::Bold);
    lyricsDisplay->setFont(font);

}

void MainPage::initconnect()
{
    QObject::connect(player,&QPushButton::clicked,[&](){
        if(!Music->isPlaying())
        {
            Music->play();
        }
        else
        {
            Music->pause();
        }
    });
    QObject::connect(next,&QPushButton::clicked,this,&MainPage::NextMusic);
    QObject::connect(preview,&QPushButton::clicked,this,&MainPage::PreviewMusic);
    QObject::connect(Music,&QMediaPlayer::durationChanged,[&](){
        timeSlider->setMaximum(Music->duration());
    });
    QObject::connect(Music,&QMediaPlayer::positionChanged,[&](){
        timeSlider->setSliderPosition(Music->position());
    });
    QObject::connect(Music,&QMediaPlayer::durationChanged,[&](){
        TotalTime = QTime(0,0).addMSecs(Music->duration());
        time->setText("00:00:00/"+TotalTime.toString());
    });
    QObject::connect(Music,&QMediaPlayer::positionChanged,[&](){
        CurrentTime = QTime(0,0).addMSecs((Music->position()));
        time->setText(CurrentTime.toString()+"/"+TotalTime.toString());
    });
    QObject::connect(timeSlider,&QSlider::sliderMoved,[&](){
        Music->setPosition(timeSlider->sliderPosition());
    });
    QObject::connect(timeSlider,&QSlider::sliderPressed,[&](){
        Music->setPosition(timeSlider->sliderPosition());
    });
    QObject::connect(Music,&QMediaPlayer::mediaStatusChanged,[&](){
        if(Music->mediaStatus()==QMediaPlayer::EndOfMedia){
            next->click();
        }
    });
    QObject::connect(Music,&QMediaPlayer::playbackStateChanged,[&](QMediaPlayer::PlaybackState State){
        if(State==QMediaPlayer::PausedState){
            player->setText("start");
        }
        else if(State==QMediaPlayer::PlayingState){
            player->setText("pause");
        }
    });
    QObject::connect(volumeSlider,&QSlider::sliderMoved,[&](){
        OutPut->setVolume(volumeSlider->sliderPosition());
    });
    QObject::connect(volumeButton,&QPushButton::clicked,[&](){
        if(volumeSlider->isHidden()){
            volumeSlider->show();
        }
        else{
            volumeSlider->hide();
        }
    });
    QObject::connect(musicList,&QListWidget::itemClicked,this,&MainPage::UpdateMusic);
    QObject::connect(addMusic,&QPushButton::clicked,this,&MainPage::AddMusic);
    QObject::connect(diskScanner,&DiskScanner::scanMusic,musicListModel,&MusicListModel::appendMusicPathList);
    QObject::connect(diskScanner,&DiskScanner::scanLyrics,musicListModel,&MusicListModel::appendLyricsPathList);
    QObject::connect(musicListModel,&MusicListModel::newMusic,this,&MainPage::updateMusicListModel);
    QObject::connect(Music,&QMediaPlayer::sourceChanged,[&](){});
    QObject::connect(Music,&QMediaPlayer::positionChanged,this,&MainPage::UpdateLyric);

}

void MainPage::initMusicList()
{
    diskScanner->scan();
    musicListModel->loadLyrics();
}

void MainPage::initMusic()
{
    Music->setAudioOutput(OutPut);
    initMusicList();
    updateMusic(0);
    OutPut->setVolume(50);
}

void MainPage::updateMusic(int newMusicIndex)
{
    if(!musicListModel->isempty()&&newMusicIndex<musicListModel->pathSize()){
        CurrentMusicIndex=newMusicIndex;
        CurrentLyricsIndex=0;
        CurrentMusic=musicListModel->path_at(newMusicIndex);
        Music->setSource(QUrl::fromLocalFile(musicListModel->path_at(newMusicIndex)));
        currentMusicName->setText((QUrl::fromLocalFile(CurrentMusic)).fileName());
        if(musicListModel->lyric_at(CurrentMusicIndex,0)!="For the moment, there are no lyrics"){
            updateLyric(0);
        }
        else{
            lyricsDisplay->setText("For the moment, there are no lyrics");
        }
        musicList->setCurrentRow(newMusicIndex);
    }
}

void MainPage::updateLyric(int newLyricIndex)
{
    qDebug()<<newLyricIndex;
    if(newLyricIndex>=0&&newLyricIndex<musicListModel->lyricsSize(CurrentMusicIndex)-1){
        qDebug()<<"signal";
        qDebug()<<newLyricIndex;
        previewLyricTime=musicListModel->time_at(CurrentMusicIndex,newLyricIndex);
        nextLyricTime=musicListModel->time_at(CurrentMusicIndex,newLyricIndex+1);
        CurrentLyricsIndex=newLyricIndex;
        lyricsDisplay->setText(musicListModel->lyric_at(CurrentMusicIndex,newLyricIndex));
    }
}

void MainPage::NextMusic()
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
}

void MainPage::PreviewMusic()
{
    if(CurrentMusicIndex!=0)
    {
        CurrentMusicIndex-=1;
    }
    else
    {
        CurrentMusicIndex=musicListModel->pathSize()-1;
    }
    updateMusic(CurrentMusicIndex);
}

void MainPage::UpdateMusic(QListWidgetItem *item )
{
    int newMusicIndex=musicList->row(item);
    CurrentMusicIndex=newMusicIndex;
    CurrentMusic=musicListModel->path_at(newMusicIndex);
    updateMusic(newMusicIndex);
}

void MainPage::UpdateLyric()
{
    if(CurrentTime>=nextLyricTime&&!musicListModel->lyricsIsEmpty(CurrentMusicIndex)){
        while(CurrentTime>=nextLyricTime&&CurrentLyricsIndex<musicListModel->lyricsSize(CurrentMusicIndex)-2){
            updateLyric(CurrentLyricsIndex+1);
        }

    }
    else if(CurrentTime<previewLyricTime&&!musicListModel->lyricsIsEmpty(CurrentMusicIndex)&&CurrentLyricsIndex-1>=0){
        while(CurrentTime<previewLyricTime){
            updateLyric(CurrentLyricsIndex-1);
        }

    }
}

void MainPage::AddMusic()
{
    QString newMusic = QFileDialog::getOpenFileName(parent,"choose music","/home","(*.mp3)");
    if(!musicListModel->contains(newMusic)){
        musicListModel->appendMusicPath(newMusic);
    }
}


void MainPage::updateMusicListModel(QStringList newMusic)
{
    for(auto& path:newMusic){
        musicList->addItem(QUrl::fromLocalFile(path).fileName());
    }
}


