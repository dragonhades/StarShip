#include "myview.h"
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
#include "triangleship.h"

MyView::MyView(){}

void MyView::connect_ship(TriangleShip *ship){
    QObject::connect(this,SIGNAL(mousePressNotify()),ship,SLOT(mousePressNotified()));
    QObject::connect(this,SIGNAL(mouseReleaseNotify()),ship,SLOT(mouseReleaseNotified()));
}

void MyView::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        mousePressNotify();
    }
}

void MyView::mouseReleaseEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        mouseReleaseNotify();
    }
}

/*
void MyView::showFullScreen(){
    view.showFullScreen();
}

void MyView::setFixedSize(int desktopWidth, int desktopHeight){
    view.setFixedSize(desktopWidth,desktopHeight);
}

QRectF MyView::frameRect(){
    return view.frameRect();
}
*/
