#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <QApplication>

class myApplication : public QApplication {
  public:
    myApplication(int argc ,char** argv):QApplication(argc, argv){}
    ~myApplication(){}
/*
    bool notify(QObject* object,QEvent* event)
    {
        if(event->type()==QEvent::KeyPress) return true;
        return object->event(event);
    }
*/
};
#endif // MYAPPLICATION_H
