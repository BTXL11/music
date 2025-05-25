#include "view.h"

view::view(QWidget *parent) {
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
    //time->setText("00:00/00:00");
    time->move(325,300);
    time->resize(200,50);
    volumeSlider = new QSlider(parent);
    volumeSlider->setMaximum(100);
    volumeSlider->move(425,200);
    volumeSlider->resize(10,100);
    volumeSlider->hide();
    volumeButton = new QPushButton(parent);
    volumeButton->move(425,300);
    volumeButton->setText("volume");
    qDebug()<<"signal";

}
