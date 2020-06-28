#include "bullet.h"
#include "mywindow.h"
#include "enemy.h"
#include <QPainter>
#include <QPropertyAnimation>

Bullet::Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
               MyWindow *game, const QPixmap &sprite)
    : m_startPos(startPos)
    , m_targetPos(targetPoint)
    , m_sprite(sprite)
    , m_currentPos(startPos)
    , m_target(target)
    , m_game(game)
    , m_damage(damage)
{}

const QSize Bullet::ms_fixedSize(8,8);

void Bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(m_currentPos,m_sprite);
}

void Bullet::move()
{
    static const int duration = 100;//100ms击中
    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));
    animation->start();
}

void Bullet::hitTarget()
{
    // 先判断敌人是否存活
    if (m_game->enemyList().indexOf(m_target) != -1)
        m_target->getDamage(m_damage);
    m_game->removedBullet(this);
}

QPoint Bullet::currentPos() const
{
    return m_currentPos;
}

void Bullet::setCurrentPos(QPoint pos)
{
    m_currentPos = pos;
}

