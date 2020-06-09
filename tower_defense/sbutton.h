#ifndef SBUTTON_H
#define SBUTTON_H

#include <QWidget>
#include <QPushButton>
class SButton : public QPushButton
{
    Q_OBJECT
public:
    SButton(QString pix);
    void btup();
    void btdown();
signals:

public slots:
};


#endif // SBUTTON_H
