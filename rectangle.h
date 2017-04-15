#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <QGraphicsPolygonItem>
#include <QApplication>
#include <QPainter>
#include <QPointF>
#include <QPoint>
#include <QVector>

class Rectangle : public QGraphicsPolygonItem {
    QVector<QPointF> points;
public:
    Triangle(const QPointF &pos, const QPointF &pt1, const QPointF &pt2, const QPointF &pt3);
    QPointF get_head();
    void draw();
    virtual ~Triangle(){}
};

class Rectangle
{
public:
    Rectangle();
};

#endif // RECTANGLE_H
