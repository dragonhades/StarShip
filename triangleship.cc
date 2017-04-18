#include "triangleship.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QDebug>
#include <QTimer>
#include <QTransform>
#include <QPointF>
#include <QLineF>
#include <QWidget>
#include <QtMath>
#include "constants.h"
#include "triangle.h"
#include "tools.h"
#include "exit.h"
#include "cursor.h"
#include "bullet.h"

TriangleShip::TriangleShip(QGraphicsView *view):view{view}{
}

void TriangleShip::addComponents(Triangle *triangle){
    if(!tri) {
        tri = new QGraphicsItemGroup();
        head = QLineF(triangle->scenePos(), triangle->get_head());
        scene()->addItem(tri);
    }
    tri->addToGroup(triangle);
    QRectF matrix = tri->boundingRect();
    center = matrix.center();
    scene()->addRect(matrix);
}

void TriangleShip::move(){
    if(engineState==PAUSE) return;

    QPointF cursor = view->mapFromGlobal(view->cursor().pos());
    qreal AGLcenterCursor = angle_x_to_y(tri->scenePos(), cursor);
    current_A = tri->rotation();
    if(abs(current_A-AGLcenterCursor)<rotate_speed){
    }
    else if((current_A>=0&&AGLcenterCursor>=0) || (current_A<0&&AGLcenterCursor<0)){
        if(current_A>AGLcenterCursor){
            current_A-=rotate_speed;
        }
        if(current_A<AGLcenterCursor){
            current_A+=rotate_speed;
        }
    } else {
        if(360-abs(current_A)-abs(AGLcenterCursor)<180){
            if(current_A>=0&&AGLcenterCursor<0){
                if(current_A>=180) current_A = -180+rotate_speed;
                else current_A+=rotate_speed;
            } else {
                if(current_A<=-180) current_A = 180-rotate_speed;
                else current_A-=rotate_speed;
            }
        } else {
            if(current_A>=0&&AGLcenterCursor<0){
                current_A-=rotate_speed;
            } else {
                current_A+=rotate_speed;
            }
        }
    }
    QPointF offset = tri->sceneBoundingRect().center();
    QTransform transform;
    transform.translate(offset.x(),offset.y());
    transform.rotate(current_A);
    transform.translate(-offset.x(),-offset.y());
    tri->setTransformOriginPoint(tri->boundingRect().center());
    tri->setRotation(qRadiansToDegrees(qAtan2(transform.m12(), transform.m11())));
    head.setAngle(current_A);
    if((offset.x()>=cursor.x()-170 && offset.y()>=cursor.y()-170) &&
       (offset.x()<=cursor.x()+170 && offset.y()<=cursor.y()+170)) {
        decreaseSpeed(decelaration*2);
    } else {
        increaseSpeed(accelaration);
    }
    tri->setPos(tri->pos().x()-head.dy()/5*current_speed, tri->pos().y()-head.dx()/5*current_speed);
}

void TriangleShip::fire(){
    fire_rate_acc+=fire_rate;
    if(fire_rate_acc>=100){
        fire_rate_acc=0;
        QPointF p1(-2,-40);
        QPointF p2(2,40);
        QRectF rect(p1,p2);
        auto bullet = new QGraphicsEllipseItem(rect);
        bullet->setPos(tri->scenePos());
        bullet->setPos(bullet->scenePos().x()-head.dy()*2.5, bullet->scenePos().y()-head.dx()*2.5);
        QPen pen;
        pen.setWidth(2);
        bullet->setPen(pen);
        QBrush brush;
        brush.setColor(Qt::black);
        brush.setStyle(Qt::SolidPattern);
        bullet->setBrush(brush);
        scene()->addItem(bullet);
        Bullet *b = new Bullet(bullet,head,view);
        scene()->addItem(b);
        connect(this,SIGNAL(notifyBullet()),b,SLOT(keyPress()));
    }
}


void TriangleShip::increaseSpeed(const qreal &speed){
    if(current_speed<max_speed) current_speed += speed;
}

void TriangleShip::decreaseSpeed(const qreal &speed){
    if(current_speed<speed) current_speed = 0;
    else current_speed -= speed;
}

void TriangleShip::setMaxSpeed(const qreal &s){
    max_speed = s;
}
/*
bool TriangleShip::event(QEvent *e){
    if(e->type()==QEvent::KeyPress){
        if(e->type()==Qt::Key_W){
            engineState = SPEEDUP;
        }
        else if(e->type()==Qt::Key_S){
            engineState = SLOWDOWN;
        }
        if(e->type()==Qt::Key_Space){
            weaponState = FIRE;
        }
    }
    if(e->type()==QEvent::KeyRelease){
        if(e->type()==Qt::Key_W){
            engineState = STOP;
        }
        else if(e->type()==Qt::Key_S){
            engineState = STOP;
        }
        else if(e->type()==Qt::Key_Space){
            weaponState = STOP;
        }
    }
}
*/

void TriangleShip::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        weaponState = FIRE;
    }
}

void TriangleShip::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        weaponState = STOP;
    }
}


void TriangleShip::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_W:
        engineState = SPEEDUP;
        break;
    case Qt::Key_S:
        engineState = SLOWDOWN;
        break;
    case Qt::Key_Space:
        if(weaponState!=PAUSE) weaponState = FIRE;
        break;
    case Qt::Key_Escape:
        if(engineState==PAUSE) {
            engineState = STOP;
            weaponState = STOP;
        }
        else {
            engineState = PAUSE;
            weaponState = PAUSE;
            notifyBullet();
            keyPress();
        }
        break;
    default:
        break;
    }
}

void TriangleShip::keyReleaseEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_W:
        engineState = STOP;
        break;
    case Qt::Key_S:
        engineState = STOP;
        break;
    case Qt::Key_Space:
        if(weaponState!=PAUSE) weaponState = STOP;
        break;
    default:
        break;
    }
}

void TriangleShip::notified(){
    engineState = STOP;
    weaponState = STOP;
    notifyBullet();
}

void TriangleShip::advance(int phase){
    if(!phase) return;
    if(engineState!=PAUSE) QGraphicsSimpleTextItem::setFocus();
    switch (engineState) {
    case SPEEDUP :
        increaseSpeed(accelaration);
        break;
    case SLOWDOWN :
        decreaseSpeed(decelaration);
        break;
    default:
        break;
    }
    switch (weaponState) {
    case FIRE:
        fire();
        break;
    default:
        break;
    }
    move();
    QPointF p = tri->pos();
    setPos(p.x()+15, p.y()-15);
    int x = p.x();
    int y = p.y();
    QString qs;
    setText(qs.fromStdString("x: "+std::to_string(x)+"   y: "+std::to_string(y)));
}
