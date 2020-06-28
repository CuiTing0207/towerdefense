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
     butt *backbutt=new butt(":/button.png");//�ص�������İ�ť
     backbutt->setParent(this);
     backbutt->move(1000,700);
     connect(backbutt,&butt::clicked,this,[=](){
         emit back();
     });


     butt *newtower=new butt(":/button.png");//�����õİ�ť
     newtower->setParent(this);
     newtower->move(550,100);
     connect(newtower,&butt::clicked,this,&window2::new_tower);


     butt *newtower2=new butt(":/button.png");//����2�õİ�ť
     newtower2->setParent(this);
     newtower2->move(700,500);
     connect(newtower2,&butt::clicked,this,&window2::new_tower2);

     butt *newtower3=new butt(":/button.png");//����3�õİ�ť
     newtower3->setParent(this);
     newtower3->move(100,500);
     connect(newtower3,&butt::clicked,this,&window2::new_tower3);


//     butt *newmonster=new butt(":/start.png");//��ʼ��Ϸ�İ�ť
//     newmonster->setParent(this);
//     newmonster->move(550,550);
//     connect(newmonster,&butt::clicked,this,&window2::new_monster);


     QTimer *timer = new QTimer(this);
     connect(timer,&QTimer::timeout,this,&window2::updatewindow);
     timer->start(30);

      //QTimer *timerm=new QTimer(this);
      timerm=new QTimer;
      connect(timerm,&QTimer::timeout,this,&window2::new_monster);
      timerm->start(2000);//2�����һ������

      QTimer *stopm=new QTimer(this);//����ֹͣ
      connect(stopm,SIGNAL(timeout()),this,SLOT(stopMonster()));
      stopm->setSingleShot(true);
      stopm->start(30000);//һ����ʮ��


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
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);//����ͼƬ����

    QPixmap endpix(":/flag.png");
    painter.drawPixmap(100,350,100,150,endpix);//�����յ��С����
    textshow(&painter);//����ַ�

    foreach(Tower *tower,tower_n)//tower����
        tower->paint(&painter);

    foreach(monster1 *mt,monster1_n)
        mt->paint(&painter);
    foreach(Bullet *bullet,bullet_n)
        bullet->draw(&painter);

}

void window2::new_tower(){//�½���
    if(coin>=300)
    {
        coin-=300;
    Tower *nt=new Tower(this,QPoint(550,250),":/pri_tower.png");

    tower_n.push_back(nt);
    update();
    }
}

void window2::new_tower2(){//�½��߼���
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

void window2::new_tower3(){//�½���
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

void window2::new_monster(){//�½�����

    monster1 *mt=new monster1(this,QPoint(1100,350),QPoint(100,350),":/monster1.gif");
    monster1_n.push_back(mt);
    update();
}

void window2::updatewindow(){//ҳ�����ʵ�ֹ����ƶ�
    foreach(monster1 *mt,monster1_n)
        mt->move();
    foreach(Tower *tower,tower_n)
       tower->findMonsterInRange();
    update();
}

void window2::textshow(QPainter *painter){//��ʾ����
    painter->save();
    painter->setPen(Qt::white);//��ʾ��ʾ���
    painter->drawText(QRect(350,100,150,100),QString("Click the button to set tower"));
    painter->setPen(QPen(Qt::red));//��ʾ���Hp
    painter->drawText(QRect(30, 5, 100, 25), QString("HP : %1").arg(playerHp));
    painter->setPen(QPen(Qt::red));//��ʾ��ҽ��
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

            // ��Ϸʤ��


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
