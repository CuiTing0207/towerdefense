#include "monster.h"
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QMovie>

monster::monster(QPoint startpos,QPoint endpos,QString addr):QObject (0),pixmap(addr)
{
    this->currentPos=startpos;
    this->startPos=startpos;
    this->endPos=endpos;
    speed=10;
}

void monster::paint(QPainter *painter){
    painter->drawPixmap(currentPos.rx(),currentPos.ry(),100,100,pixmap);
    //painter->restore();
    qreal width=pixmap.width();
    qreal height=pixmap.height();
    pixmap=pixmap.scaled(width,height,Qt::KeepAspectRatio);

}

QPoint monster::getCurrentPos(){
    return this->currentPos;
}

void monster::setCurrentPos(QPoint pos){
    this->currentPos=pos;
}

void monster::move(){
    QPropertyAnimation *animation=new QPropertyAnimation(this,"currentPos");
    animation->setDuration(2000);
    animation->setStartValue(startPos);
    animation->setEndValue(endPos);
    animation->start();

}
