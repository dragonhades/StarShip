#include "exit.h"

#include <QKeyEvent>
#include <QApplication>
#include <QDebug>
#include <iostream>

Exit::Exit(QApplication *a):a{a}{}

void Exit::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Escape){
        setPos(x()+10, y());
        a->quit();
    }
}
