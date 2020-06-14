#include "monster1.h"
#include <QPoint>
#include <QVector2D>
#include <QPainter>
monster1::monster1(QPoint startpos,QPoint endpos,QString addr):QObject (0),pixmap(addr)
{
    this->currentPos=startpos;
    this->startPos=startpos;
    this->endPos=endpos;
    speed=5.0;
}

void monster1::move(){
    QVector2D vector(endPos-startPos);//ȷ������
    vector.normalize();
    currentPos=currentPos+vector.toPoint()*speed;
    if(currentPos==endPos)
        this->speed=0;
    //���������������յ�ͣ�����������������
}

void monster1::paint(QPainter *painter){
    //painter->drawPixmap(currentPos,pixmap);
    painter->drawPixmap(currentPos.rx(),currentPos.ry(),100,100,pixmap);
    //painter->restore();
    qreal width=pixmap.width();
    qreal height=pixmap.height();
    pixmap=pixmap.scaled(width,height,Qt::KeepAspectRatio);
}
