#ifndef MONSTER_H
#define MONSTER_H
#include <Qpixmap>
#include <QPoint>
#include <QObject>
#include <QPropertyAnimation>
#include <QMovie>

class monster : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint currentPos READ getCurrentPos WRITE setCurrentPos)
public:
   monster(QPoint startpos,QPoint endpos,QString addr);
   void paint(QPainter *painter);
   void move();
   QPoint getCurrentPos();
   void setCurrentPos(QPoint pos);
private:
   QPoint startPos;
   QPoint endPos;
   QPoint currentPos;
   QPixmap pixmap;
   int speed;


signals:

public slots:
};

#endif // MONSTER_H
