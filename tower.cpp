#include "tower.h"
#include "monster1.h"
#include "window2.h"
#include "bullet.h"
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QVector2D>
#include <QtMath>
#include <QTimer>

Tower::Tower(window2 *game1,QPoint pos,QString addr):QObject (0),pixmap(addr),range(200),rate(500),damage(5),chooseMonster(NULL),game(game1)
{
    _pos=pos;
    rateTimer=new QTimer(this);
    connect(rateTimer, SIGNAL(timeout()), this, SLOT(shoot()));
}
Tower::~Tower()
{
    delete rateTimer;
    rateTimer = NULL;
}

void Tower::findMonsterInRange(){
    if (chooseMonster)
    {


        if (chooseMonster->currentPos.x()<this->_pos.x()-this->range||chooseMonster->currentPos.x()>this->_pos.x()+this->range)// 如果敌人不在攻击范围内
            lostMonster();
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
        QList<monster1 *> monsterList = game->monster1_n;
        foreach (monster1 *monster, monsterList)
        {
            if (monster->currentPos.x()<this->_pos.x()+this->range && monster->currentPos.x()>this->_pos.x()-this->range)
            {
                chooseMonsterForAttack(monster);
                break;
            }
        }
    }
}

void Tower::paint(QPainter *painter){

    painter->save();
    painter->setPen(Qt::white);
    // 绘制攻击范围
    painter->drawEllipse(QPoint(_pos.x()+50,_pos.y()+50), range, range);
    //绘制图片
    QSize pixSize(100,100);
    QPixmap scaledPixmap =pixmap.scaled(pixSize,Qt::KeepAspectRatio);
    painter->drawPixmap(_pos,scaledPixmap);
    painter->setPen(QPen(Qt::red));//显示塔的参数
    painter->drawText(QRect(_pos.x(), _pos.y()-75, 150, 25), QString("RATE : %1").arg(rate));
    painter->drawText(QRect(_pos.x(), _pos.y()-50, 150, 25), QString("DAMAGE : %1").arg(damage));
    painter->drawText(QRect(_pos.x(), _pos.y()-25, 150, 25), QString("RANGE : %1").arg(range));
    painter->restore();
}
void Tower::attackMonster()
{
    rateTimer->start(rate);
}

void Tower::chooseMonsterForAttack(monster1 *monster)
{
    chooseMonster = monster;
    attackMonster();
    chooseMonster->getAttacked(this);
}

void Tower::shoot()
{
    Bullet *bullet = new Bullet(_pos, chooseMonster->currentPos, damage, chooseMonster, game);
    bullet->move();
    chooseMonster->getDamage(damage);
    game->addBullet(bullet);
}

void Tower::targetKilled()
{
    if (chooseMonster)
        chooseMonster = NULL;

    rateTimer->stop();
    //m_rotationSprite = 0.0;
}

void Tower::lostMonster()
{
    chooseMonster->gotLostSight(this);
    if (chooseMonster)
        chooseMonster = NULL;

    rateTimer->stop();
    //m_rotationSprite = 0.0;
}

void Tower::setRate(int r){
    this->rate=r;
}

void Tower::setRange(int r){
    this->range=r;
}

//monster1* Tower::chosenmonster(){

//        return chooseMonster;
//}
