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
    Triangle(const QPointF &pos, const QVector<QPointF> &points);
    QPointF get_head();
    void draw();
    virtual ~Triangle(){}
};

#endif // TRIANGLE_H
