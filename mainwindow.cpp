#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qpainter>
#include <Qpixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QtDebug>
#include "butt.h"
#include "window2.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(1200,800);
    ui->setupUi(this);
    butt *butt1 =new butt(":/button.png");
    butt1->setParent(this);
    butt1->move(1000,700);
    window2 *scene2=new window2;
    connect(butt1,&QPushButton::clicked,this,[=](){
        this->hide();
        scene2->show();
    });
    connect(scene2,&window2::back,this,[=](){
        scene2->hide();
        this->show();
    });
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

}
