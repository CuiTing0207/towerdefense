#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class QPainter;
class window2;
class monster1;

class Bullet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint _currentPos READ currentPos WRITE setCurrentPos)
public:
    Bullet(QPoint startPos, QPoint targetPoint, int damage, monster1 *target,
           window2 *game, const QPixmap &sprite = QPixmap (":/bullet.png"));

    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint currentPos() const;

private slots:
    void hitTarget();

private:
    const QPoint	_startPos;
    const QPoint	_targetPos;
    const QPixmap	_sprite;
    QPoint			_currentPos;
    monster1 *			_target;
    window2 *	_game;
    int				_damage;

    static const QSize ms_fixedSize;
};

#endif // BULLET_H
