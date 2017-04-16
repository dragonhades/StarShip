#ifndef BULLET_H
#define BULLET_H
#include <QtGlobal>
#include <QLineF>
#include <QObject>
#include <QAbstractGraphicsShapeItem>
#include <QGraphicsPolygonItem>
class QAbstractGraphicsShapeItem;

class Bullet : public QObject, public QGraphicsPolygonItem {
    Q_OBJECT
    QAbstractGraphicsShapeItem *bullet=nullptr;
    QLineF head;
    qreal speed=0.3;
public:
    Bullet(QAbstractGraphicsShapeItem *bullet, const QLineF &dir);
protected:
    void advance(int phase);
};

#endif // BULLET_H
