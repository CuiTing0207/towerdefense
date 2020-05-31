#include "window2.h"
#include "butt.h"
#include "monster.h"
#include <QPainter>
#include <Qtimer>
window2::window2(QWidget *parent) : QMainWindow(parent)
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
     newtower->move(100,100);
     connect(newtower,&butt::clicked,this,&window2::new_tower);

     butt *newmonster=new butt(":/button.png");//开始游戏的按钮
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
    //monster *monster1=new monster(QPoint(1000,350),":/monster1.gif");
    //monster1->paint(&painter);
    //monster *mt=new monster(QPoint(1000,350),":/monster1.gif");
    //monster_n.push_back(mt);

    QPixmap endpix(":/flag.png");
    painter.drawPixmap(100,350,100,150,endpix);//怪物终点的小旗子

    foreach(Tower *tower,tower_n)//tower绘制
        tower->paint(&painter);
    foreach(monster *monster,monster_n)//monster绘制
        monster->paint(&painter);

}

void window2::new_tower(){//新建塔
    Tower *nt=new Tower(QPoint(100,150),":/newtower1.png");

    tower_n.push_back(nt);
    update();
}

void window2::new_monster(){//新建怪物
    monster *mt=new monster(QPoint(1100,350),QPoint(100,350),":/monster1.gif");
    monster_n.push_back(mt);
    mt->move();
    update();
}

void window2::updatewindow(){//页面更新实现怪物移动
    update();
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
