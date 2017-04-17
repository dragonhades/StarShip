#include "exit.h"
#include <QWidget>
#include <QPushButton>
#include <QGraphicsView>
#include <QDebug>

Exit::Exit(QGraphicsView *view):view{view}{
    resize(75,30);
    move(view->frameRect().width()-75,0);
    QPushButton *button = new QPushButton("quit",this);
    button->setGeometry(0, 0, 75, 30);
    connect(button, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void Exit::makeButton(){

}
