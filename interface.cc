#include "Interface.h"
#include "exit.h"
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QDebug>

Interface::Interface(QGraphicsView *view):view{view}{
    QGraphicsSimpleTextItem::setFlag(QGraphicsItem::ItemIsFocusable);
}

void Interface::keyPressEvent(QKeyEvent *event){
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

void Interface::advance(int phase){
    if(!phase) return;
}
