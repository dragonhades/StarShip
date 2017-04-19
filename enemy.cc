#include "enemy.h"
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
#include "bullet.h"

Enemy::Enemy(QAbstractGraphicsShapeItem *body, QGraphicsView *view):body{body},view{view}{
    QPointF p1(0,0);
    QPointF p2(1,1);
    head.setP1(p1);
    head.setP2(p2);
    size = body->boundingRect().width()/2;
}

Enemy::~Enemy(){
    //delete(body);
}

void Enemy::setAngle(const qreal x){
    head.setAngle(x);
    current_A = x;
}

void Enemy::move(){
    if(engineState==PAUSE) return;
    body->setPos(body->scenePos().x()-head.dy()/5*current_speed, body->scenePos().y()-head.dx()/5*current_speed);

    if(body->pos().y()+body->boundingRect().height()<0){
        body->setY(view->frameRect().height()+body->boundingRect().height()/2);
    }
    else if(body->pos().y()-body->boundingRect().height()>view->frameRect().height()){
        body->setY(-body->boundingRect().height()/2);
    }
    else if(body->pos().x()+body->boundingRect().width()<0){
        body->setX(view->frameRect().width()+body->boundingRect().width()/2);
    }
    else if(body->pos().x()-body->boundingRect().width()>view->frameRect().width()){
        body->setX(-body->boundingRect().width()/2);
    }
}

void Enemy::fire(){
    fire_rate_acc+=fire_rate;
    if(fire_rate_acc>=1000){
        fire_rate_acc=0;

        QPointF p1(-10,-10);
        QPointF p2(10,10);
        QRectF rect(p1,p2);

        QBrush brush;
        brush.setColor(Qt::black);
        brush.setStyle(Qt::SolidPattern);

        unsigned int bulletNum = 5;
        qreal speed =2;
        qreal angle =0;
        qreal angle_acc = 360/bulletNum;
        for(int i=0; i<bulletNum; i++){
            auto bullet = new QGraphicsEllipseItem(rect);
            bullet->setPos(body->scenePos());
            bullet->setBrush(brush);
            scene()->addItem(bullet);
            bullet->setPos(body->scenePos());
            Bullet *b1 = new Bullet(bullet,head,view);
            b1->setAngle(angle);
            b1->setSpeed(speed);
            scene()->addItem(b1);
            connect(this,SIGNAL(notifyObservers()),b1,SLOT(keyPress()));
            angle+=angle_acc;
        }
    }
}

void Enemy::zoom(){
    static bool up = true;

    if(current_scale<0.1) {
        current_scale=0.1;
        up = true;
    }
    else if(current_scale>1) {
        current_scale = 1;
        up = false;
    }
    if(up) current_scale += scale_acc;
    else current_scale -= scale_dec;
    body->setScale(current_scale);
}

void Enemy::advance(int phase){
    if(!phase) return;
    if(engineState!=PAUSE) {
        move();
        zoom();
    }
    if(weaponState!=PAUSE) fire();

    QPointF p = body->scenePos();
    setPos(p.x()+35, p.y()-35);
    int x = p.x();
    int y = p.y();
    QString qs;
    setText(qs.fromStdString("x: "+std::to_string(x)+"   y: "+std::to_string(y)));
}

void Enemy::notified(){
    if(engineState!=PAUSE) engineState=PAUSE;
    else engineState=STOP;
    if(weaponState!=PAUSE) weaponState=PAUSE;
    else weaponState=STOP;
    notifyObservers();
}
