#include "myobject2.h"
#include <QVector2D>
#include <QPainter>
#include <QPoint>

MyObject2::MyObject2(QPoint startPos,QPoint sargetPos,QString fileName):QObject(0),pixmap(fileName)
{
    this->currentPos = startPos;
    this->startPos = startPos;
    this->targetPos = targetPos;
    speed = 1.0;
}

void MyObject2::move(){
    QVector2D trace(targetPos - startPos);
    trace.normalize();
    currentPos = currentPos + trace.toPoint()*speed;
}

void MyObject2::draw(QPainter *painter){
    painter->drawPixmap(currentPos,pixmap);
}
