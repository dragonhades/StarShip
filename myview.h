#ifndef MYVIEW_H
#define MYVIEW_H
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
class TriangleShip;

class MyView : public QGraphicsView {
    Q_OBJECT
public:
    MyView();
    void connect_ship(TriangleShip *ship);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void mousePressNotify();
    void mouseReleaseNotify();
};

#endif // MYVIEW_H
