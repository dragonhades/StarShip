#ifndef EXIT_H
#define EXIT_H

#include <QGraphicsRectItem>
#include <QApplication>

class Exit : public QGraphicsRectItem {
    QApplication *a;
public:
    Exit(QApplication *a);
    void keyPressEvent(QKeyEvent *event);
};

#endif // EXIT_H
