#include "bullet.h"
#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <QTransform>
#include <QPointF>
#include <QLineF>
#include <QWidget>
#include <QtMath>

Bullet::Bullet(QAbstractGraphicsShapeItem *bullet, const QLineF &dir):bullet{bullet},head{dir}{
    //bullet->setTransformOriginPoint(bullet->sceneBoundingRect().center());
    //bullet->setRotation(head.angle());
    //bullet->setPos(bullet->sceneBoundingRect().center());
}

void Bullet::advance(int phase){
    if(!phase) return;
    /*
    QPointF offset = bullet->sceneBoundingRect().center();
    QTransform transform;
    transform.translate(offset.x(),offset.y());
    transform.rotate(head.angle());
    transform.translate(-offset.x(),-offset.y());
    bullet->setTransformOriginPoint(bullet->boundingRect().center());
    bullet->setRotation(qRadiansToDegrees(qAtan2(transform.m12(), transform.m11())));
    bullet->setTransformOriginPoint(bullet->boundingRect().center());
    bullet->setRotation(head.angle());
*/
bullet->setPos(bullet->scenePos().x()-head.dy()/5*speed, bullet->scenePos().y()-head.dx()/5*speed);
}
