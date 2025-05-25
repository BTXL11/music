#include "mainwindow.h"
#include <QApplication>
#include <QLabel>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.initwindow(&w);
    w.initMusic();
    w.initconnect();
    w.show();
    return a.exec();
}
