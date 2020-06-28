#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include "waypoint.h"
#include "mywindow.h"
#include "tower.h"

class MyWindow;
class Tower;

class Enemy : public QObject
{
    Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, MyWindow *game,const QPixmap &sprite);
    ~Enemy();
    void draw(QPainter *painter)const;
    void move();
    void getDamage(int damage);
    void getRemoved();
    QPoint pos() const;

    void getLostSight(Tower *attacker);
    void getAttacked(Tower *attacker);
public slots:
    void doActivate();
private:
    bool            m_active;
    int             m_maxHp;
    int             m_currentHp;
    qreal           m_walkingSpeed;
    qreal			m_rotationSprite;
    QPoint			m_pos;
    WayPoint *		m_destinationWayPoint;
    MyWindow *	    m_game;
    QList<Tower *>  m_attackedTowersList;
    const QPixmap   m_sprite;
    static const QSize    ms_fixedSize;

    //
    //QList<Tower *>
};

#endif // ENEMY_H
