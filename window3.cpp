#include "window3.h"
#include "butt.h"
#include <QPainter>
#include "buttnew.h"
#include <QDebug>
window3::window3(QWidget *parent) : QMainWindow(parent)
{
   this->setFixedSize(1200,800);
    butt *backbutt2=new butt(":/button.png");//回到主界面的按钮
    backbutt2->setParent(this);
    backbutt2->move(1000,200);
    connect(backbutt2,&butt::clicked,this,[=](){
        emit back();

    });

   // butt *newtower=new butt(":/button.png");//建塔用的按钮
   // newtower->setParent(this);
   // newtower->move(200,100);
   // connect(newtower,&butt::clicked,this,&window3::new_tower);
    buttnew *menubutt=new buttnew(":/button.png");
    menubutt->setParent(this);
    menubutt->move(200,100);
    //connect(menubutt,&buttnew::chooseac1,this,[=](){
     //   qDebug()<<"Tower set!!";
    //});
    connect(menubutt,&buttnew::chooseac1,this,&window3::new_tower);
}


void window3::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/level2.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);//绘制背景图片
    foreach(Tower *tower,tower_n)//tower绘制
        tower->paint(&painter);
    textshow(&painter);
}

void window3::new_tower(){//新建塔
    Tower *nt=new Tower(QPoint(100,150),":/newtower1.png");

    tower_n.push_back(nt);
    update();
}

void window3::textshow(QPainter *painter){
    painter->save();
    painter->setPen(Qt::white);
    //painter->drawText(QRect(550,500,150,50),QString("num1:%1 num2:%2").arg(num1).arg(num2));
    painter->drawText(QRect(280,100,150,100),QString("Right-Click the button to set tower"));
    painter->restore();
}
