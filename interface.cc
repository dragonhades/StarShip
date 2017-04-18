#include "Interface.h"
#include "exit.h"
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QDebug>

void Interface::keyPressEvent(QKeyEvent *event){
    qDebug() <<42;
    switch(event->key()){
    case Qt::Key_Escape:
        notifiedExit();
        break;
    default:
        break;
    }
}

void Interface::notifiedExit(){
    if(!exit){
        QGraphicsSimpleTextItem::setFlag(QGraphicsItem::ItemIsFocusable);
        QGraphicsSimpleTextItem::setFocus();
        exit = new Exit(view);
        scene()->addWidget(exit);
        //exit->QWidget::setFocus();
    } else {
        delete exit;
        exit=nullptr;
        notify();
    }
}
