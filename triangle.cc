#include "triangle.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QApplication>
#include <QDebug>
#include <QPoint>
#include <QPointF>
#include <QPainter>
#include <QVector>
#include <QPolygonF>

Triangle::Triangle(const QPointF &pos, const QVector<QPointF> &arr){
    setPos(pos);
    points = arr;
    draw();
}

QPointF Triangle::get_head(){
    return polygon()[0];
}

void Triangle::draw(){
    QPolygonF poly(points);
    QPen pen;
    pen.setWidth(3);
    setPen(pen);
    setPolygon(poly);
}

