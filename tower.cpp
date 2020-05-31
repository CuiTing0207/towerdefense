#include "tower.h"
#include <QPixmap>
#include <QPoint>
#include <QPainter>
Tower::Tower(QPoint pos,QString addr):QObject (0),pixmap(addr)
{
    _pos=pos;

}

void Tower::paint(QPainter *painter){
    //painter->drawPixmap(_pos,pixmap);
    QSize pixSize(100,100);
    QPixmap scaledPixmap =pixmap.scaled(pixSize,Qt::KeepAspectRatio);
    painter->drawPixmap(_pos,scaledPixmap);
    /*painter->drawPixmap(_pos.rx(),_pos.ry(),100,100,pixmap);
    qreal width=pixmap.width();
    qreal height=pixmap.height();
    pixmap=pixmap.scaled(width/2,height/2,Qt::KeepAspectRatio);*/
}
