#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QDesktopWidget>
#include <QPoint>
#include <QDebug>
#include <QTimer>
#include "exit.h"
#include "cursor.h"
#include "triangle.h"
#include "triangleship.h"
#include "constants.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    int desktopHeight=a.desktop()->screenGeometry().height();
    int desktopWidth=a.desktop()->screenGeometry().width();
    QGraphicsScene * scene = new QGraphicsScene();
    QGraphicsView * view = new QGraphicsView(scene);

    // create an item to put into the scene
    Exit * exit_button = new Exit(&a);
    exit_button->setRect(1180, 0 ,100,100);

    QTimer * timer = new QTimer;
    QObject::connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    timer->start(timer_start);

    Cursor * cursor = new Cursor(view);
    QPointF p(0, 0);
    QPointF p1(p.x()+0, p.y()-20);
    QPointF p2(p.x()-10, p.y()+20);
    QPointF p3(p.x()+10, p.y()+20);
    Triangle * triangle = new Triangle(p, p1, p2, p3);
    TriangleShip * ship = new TriangleShip(triangle,view);
    // add the item to the scene
    scene->addItem(triangle);
    scene->addItem(ship);
    scene->addItem(exit_button);    // add the item to the scene
    //scene->addItem(&item);
    scene->addItem(cursor);
    // make rect focusable
    ship->setFlag(QGraphicsItem::ItemIsFocusable);
    triangle->setFlag(QGraphicsItem::ItemIsFocusable);
    //triangle->setFocus();
    exit_button->setFlag(QGraphicsItem::ItemIsFocusable);
    ship->setFocus();
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //view->showFullScreen();
    view->show();
    view->setFixedSize(1280,720);
    scene->setSceneRect(0,0,desktopWidth,desktopHeight);

    return a.exec();
}
