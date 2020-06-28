#ifndef MONSTER1_H
#define MONSTER1_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QList>

class window2;
class Tower;

class monster1 : public QObject
{
    Q_OBJECT
public:
    monster1(window2 *game1,QPoint startpos,QPoint endpos,QString addr);
    ~monster1();
    void move();
    void paint(QPainter *painter);
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);
    void getDamage(int damage);
    void getRemoved();
    void setSpeed(qreal s);
    QPoint startPos;
    QPoint endPos;
    QPoint currentPos;
private:
    int currentHp;
    QPixmap pixmap;
    qreal speed;
    QList<Tower *>	attackedTowersList;
    window2 *game;


signals:

public slots:
};

#endif // MONSTER1_H
