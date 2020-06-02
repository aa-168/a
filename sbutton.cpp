#include "sbutton.h"
#include <QPixmap>
SButton::SButton(QString pix):QPushButton(0){
   QPixmap pixmap(pix);
   this->setFixedSize(pixmap.width(),pixmap.height());
   this->setStyleSheet("QPushButton{border:Opx;}");
   this->setIcon(pixmap);
   this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}
