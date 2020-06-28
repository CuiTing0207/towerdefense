#include "bullet.h"
#include "monster1.h"
#include "window2.h"
#include <QPainter>
#include <QPropertyAnimation>

const QSize Bullet::ms_fixedSize(8, 8);

Bullet::Bullet(QPoint startPos, QPoint targetPoint, int damage, monster1 *target,
               window2 *game, const QPixmap &sprite/* = QPixmap(":/bullet.png")*/)
    : _startPos(startPos)
    , _targetPos(targetPoint)
    , _sprite(sprite)
    , _currentPos(startPos)
    , _target(target)
    , _game(game)
    , _damage(damage)
{
}

void Bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(_currentPos, _sprite);
}

void Bullet::move()
{
    // 100毫秒内击中敌人
    static const int duration = 100;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(_startPos);
    animation->setEndValue(_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));

    animation->start();
}

void Bullet::hitTarget()
{

    // 因此先判断下敌人是否还有效
    //if (m_game->monster1_n().indexOf(m_target) != -1)
    //	m_target->getDamage(m_damage);
    _game->removedBullet(this);
}

void Bullet::setCurrentPos(QPoint pos)
{
    _currentPos = pos;
}

QPoint Bullet::currentPos() const
{
    return _currentPos;
}
