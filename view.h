#ifndef VIEW_H
#define VIEW_H

#include <QPushButton>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include <QSlider>
class view {
public:
    view(QWidget *parent );
    QPushButton *player;
    QPushButton *next;
    QPushButton *preview;
    QLabel *currentMusicName;
    QSlider *timeSlider;
    QSlider *volumeSlider;
    QPushButton *volumeButton;
    QLabel *time;
};

#endif // VIEW_H
