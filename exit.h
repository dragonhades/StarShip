#ifndef EXIT_H
#define EXIT_H

#include <QWidget>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>

class Exit : public QWidget, public QGraphicsSimpleTextItem {
    QGraphicsView *view=0;
public:
    Exit(QGraphicsView *view);
};

#endif // EXIT_H
