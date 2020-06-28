#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qpainter>
#include <Qpixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QtDebug>
#include "butt.h"
#include "window2.h"

#include <QMediaPlayer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(1200,800);
    ui->setupUi(this);
    butt *butt1 =new butt(":/start.png");//����һ�صİ�ť
    butt1->setParent(this);
    butt1->move(1000,700);
    window2 *scene2=new window2;
    connect(butt1,&QPushButton::clicked,this,[=](){
        this->hide();
        scene2->show();
    });
    connect(scene2,&window2::back,this,[=](){//��һ�ط���
        scene2->hide();
        this->show();
    });

//    butt *butt2 =new butt(":/butt2.png");//���ڶ��صİ�ť
//    butt2->setParent(this);
//    butt2->move(1100,700);
//    window3 *scene3=new window3;
//    connect(butt2,&QPushButton::clicked,this,[=](){
//        this->hide();
//        scene3->show();
//    });

//    connect(scene3,&window3::back,this,[=](){//�ڶ��ط���������
//        scene3->hide();
//        this->show();
//    });

    QMediaPlayer * player = new QMediaPlayer;//����������
    player->setMedia(QUrl("qrc:/bgm1.mp3"));
    player->setVolume(30);
    player->play();

  //  QPushButton *butt =new QPushButton(this);
   // butt->setFixedSize(50,50);
    //butt->move(700,500);
    //connect(butt,&QPushButton::clicked,this,&QMainWindow::close);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/shanyi.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    textshow(&painter);//����ַ�
}

void MainWindow::textshow(QPainter *painter){//��ʾ��Ҫ˵��

        painter->save();
        painter->setPen(Qt::yellow);

        painter->drawText(QRect(830,650,350,50),QString("CLICK BELOW TO START GAME!"));//ѡ��ؿ�����ʾ
        painter->restore();

}
