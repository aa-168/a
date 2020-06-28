#include "mywindow.h"
#include "ui_mainwindow.h"
#include "sbutton.h"
#include "mainwindow.h"
#include "towerposition.h"
#include "waypoint.h"
#include <tower.h>
#include <QPainter>
#include <QTimer>
#include <myobject2.h>
#include "enemy.h"
#include "bullet.h"

static const int TowerCost = 100;

MyWindow::MyWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_waves(0)
    , m_playerHp(5)
    , m_playerGold(400)
    , m_gameEnded(false)
    , m_gameWin(false)
{
     this->setFixedSize(800,600);
     loadTowerPositions();
     addWayPoints();
     SButton * startwave = new SButton(":/button1.png");
     startwave->setParent(this);
     startwave->move(100,40);
     connect(startwave, SIGNAL(clicked()),this,SLOT(gameStart()));

     QTimer * timer = new QTimer (this);
     connect(timer,&QTimer::timeout,this,&MyWindow::updateScene);
      timer->start(10);
}

MyWindow::~MyWindow()
{

}



void MyWindow::paintEvent(QPaintEvent *){
    if(m_gameEnded || m_gameWin)
    {
        QString text = m_gameEnded ? "YOU LOST!!!" : "YOU WIN!!!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
    }
    QPixmap pixmap(":/map.jpg");
    QPainter painter(this);

    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    foreach(const TowerPosition &towerPos, towerPosition_list)
        towerPos.draw(&painter);
    foreach(Tower *tower,tower_list)
        tower->draw(&painter);
    foreach(WayPoint *wp,wayPoint_list)
        wp->draw(&painter);
    foreach (const Enemy *enemy, enemy_list)
        enemy->draw(&painter);
    foreach(const Bullet *bullet,bullet_list)
        bullet->draw(&painter);
    showinfo(&painter);
}

bool MyWindow::canBuyTower() const
{
    if(m_playerGold >= TowerCost)
        return true;
    return false;
}

void MyWindow::getHpDamage(int damage)
{
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

void MyWindow::showinfo(QPainter *painter){
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(10,50,2000,50),QString("money:%1").arg(m_playerGold));
    painter->drawText(QRect(10,100,2000,50),QString("health:%2").arg(m_playerHp));
    painter->restore();
}

void MyWindow::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;
    }
}

void MyWindow::awardGold(int gold)
{
    m_playerGold += gold;
    update();
}


void MyWindow::loadTowerPositions()
{
    QPoint pos[] =
    {
        QPoint(680,80),
        QPoint(520,120),
        QPoint(600,200),
        QPoint(480,240),
        QPoint(360,320),
        QPoint(240,240),
        QPoint(160,360),
        QPoint(80,400)
    };
    int num = sizeof(pos)/sizeof(pos[0]);
    for(int i = 0;i < num;i++)
        towerPosition_list.push_back(pos[i]);
}

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos = event->pos();
    auto it = towerPosition_list.begin();
    while(it != towerPosition_list.end())
    {
        if(canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {
            it -> setHasTower();
            m_playerGold -= TowerCost;
            QPoint centerpoint = it->centerPos();
            QPoint point(20,20);
            centerpoint = centerpoint - point;
            Tower *tower = new Tower(it->centerPos(), this);
            tower_list.push_back(tower);
            update();
        }
        ++it;
    }
}

void MyWindow::addWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(20, 460));
    wayPoint_list.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(220, 460));
    wayPoint_list.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(220, 300));
    wayPoint_list.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(580, 300));
    wayPoint_list.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(580, 60));
    wayPoint_list.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(780, 60));
    wayPoint_list.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);
}

bool MyWindow::loadwave()
{
    if (m_waves >= 6)
        return false;

    if(m_waves<=3)
    {
        WayPoint *startPoint = wayPoint_list.back();
        int enemy_start_interval[]={1000,3000,5000,6000,7000,8000};
        for(int i=0;i<6;++i)
        {
            Enemy *enemy=new Enemy(startPoint,this,QPixmap(":/monster1.png"));
            enemy_list.push_back(enemy);
            QTimer::singleShot(enemy_start_interval[i],enemy,SLOT(doActivate()));
        }
    }
    if(m_waves>3){
        WayPoint * startPoint =wayPoint_list.back();
        int enemy_start_interval[]={1000,3000,5000,6000,7000,8000};
        for(int i=0;i<6;++i){
            Enemy *enemy=new Enemy(startPoint,this,QPixmap(":/monster1.png"));
            enemy_list.push_back(enemy);
            QTimer::singleShot(enemy_start_interval[i],enemy,SLOT(doActivate()));
        }
    }
    return true;
}

void MyWindow::gameStart()
{
    loadwave();
}

void MyWindow::updateScene(){
    foreach(Enemy *enemy,enemy_list)
        enemy->move();
    foreach (Tower *tower, tower_list)
        tower->checkEnemyInRange();
    update();
}

void MyWindow::addBullet(Bullet *bullet){
    Q_ASSERT(bullet);

    bullet_list.push_back(bullet);
}

void MyWindow::removedBullet(Bullet *bullet){
    Q_ASSERT(bullet);

    bullet_list.removeOne(bullet);
    delete bullet;
}

QList<Enemy *> MyWindow::enemyList() const
{
    return enemy_list;
}

void MyWindow::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    enemy_list.removeOne(enemy);
    delete enemy;

    if (enemy_list.empty())
    {
        ++m_waves;
        if (!loadwave())
        {
            m_gameWin = true;

        }
    }
}
