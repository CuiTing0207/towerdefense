#ifndef MONSTER1_H
#define MONSTER1_H

#include <QObject>
#include <QPoint>
#include <QPixmap>

class monster1 : public QObject
{
    Q_OBJECT
public:
    monster1(QPoint startpos,QPoint endpos,QString addr);
    void move();
    void paint(QPainter *painter);
private:
    QPoint startPos;
    QPoint endPos;
    QPoint currentPos;
    QPixmap pixmap;
    qreal speed;

signals:

public slots:
};

#endif // MONSTER1_H
