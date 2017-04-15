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
#include "constants.h"
#include "triangle.h"
#include "tools.h"
#include "cursor.h"

TriangleShip::TriangleShip(Triangle *triangle, QGraphicsView *view):view{view}{
    tri = triangle;
    center = triangle->scenePos();
    head = QLineF(center, triangle->get_head());
}

void TriangleShip::move(){
    tri->setPos(tri->scenePos());
    qreal AGLcenterCursor = angle_x_to_y(tri->scenePos(), view->mapFromGlobal(view->cursor().pos()));
    tri->setPos(tri->scenePos().x()-(head.dy()/5*current_speed), tri->scenePos().y()-(head.dx()/5*current_speed));
    qreal current_A = tri->rotation();
    if((current_A>=0&&AGLcenterCursor>=0) || (current_A<0&&AGLcenterCursor<0)){
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
    tri->setRotation(current_A);
    head.setAngle(current_A);
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
    scene()->translate(scenePos().x(),scenePos().y());
}