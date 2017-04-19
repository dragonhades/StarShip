#include "exit.h"
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QGraphicsView>
#include <QDebug>

Exit::Exit(QGraphicsView *view):view{view}{
    resize(200,70);
    QPen pen;
    pen.setWidth(3);
    QPushButton *button = new QPushButton("quit",this);
    button->setGeometry(0, 0, 200, 70);
    move(view->frameRect().width()/2-100,view->frameRect().height()/2-35);
    connect(button, SIGNAL(clicked()), qApp, SLOT(quit()));
}
