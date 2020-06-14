#ifndef WINDOW3_H
#define WINDOW3_H

#include <QMainWindow>
#include "tower.h"
#include <QList>

class window3 : public QMainWindow
{
    Q_OBJECT
public:
    explicit window3(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
   void new_tower();
   void textshow(QPainter *painter);
signals:
   void back();
private:
   QList<Tower*> tower_n;
public slots:
};

#endif // WINDOW3_H
