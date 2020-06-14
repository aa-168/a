#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include "tower.h"
#include <QList>
#include "myobject.h"
#include "myobject2.h"
class MyWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void set_tower();
    void addMyObject();
    void updateScene();
private:
    QList<Tower*> tower_list;
    QList<MyObject*> object_list;
    QList<MyObject2*> object2_list;
signals:
    //void chooseBack();
public slots:
};

#endif // MYWINDOW_H
