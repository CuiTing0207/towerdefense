#ifndef TOWER_H
#define TOWER_H
#include<QPoint>
#include <QPixmap>
#include <QObject>

class QPainter;
class monster1;
class window2;
class QTimer;

class Tower : public QObject
{
    Q_OBJECT
public:
    Tower(window2 *game1,QPoint pos,QString addr);
    ~Tower();
    void paint(QPainter *painter);
    void findMonsterInRange();
    void chooseMonsterForAttack(monster1 *monster);
    void lostMonster();
    void targetKilled();
    void attackMonster();
    void setRate(int r);//改变攻击速度
    void setRange(int r);//改变攻击范围
    //monster1* chosenmonster();
    int damage;//造成伤害
private:
    QPoint _pos;
    QPixmap pixmap;
    int range;//攻击范围
    int rate;//攻击速度

    monster1 * chooseMonster;
    QTimer * rateTimer;
    window2 *game;

signals:

public slots:
    void shoot();
};

#endif // TOWER_H
