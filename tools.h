#ifndef TOOLS_H
#define TOOLS_H
#include <QtGlobal>
#include <QPointF>
#include <QDebug>
#include "math.h"

#define PI 3.1415

qreal angle_x_to_y(const QPointF &pt1, const QPointF &pt2){
    using namespace std;
    qreal dx = pt2.x() - pt1.x();
    qreal dy = pt2.y() - pt1.y();
    //qDebug() << pt2.x()<<" "<<pt2.y();
    //qDebug() << atan2(det, dot)*360/M_PI;
    qreal x=  -atan2(dy, dx)*180/PI;
    if(x>=0){
        x = 90-x;
    } else {
        if(x<0&&x>=-90){
            x = abs(x)+90;
        }
        else x = abs(x)-270;
    }
    //rqDebug() <<x;
    return x;
}

qreal abs(const qreal &x){
    return x>=0?x:-x;
}

#endif // TOOLS_H
