#include "monster1.h"
#include "tower.h"
#include "window2.h"
#include <QPoint>
#include <QVector2D>
#include <QPainter>

monster1::monster1(window2 *game1,QPoint startpos,QPoint endpos,QString addr):QObject (0),pixmap(addr),currentHp(50),game(game1)
{
    this->currentPos=startpos;
    this->startPos=startpos;
    this->endPos=endpos;
    speed=2.0;
}
monster1::~monster1()
{
    attackedTowersList.clear();
    //endPos = currentPos;
    game = NULL;
}

void monster1::move(){
    QVector2D vector(endPos-startPos);//确定方向
    vector.normalize();
    currentPos=currentPos+vector.toPoint()*speed;
    if(currentPos==endPos)
    {this->speed=0;
     game->getHpDamage();
     game->removedMonster(this);
    }
    //加限制让它到了终点停下来
}

void monster1::paint(QPainter *painter){
    //painter->drawPixmap(currentPos,pixmap);
    painter->drawPixmap(currentPos.rx(),currentPos.ry(),100,100,pixmap);
    //painter->restore();
    qreal width=pixmap.width();
    qreal height=pixmap.height();
    pixmap=pixmap.scaled(width,height,Qt::KeepAspectRatio);
}
void monster1::getRemoved()
{
    if (attackedTowersList.empty())
        return;

    foreach (Tower *attacker, attackedTowersList)
        attacker->targetKilled();
    // 通知game,此敌人已经阵亡
    game->removedMonster(this);
}

void monster1::getDamage(int damage)
{

    currentHp -= damage;

    // 阵亡,需要移除
    if (currentHp <= 0)
    {

        game->awardCoin(200);
        getRemoved();
    }
}

void monster1::getAttacked(Tower *attacker)
{
    attackedTowersList.push_back(attacker);
}

void monster1::gotLostSight(Tower *attacker)
{
    attackedTowersList.removeOne(attacker);
}

void monster1::setSpeed(qreal s){
    this->speed=s;
}
