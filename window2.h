#ifndef WINDOW2_H
#define WINDOW2_H

#include <QMainWindow>
#include"tower.h"
#include"monster.h"
#include "monster1.h"
#include <QList>
#include <QTimer>

class window2 : public QMainWindow
{
    Q_OBJECT
public:
    explicit window2(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void new_tower();
    void new_monster();
    void updatewindow();
    void textshow(QPainter *painter);

signals:
    void back();
private:
    QList<Tower*> tower_n;
    QList<monster *> monster_n;
    QList<monster1 *> monster1_n;
    int num1=10;
    int num2=20;

public slots:
    //void selfmove();
    //void dogo();
};

#endif // WINDOW2_H
