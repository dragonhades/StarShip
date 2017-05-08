#ifndef TRIANGLESHIP_H
#define TRIANGLESHIP_H
#include <QObject>
#include <QWidget>
#include <QGraphicsPolygonItem>
#include <QPainter>
#include "constants.h"
class Triangle;
class QPointF;
class QGraphicsView;
class QLineF;

class TriangleShip :public QWidget, public QGraphicsSimpleTextItem {
    Q_OBJECT
    QGraphicsItemGroup *tri=nullptr;
    QPointF center;
    QLineF head;
    qreal max_speed=0.6;
    qreal rotate_speed=0.7;
    int fire_rate=1;
    int fire_rate_acc=100;
    qreal current_speed=0;
    qreal current_A=0;
    qreal accelaration=0.0012;
    qreal decelaration=0.0010;
    STATE engineState=STATE::STOP;
    STATE weaponState=STATE::STOP;
    QGraphicsView *view=nullptr;
    void move();
    bool canFire();
public:
    TriangleShip(QGraphicsView *view);
    void addComponents(Triangle *triangle);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void increaseSpeed(const qreal &speed);
    void decreaseSpeed(const qreal &speed);
    void setMaxSpeed(const qreal &s);
    void fire();
signals:
    void keyPress();
    void notifyObservers();
public slots:
    void notified();
    void mousePressNotified();
    void mouseReleaseNotified();
protected:
    void advance(int phase);
};

#endif // TRIANGLESHIP_H
