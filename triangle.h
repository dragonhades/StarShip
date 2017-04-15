#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <QGraphicsPolygonItem>
#include <QApplication>
#include <QPainter>
#include <QPointF>
#include <QPoint>
#include <QVector>

class Triangle : public QGraphicsPolygonItem {
    QVector<QPointF> points;
public:
    Triangle(const QPointF &pos, const QPointF &pt1, const QPointF &pt2, const QPointF &pt3);
    QPointF get_head();
    void draw();
    virtual ~Triangle(){}
};

#endif // TRIANGLE_H
