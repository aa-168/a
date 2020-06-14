#ifndef MYOBJECT2_H
#define MYOBJECT2_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
class MyObject2 : public QObject
{
    Q_OBJECT
public:
    MyObject2(QPoint startPos,QPoint sargetPos,QString fileName);
    void move();
    void draw(QPainter *painter);
private:
    QPoint startPos;
    QPoint targetPos;
    QPoint currentPos;
    QPixmap pixmap;
    qreal speed;
signals:

public slots:
};

#endif // MYOBJECT2_H
