#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include "tower.h"
#include <QList>
class MyWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void set_tower();
private:
    QList<Tower*> tower_list;
signals:
    //void chooseBack();
public slots:
};

#endif // MYWINDOW_H
