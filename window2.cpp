#include "window2.h"
#include "butt.h"

#include "monster1.h"
#include "bullet.h"
#include <QPainter>
#include <Qtimer>

#include <QtDebug>

static const int TowerCost = 300;

window2::window2(QWidget *parent) : QMainWindow(parent),waves(0),playerHp(5),coin(1000),gamelose(false),gamewin(false)
{
      this->setFixedSize(1200,800);
     butt *backbutt=new butt(":/button.png");//回到主界面的按钮
     backbutt->setParent(this);
     backbutt->move(1000,700);
     connect(backbutt,&butt::clicked,this,[=](){
         emit back();
     });


     butt *newtower=new butt(":/button.png");//建塔用的按钮
     newtower->setParent(this);
     newtower->move(550,100);
     connect(newtower,&butt::clicked,this,&window2::new_tower);


     butt *newtower2=new butt(":/button.png");//建塔2用的按钮
     newtower2->setParent(this);
     newtower2->move(700,500);
     connect(newtower2,&butt::clicked,this,&window2::new_tower2);

     butt *newtower3=new butt(":/button.png");//建塔3用的按钮
     newtower3->setParent(this);
     newtower3->move(100,500);
     connect(newtower3,&butt::clicked,this,&window2::new_tower3);


//     butt *newmonster=new butt(":/start.png");//开始游戏的按钮
//     newmonster->setParent(this);
//     newmonster->move(550,550);
//     connect(newmonster,&butt::clicked,this,&window2::new_monster);


     QTimer *timer = new QTimer(this);
     connect(timer,&QTimer::timeout,this,&window2::updatewindow);
     timer->start(30);

      //QTimer *timerm=new QTimer(this);
      timerm=new QTimer;
      connect(timerm,&QTimer::timeout,this,&window2::new_monster);
      timerm->start(2000);//2秒产生一个怪物

      QTimer *stopm=new QTimer(this);//怪物停止
      connect(stopm,SIGNAL(timeout()),this,SLOT(stopMonster()));
      stopm->setSingleShot(true);
      stopm->start(30000);//一共三十秒


}

void window2::paintEvent(QPaintEvent *){
    if (gamewin || gamelose)
    {
        QString text = gamelose ? "YOU LOST!!!" : "YOU WIN!!!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
    }
    QPainter painter(this);
    QPixmap pixmap(":/level1.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);//背景图片绘制

    QPixmap endpix(":/flag.png");
    painter.drawPixmap(100,350,100,150,endpix);//怪物终点的小旗子
    textshow(&painter);//输出字符

    foreach(Tower *tower,tower_n)//tower绘制
        tower->paint(&painter);

    foreach(monster1 *mt,monster1_n)
        mt->paint(&painter);
    foreach(Bullet *bullet,bullet_n)
        bullet->draw(&painter);

}

void window2::new_tower(){//新建塔
    if(coin>=300)
    {
        coin-=300;
    Tower *nt=new Tower(this,QPoint(550,250),":/pri_tower.png");

    tower_n.push_back(nt);
    update();
    }
}

void window2::new_tower2(){//新建高级塔
    if(coin>=400)
    {
        coin-=400;
    Tower *nt=new Tower(this,QPoint(800,500),":/best_tower.png");
    nt->damage=10;
    nt->setRate(300);
    nt->setRange(300);
    tower_n.push_back(nt);
    update();
    }
}

void window2::new_tower3(){//新建塔
    if(coin>=400)
    {
        coin-=400;
    Tower *nt=new Tower(this,QPoint(200,500),":/newtower1.png");
    nt->damage=10;
    nt->setRate(500);
    nt->setRange(300);
//    if(nt->chosenmonster())
//        nt->chosenmonster()->setSpeed(1.0);
    tower_n.push_back(nt);
    update();
    }
}

void window2::new_monster(){//新建怪物

    monster1 *mt=new monster1(this,QPoint(1100,350),QPoint(100,350),":/monster1.gif");
    monster1_n.push_back(mt);
    update();
}

void window2::updatewindow(){//页面更新实现怪物移动
    foreach(monster1 *mt,monster1_n)
        mt->move();
    foreach(Tower *tower,tower_n)
       tower->findMonsterInRange();
    update();
}

void window2::textshow(QPainter *painter){//显示文字
    painter->save();
    painter->setPen(Qt::white);//显示提示语句
    painter->drawText(QRect(350,100,150,100),QString("Click the button to set tower"));
    painter->setPen(QPen(Qt::red));//显示玩家Hp
    painter->drawText(QRect(30, 5, 100, 25), QString("HP : %1").arg(playerHp));
    painter->setPen(QPen(Qt::red));//显示玩家金币
    painter->drawText(QRect(200, 5, 200, 25), QString("COIN : %1").arg(coin));
    painter->restore();
}
void window2::removedMonster(monster1 *mt)
{
    Q_ASSERT(mt);

    monster1_n.removeOne(mt);

    delete mt;


    if (monster1_n.empty())
    {

            gamewin = true;

            // 游戏胜利


    }
}
void window2::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    bullet_n.removeOne(bullet);
    delete bullet;
}

void window2::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    bullet_n.push_back(bullet);
}

void window2::awardCoin(int coin1)
{
    coin += coin1;
    update();
}
void window2::getHpDamage(int damage/* = 1*/)
{

    playerHp -= damage;
    if (playerHp <= 0)
    gamelose=true;
}

void window2::stopMonster(){
    timerm->stop();
}
