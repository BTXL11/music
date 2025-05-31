#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MainPage.h"
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
#include <QTime>
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>
#include <QModelIndex>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFileDialog>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow  {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    MainPage* MainPage;



};


#endif // MAINWINDOW_H
