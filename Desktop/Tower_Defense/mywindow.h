#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include "towerposition.h"
#include "tower.h"
#include <QList>
#include <QMouseEvent>

class Enemy;
class Sbutton;
class WayPoint;
class Tower;
class Bullet;

class MyWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyWindow(QWidget *parent = nullptr);
    ~MyWindow();
    void paintEvent(QPaintEvent*);
    void updateScene();
    void showinfo(QPainter *);
    void loadTowerPositions();
    void mousePressEvent(QMouseEvent *event);
    void addWayPoints();
    bool loadwave();
    void addBullet(Bullet *bullet);
    void removedBullet(Bullet *bullet);
    void removedEnemy(Enemy *enemy);
    QList<Enemy *> enemyList() const;
    void awardGold(int gold);
    void getHpDamage(int damage = 1);
    bool canBuyTower() const;
    void doGameOver();
private:

    int	m_playerHp;
    int	m_playerGold;
    bool m_gameEnded;
    bool m_gameWin;
    int m_waves;
    QList<Enemy*> enemy_list;
    QList<WayPoint*> wayPoint_list;
    QList<TowerPosition> towerPosition_list;
    QList<Tower*> tower_list;
    QList<Bullet*> bullet_list;
signals:
    void chooseBack();
private slots:
    void gameStart();
};

#endif // MYWINDOW_H
