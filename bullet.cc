#include "bullet.h"
#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QTransform>
#include <QPointF>
#include <QLineF>
#include <QWidget>
#include <QtMath>
#include "tools.h"
#include "constants.h"

Bullet::Bullet(QAbstractGraphicsShapeItem *bullet, const QLineF &dir, QGraphicsView *view):
    bullet{bullet},head{dir},view{view}{
    bullet->setRotation(head.angle());
}

void Bullet::setAngle(const qreal angle){
    head.setAngle(angle);
}

void Bullet::setSpeed(const qreal speed){
    this->speed = speed;
}

void Bullet::move(){
    bullet->setPos(bullet->scenePos().x()-head.dy()/5*speed, bullet->scenePos().y()-head.dx()/5*speed);
}

void Bullet::advance(int phase){
    if(!phase) return;

    if(state == PAUSE) return;
    else move();
#ifdef DEBUG
    QPointF p = bullet->scenePos();
    setPos(p.x()+15, p.y()-15);
    int x = p.x();
    int y = p.y();
    QString qs;
    setText(qs.fromStdString("x: "+std::to_string(x)+"   y: "+std::to_string(y)));
#endif
    if(bullet->pos().y()+bullet->boundingRect().height()<0||
       bullet->pos().y()-bullet->boundingRect().height()>view->frameRect().height()||
       bullet->pos().x()+bullet->boundingRect().width()<0||
       bullet->pos().x()-bullet->boundingRect().width()>view->frameRect().width()){
        scene()->removeItem(bullet);
        scene()->removeItem(this);
        delete this;
    }
}

void Bullet::keyPress(){
    if(state==STATE::PAUSE) state = STATE::STOP;
    else state = STATE::PAUSE;
}
