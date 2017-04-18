#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include "exit.h"
#include <QObject>
#include <QWidget>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>

class Interface : public QWidget, public QGraphicsSimpleTextItem {
    Q_OBJECT
    QGraphicsView *view;
    Exit *exit=0;
public:
    Interface(QGraphicsView *view):view{view}{}
    ~Interface(){}
    void keyPressEvent(QKeyEvent *event);
signals:
    void notify();
public slots:
    void notifiedExit();
};
#endif // MYAPPLICATION_H
