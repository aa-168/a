#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QTimer>

class MyWindow;
class Enemy;

class Tower : public QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos, MyWindow *game, const QPixmap &sprite = QPixmap(":/tower1.png"));
    ~Tower();
    void draw(QPainter *painter) const;
    void targetKilled();
    void checkEnemyInRange();
    void attackEnemy();
    void chooseEnemyForAttack(Enemy *enemy);

    void removeBullet();
    void damageEnemy();
    void lostSightOfEnemy();

private slots:
    void shootWeapon();
private:
    qreal			m_rotationSprite;
    Enemy *			m_chooseEnemy;
    MyWindow *	    m_game;
    QTimer *		m_fireRateTimer;
    QPoint          m_pos;
    QPixmap         m_sprite;
    int             m_attackRange;
    int             m_damage;
    int             m_fireRate;
    bool            m_attacking;
    static const QSize ms_fixedSize;
signals:


};

#endif // TOWER_H
