#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>

class Monster : public QObject
{
    Q_OBJECT
public:
    explicit Monster(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MONSTER_H