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
    QVector<QPointF> points;
    points.push_back(QPointF(p.x()+0, p.y()-20));
    points.push_back(QPointF(p.x()-10, p.y()+15));
    points.push_back(QPointF(p.x()+10, p.y()+15));
    Triangle * triangle = new Triangle(p, points);
    points.clear();
    points.push_back(QPointF(p.x()-10, p.y()+90));
    points.push_back(QPointF(p.x()-10, p.y()+15));
    points.push_back(QPointF(p.x()+10, p.y()+15));
    points.push_back(QPointF(p.x()+10, p.y()+90));
    Triangle * rect = new Triangle(p, points);
    points.clear();
    points.push_back(QPointF(p.x()-10, p.y()+35));
    points.push_back(QPointF(p.x()-10, p.y()+75));
    points.push_back(QPointF(p.x()-50, p.y()+75));
    Triangle * leftTri = new Triangle(p, points);
    points.clear();
    points.push_back(QPointF(p.x()+10, p.y()+35));
    points.push_back(QPointF(p.x()+10, p.y()+75));
    points.push_back(QPointF(p.x()+50, p.y()+75));
    Triangle * rightTri = new Triangle(p, points);
    TriangleShip * ship = new TriangleShip(view);
    //cene->addItem(triangle);
    //scene->addItem(rect);
    scene->addItem(ship);
    ship->addComponents(triangle);
    ship->addComponents(rect);
    ship->addComponents(leftTri);
    ship->addComponents(rightTri);
    // add the item to the scene
    scene->addItem(exit_button);    // add the item to the scene
    scene->addItem(cursor);
    // make rect focusable
    ship->setFlag(QGraphicsItem::ItemIsFocusable);
    triangle->setFlag(QGraphicsItem::ItemIsFocusable);
    triangle->setFocus();
    //exit_button->setFlag(QGraphicsItem::ItemIsFocusable);
    ship->setFocus();
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //view->showFullScreen();

    view->show();
    view->setFixedSize(1280,720);
    scene->setSceneRect(0,0,desktopWidth+5000,desktopHeight+5000);

    return a.exec();
}
