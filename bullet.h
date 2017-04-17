#ifndef BULLET_H
#define BULLET_H
#include <QtGlobal>
#include <QLineF>
#include <QObject>
#include <QAbstractGraphicsShapeItem>
#include <QGraphicsPolygonItem>
#include "constants.h"
class QAbstractGraphicsShapeItem;
class QGraphicsView;

class Bullet : public QObject, public QGraphicsSimpleTextItem {
    Q_OBJECT
    QAbstractGraphicsShapeItem *bullet=nullptr;
    QLineF head;
    QGraphicsView *view=0;
    qreal speed=0.7;
    void move();
    STATE state;
public:
    Bullet(QAbstractGraphicsShapeItem *bullet, const QLineF &dir, QGraphicsView *view);
public slots:
    void keyPress();
protected:
    void advance(int phase);
};

#endif // BULLET_H
