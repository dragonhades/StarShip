#ifndef TRIANGLESHIP_H
#define TRIANGLESHIP_H
#include <QObject>
#include <QWidget>
#include <QGraphicsPolygonItem>
#include <QPainter>
class Triangle;
class QPointF;
class QGraphicsView;
class QLineF;

class TriangleShip :public QObject, public QGraphicsSimpleTextItem {
    Q_OBJECT
    QGraphicsItemGroup *tri=nullptr;
    QPointF center;
    QLineF head;
    qreal max_speed=0.5;
    qreal rotate_speed=0.5;
    int fire_rate=5;
    qreal current_speed=0;
    qreal current_A=0;
    enum STATE { STOP, SPEEDUP, SLOWDOWN };
    STATE engineState=STATE::STOP;
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
    void moveView();
    void fire();
protected:
    void advance(int phase);
};

#endif // TRIANGLESHIP_H
