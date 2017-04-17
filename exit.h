#ifndef EXIT_H
#define EXIT_H

#include <QWidget>
#include <QApplication>
#include <QGraphicsView>

class Exit : public QWidget {
    QGraphicsView *view=0;
public:
    Exit(QGraphicsView *view);
    void makeButton();
};

#endif // EXIT_H
