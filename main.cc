#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QDesktopWidget>
#include <QWidget>
#include <QObject>
#include <QPoint>
#include <QDebug>
#include <QTimer>
#include <QPushButton>
#include "exit.h"
#include "cursor.h"
#include "triangle.h"
#include "triangleship.h"
#include "constants.h"
#include "Interface.h"

int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    int desktopHeight=a.desktop()->screenGeometry().height();
    int desktopWidth=a.desktop()->screenGeometry().width();
    QGraphicsScene * scene = new QGraphicsScene();
    QGraphicsView * view = new QGraphicsView(scene);
    view->showFullScreen();
    scene->setSceneRect(0,0,desktopWidth,desktopHeight);
    view->setFixedSize(desktopWidth,desktopHeight);

    QTimer * timer = new QTimer;
    QObject::connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    timer->start(timer_start);

    Cursor * cursor = new Cursor(view);
    scene->addItem(cursor);

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

    scene->addItem(ship);
    ship->addComponents(triangle);
    ship->addComponents(rect);
    ship->addComponents(leftTri);
    ship->addComponents(rightTri);
    ship->QGraphicsSimpleTextItem::setFlag(QGraphicsItem::ItemIsFocusable);
    ship->QGraphicsSimpleTextItem::setFocus();

    Interface *interface = new Interface(view);
    scene->addItem(interface);
    QObject::connect(ship,SIGNAL(keyPress()),interface,SLOT(notifiedExit()));
    QObject::connect(interface,SIGNAL(notify()),ship,SLOT(notified()));

    //Exit * exit = new Exit(view);
    //scene->addWidget(exit);

    /*
    auto frame = new QGraphicsRectItem(view->frameRect());
    scene->addItem(frame);
    //view->translate(50,50);
    auto frame2 = new QGraphicsRectItem(view->frameRect());
    scene->addItem(frame2);
    */

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    return a.exec();
}
