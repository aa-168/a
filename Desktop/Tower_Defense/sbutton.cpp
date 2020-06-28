#include "sbutton.h"
#include <QPixmap>
#include <QPropertyAnimation>

SButton::SButton(QString pix):QPushButton(0){
   QPixmap pixmap(pix);
   this->setFixedSize(pixmap.width(),pixmap.height());
   this->setStyleSheet("QPushButton{border:Opx;}");
   this->setIcon(pixmap);
   this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}

void SButton::btdown(){
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+5,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void SButton::btup(){
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+5,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
