#ifndef TRIANGLESHIP_H
#define TRIANGLESHIP_H
#include <QObject>
#include <QGraphicsPolygonItem>
class Triangle;
class QPointF;
class QGraphicsView;
class QLineF;

class TriangleShip : public QObject, public QGraphicsPolygonItem {
    Q_OBJECT
    Triangle *tri=nullptr;
    QPointF center;
    QLineF head;
    qreal max_speed=0.5;
    qreal rotate_speed=1;
    qreal current_speed=0;
    enum STATE { STOP, SPEEDUP, SLOWDOWN };
    STATE engineState=STATE::STOP;
    QGraphicsView *view=nullptr;
    void move();
public:
    TriangleShip(Triangle *triangle, QGraphicsView *view);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void increaseSpeed(const qreal &speed);
    void decreaseSpeed(const qreal &speed);
    void setMaxSpeed(const qreal &s);
    void moveView();
protected:
    void advance(int phase);
};

#endif // TRIANGLESHIP_H
