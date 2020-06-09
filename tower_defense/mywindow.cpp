#include "mywindow.h"
#include "sbutton.h"
#include <QPainter>

MyWindow::MyWindow(QWidget *parent) : QMainWindow(parent)
{
     this->setFixedSize(800,600);
     SButton *setTower = new SButton(":/button1.png");
     setTower->setParent(this);
     setTower->move(500,500);
     connect(setTower,&SButton::clicked,this,&MyWindow::set_tower);
}

void MyWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    foreach(Tower * tower,tower_list)
        tower->draw(&painter);
}

void MyWindow::set_tower(){
    Tower * a_new_tower = new Tower(QPoint(200,200),":/tower.png");
    tower_list.push_back(a_new_tower);
    update();
}
