#ifndef WINDOW2_H
#define WINDOW2_H

#include <QMainWindow>
#include"tower.h"


#include <QList>
#include <QTimer>
class monster1;
class Bullet;
class window2 : public QMainWindow
{
    Q_OBJECT
public:
    explicit window2(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void new_tower();
    void new_tower2();
    void new_tower3();
    void new_monster();
    void updatewindow();
    void textshow(QPainter *painter);
    void removedMonster(monster1 *mt);
    void removedBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
    void getHpDamage(int damage = 1);
    void awardCoin(int coin1);
    QList<monster1 *> monster1_n;
    QList<Bullet *> bullet_n;
signals:
    void back();

private:
    QList<Tower*> tower_n;

    bool gamewin;
    bool gamelose;
    int coin;
    int waves;
    int total_waves;
    int playerHp;
    QTimer *timerm;



public slots:
  void stopMonster();
};

#endif // WINDOW2_H
