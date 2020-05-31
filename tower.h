#ifndef TOWER_H
#define TOWER_H
#include<QPoint>
#include <QPixmap>
#include <QObject>

class Tower : public QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos,QString addr);
    void paint(QPainter *painter);
private:
    QPoint _pos;
    QPixmap pixmap;

signals:

public slots:
};

#endif // TOWER_H
