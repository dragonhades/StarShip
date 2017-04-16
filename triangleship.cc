#include "triangleship.h"
#include <QKeyEvent>
#include <QMouseEvent>
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
#include "constants.h"
#include "triangle.h"
#include "tools.h"
#include "cursor.h"

TriangleShip::TriangleShip(QGraphicsView *view):view{view}{
}

void TriangleShip::addComponents(Triangle *triangle){
    if(!tri) {
        tri = new QGraphicsItemGroup();
        head = QLineF(triangle->scenePos(), triangle->get_head());
        scene()->addItem(tri);
    }

    //scene()->addItem(triangle);
    //if(!group) group = new QGraphicsItemGroup();
    tri->addToGroup(triangle);
    scene()->addItem(triangle);
    QRectF matrix = tri->boundingRect();
    center = matrix.center();
    //head = QLineF(tri->scenePos(), head.p2());
    scene()->addRect(matrix);
    //group->addToGroup(matrix);
}

void TriangleShip::move(){
    //qDebug() <<center.x() <<" "<<center.y();
    //center = tri->boundingRect().center();
    qreal AGLcenterCursor = angle_x_to_y(tri->scenePos(), view->mapFromGlobal(view->cursor().pos()));
    QPointF newpt= QPointF(tri->scenePos().x()-(head.dy()/5*current_speed), tri->scenePos().y()-(head.dx()/5*current_speed));
    qreal current_A = tri->rotation();
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
    //qDebug() << AGLcenterCursor;
    QPointF offset = tri->sceneBoundingRect().center();
    QTransform transform;
    transform.translate(offset.x(),offset.y());
    transform.rotate(current_A);
    //qDebug() << head.dy()<<head.dx()<<current_speed;
    transform.translate(-offset.x(),-offset.y());
    tri->setTransformOriginPoint(tri->boundingRect().center());
    tri->setRotation(qRadiansToDegrees(qAtan2(transform.m12(), transform.m11())));
    //transform.reset();
    //transform.translate(offset.x()+head.dy()/5*current_speed,offset.y()+head.dx()/5*current_speed);
    //tri->setTransform(transform);
    head.setAngle(current_A);
    tri->setPos(tri->pos().x()-head.dy()/5*current_speed, tri->pos().y()-head.dx()/5*current_speed);
    //tri->setPos(transform.m31(),transform.m32());
    //tri->setPos(center);
}

void TriangleShip::moveView(){

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

void TriangleShip::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_W){
        engineState = STATE::SPEEDUP;
    }
    else if(event->key()==Qt::Key_S){
        engineState = STATE::SLOWDOWN;
    }
}

void TriangleShip::keyReleaseEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_W){
        engineState = STATE::STOP;
    }
    else if(event->key()==Qt::Key_S){
        engineState = STATE::STOP;
    }
}

void TriangleShip::advance(int phase){
    if(!phase) return;
    switch (engineState) {
    case STATE::SPEEDUP :
        increaseSpeed(0.0012);
        break;
    case STATE::SLOWDOWN :
        decreaseSpeed(0.0008);
        break;
    default:
        break;
    }
    move();
}
