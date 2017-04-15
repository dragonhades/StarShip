#include <QKeyEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>
#include <QPointF>
#include <QDebug>
#include <QString>
#include <QTimer>
#include "cursor.h"
#include "constants.h"

Cursor::Cursor(QGraphicsView *view):view{view}{
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(timer_start);
}

void Cursor::move(){
    QPointF p = view->mapFromGlobal(view->cursor().pos());
    setPos(p.x()+15, p.y()-15);
    int x = p.x();
    int y = p.y();
    QString qs;
    setText(qs.fromStdString("x: "+std::to_string(x)+"   y: "+std::to_string(y)));
}
