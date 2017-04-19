#ifndef ENEMY_H
#define ENEMY_H
#include <QtGlobal>
#include <QLineF>
#include <QObject>
#include "constants.h"
#include <QGraphicsSimpleTextItem>
class QGraphicsSimpleTextItem;
class QGraphicsView;

class Enemy : public QObject, public QGraphicsSimpleTextItem {
    Q_OBJECT
    QAbstractGraphicsShapeItem *body=nullptr;
    qreal size;
    QLineF head;
    qreal max_speed=0.6;
    qreal rotate_speed=0.5;
    int fire_rate=1;
    int fire_rate_acc=1000;
    qreal current_speed=1;
    qreal current_A=0;
    qreal accelaration=0.00012;
    qreal decelaration=0.00009;
    STATE engineState=STATE::STOP;
    STATE weaponState=STATE::STOP;
    qreal scale_acc = 0.012;
    qreal scale_dec = 0.009;
    qreal current_scale = 1;
    QGraphicsView *view=nullptr;
    void move();
    void fire();
    void zoom();
    void increaseSpeed(const qreal &speed);
    void decreaseSpeed(const qreal &speed);
public:
    Enemy(QAbstractGraphicsShapeItem *body, QGraphicsView *view);
    void setAngle(const qreal x);
    ~Enemy();
signals:
    void notifyObservers();
public slots:
    void notified();
protected:
    void advance(int phase);
};


#endif // ENEMY_H
