#include "enemy.h"
#include "waypoint.h"
#include "utility.h"
#include "tower.h"
#include "mywindow.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>
#include "utility.h"

static const int Health_Bar_Width = 20;

const QSize Enemy::ms_fixedSize(38,38);

Enemy::Enemy(WayPoint *startWayPoint,MyWindow *game, const QPixmap &sprite)
    : QObject(0), m_pos(startWayPoint->pos()),m_sprite(sprite)
{
    m_maxHp = 40;
    m_currentHp = 40;
    m_active = false;
    m_walkingSpeed = 1.0;
    m_destinationWayPoint = startWayPoint->nextWayPoint();
    m_rotationSprite = 0.0;
    m_game = game;
}

void Enemy::draw(QPainter *painter) const
{
    if (!m_active)
        return;

    painter->save();
    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 3 - 6, -ms_fixedSize.height() / 2);
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 2));
    painter->drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    // 绘制敌人
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

Enemy::~Enemy()
{
    m_attackedTowersList.clear();
    m_destinationWayPoint = NULL;
    m_game = NULL;
}

void Enemy::doActivate()
{
    m_active = true;
}

void Enemy::move()
{
    if (!m_active)
        return;

    if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
    {

        if (m_destinationWayPoint->nextWayPoint())
        {

            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        }
        else
        {
            m_game->getHpDamage();
            m_game->removedEnemy(this);
            return;
        }
    }

    QPoint targetPoint = m_destinationWayPoint->pos();

    qreal movementSpeed = m_walkingSpeed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * movementSpeed;
}

void Enemy::getRemoved()
{
    if (m_attackedTowersList.empty())
        return;

    foreach (Tower *attacker, m_attackedTowersList)
        attacker->targetKilled();
    m_game->removedEnemy(this);
}

void Enemy::getDamage(int damage)
{
    m_currentHp -= damage;
    if (m_currentHp <= 0)
    {
        m_game->awardGold(100);
        getRemoved();
    }
}

void Enemy::getAttacked(Tower *attacker)
{
    m_attackedTowersList.push_back(attacker);
}

void Enemy::getLostSight(Tower *attacker)
{
    m_attackedTowersList.removeOne(attacker);
}

QPoint Enemy::pos() const
{
    return m_pos;
}

