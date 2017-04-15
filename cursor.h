#ifndef CURSOR_H
#define CURSOR_H
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QApplication>
#include <QMouseEvent>
#include <QObject>
class QGraphicsView;

class Cursor : public QObject, public QGraphicsSimpleTextItem {
    Q_OBJECT
    QGraphicsView *view;
public:
    Cursor(QGraphicsView *view);
    void mouseMoveEvent(QMouseEvent *cursor);
    virtual ~Cursor(){}
public slots:
    void move();
};

#endif // CURSOR_H
