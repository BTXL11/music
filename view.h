#ifndef VIEW_H
#define VIEW_H

#include "qpushbutton.h"
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include <QSlider>
class view {
public:
    view(QWidget *parent = nullptr );
    QPushButton *player;
    QPushButton *next;
    QPushButton *preview;
    QLabel *currentMusicName;
    QSlider *timeSlider;
    QLabel *time;
};

#endif // VIEW_H
