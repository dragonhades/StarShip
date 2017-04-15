#include "triangle.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QDebug>
#include <QPoint>
#include <QPointF>
#include <QPainter>
#include <QVector>
#include <QPolygonF>

Triangle::Triangle(const QPointF &pos, const QPointF &pt1, const QPointF &pt2, const QPointF &pt3){
    setPos(pos);
    points.push_back(pt1);
    points.push_back(pt2);
    points.push_back(pt3);
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

