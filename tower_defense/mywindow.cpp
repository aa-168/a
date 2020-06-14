#include "mywindow.h"
#include "sbutton.h"
#include <QPainter>
#include <QTimer>
#include <myobject2.h>

MyWindow::MyWindow(QWidget *parent) : QMainWindow(parent)
{
     this->setFixedSize(800,600);
     SButton *setTower = new SButton(":/settower.png");
     setTower->setParent(this);
     setTower->move(600,80);
     connect(setTower,&SButton::clicked,this,&MyWindow::set_tower);
     connect(setTower,&SButton::clicked,this,&MyWindow::addMyObject);
     QTimer * timer = new QTimer (this);
     connect(timer,&QTimer::timeout,this,&MyWindow::updateScene);
      timer->start(10);
}

void MyWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/map.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    foreach(Tower * tower,tower_list)
        tower->draw(&painter);
    foreach(MyObject * object,object_list)
        object->draw(&painter);
    foreach(MyObject2* object,object2_list)
        object->draw(&painter);
}

void MyWindow::set_tower(){
    Tower * a_new_tower = new Tower(QPoint(400,300),":/tower.png");
    tower_list.push_back(a_new_tower);
    update();
}

void MyWindow::addMyObject(){
    MyObject2* object = new MyObject2(QPoint(760,40),QPoint(560,40),":/monster1.png");
    object2_list.push_back(object);
    object->move();
    update();
}

void MyWindow::updateScene(){
    foreach(MyObject2* object,object2_list)
        object->move();
    update();
}
