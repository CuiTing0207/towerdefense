#include "window2.h"
#include "butt.h"
#include "monster.h"
#include "monster1.h"
#include <QPainter>
#include <Qtimer>
#include "window3.h"
window2::window2(QWidget *parent) : QMainWindow(parent)
{
      this->setFixedSize(1200,800);
     butt *backbutt=new butt(":/button.png");//回到主界面的按钮
     backbutt->setParent(this);
     backbutt->move(1000,700);
     connect(backbutt,&butt::clicked,this,[=](){
         emit back();
     });
     //butt *butt2 =new butt(":/button.png");//到第二关的按钮（应该让它胜利后出现）
     //butt2->setParent(this);
     //butt2->move(1000,200);
     //window3 *scene3=new window3;
     //connect(butt2,&QPushButton::clicked,this,[=](){
        // this->hide();
         //scene3->show();
    // });

     butt *newtower=new butt(":/button.png");//建塔用的按钮
     newtower->setParent(this);
     newtower->move(250,100);
     connect(newtower,&butt::clicked,this,&window2::new_tower);



     butt *newmonster=new butt(":/start.png");//开始游戏的按钮
     newmonster->setParent(this);
     newmonster->move(550,350);
     connect(newmonster,&butt::clicked,this,&window2::new_monster);




    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&window2::updatewindow);
    timer->start(30);




}

void window2::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/level1.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);//背景图片绘制

    QPixmap endpix(":/flag.png");
    painter.drawPixmap(100,350,100,150,endpix);//怪物终点的小旗子
    textshow(&painter);//输出字符

    foreach(Tower *tower,tower_n)//tower绘制
        tower->paint(&painter);
    foreach(monster *monster,monster_n)//monster绘制
        monster->paint(&painter);
    foreach(monster1 *mt,monster1_n)
        mt->paint(&painter);

}

void window2::new_tower(){//新建塔
    Tower *nt=new Tower(QPoint(250,150),":/pri_tower.png");

    tower_n.push_back(nt);
    update();
}

void window2::new_monster(){//新建怪物

    monster1 *mt=new monster1(QPoint(1100,350),QPoint(100,350),":/monster1.gif");
    monster1_n.push_back(mt);
    update();
}

void window2::updatewindow(){//页面更新实现怪物移动
    foreach(monster1 *mt,monster1_n)
        mt->move();
    update();
}

void window2::textshow(QPainter *painter){
    painter->save();
    painter->setPen(Qt::white);
    //painter->drawText(QRect(550,500,150,50),QString("num1:%1 num2:%2").arg(num1).arg(num2));
    painter->drawText(QRect(350,100,150,100),QString("Click the button to set tower"));
    painter->restore();
}

/*bool window2::loadwave(){
    int monsterInterval[]={100,200,300,400,500,600};
    for (int i=0;i<6;++i){
        monster *mt=new monster(QPoint(1000,350),":/monster1.gif");
        monster_n.push_back(mt);
        QTimer::singleShot(monsterInterval[i],mt,SLOT(dogo));
    }
}
void window2::dogo(){

}*/



/*void window2::selfmove(){
    int d=3;
    foreach(monster *monster,monster_n)
    monster->move(d);


    update();
}*/
