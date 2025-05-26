#ifndef VIEW_H
#define VIEW_H

#include <QPushButton>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include <QSlider>
#include <QAbstractListModel>
class view {
public:
    view(QAbstractItemModel *model,QWidget *parent );
    QPushButton *player;
    QPushButton *player2;
    QPushButton *next;
    QPushButton *preview;
    QLabel *currentMusicName;
    QSlider *timeSlider;
    QSlider *volumeSlider;
    QPushButton *volumeButton;
    QLabel *time;
};

#endif // VIEW_H
