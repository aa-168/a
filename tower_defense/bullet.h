#ifndef BULLET_H
#define BULLET_H

#include <QObject>

class Bullet : public QObject
{
    Q_OBJECT
public:
    explicit Bullet(QObject *parent = nullptr);

signals:

public slots:
};

#endif // BULLET_H