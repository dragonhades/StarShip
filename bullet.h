#ifndef BULLET_H
#define BULLET_H
#include <QtGlobal>
#include <QLineF>
#include <QObject>
#include <QAbstractGraphicsShapeItem>
#include <QGraphicsPolygonItem>
class QAbstractGraphicsShapeItem;
class QGraphicsView;

class Bullet : public QObject, public QGraphicsSimpleTextItem {
    Q_OBJECT
    QAbstractGraphicsShapeItem *bullet=nullptr;
    QLineF head;
    QGraphicsView *view=0;
    qreal speed=0.7;
public:
    Bullet(QAbstractGraphicsShapeItem *bullet, const QLineF &dir, QGraphicsView *view);
protected:
    void advance(int phase);
};

#endif // BULLET_H
