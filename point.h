#ifndef POINT_H
#define POINT_H

#include <memory>
#include<QPoint>
#include<QDebug>
#include <QSysInfo>
#include<QSharedDataPointer>

class Point{//每一个节点
public:
    Point();
//    ~Point();
    QPoint xy;
    QPoint fatherpoint;
    Point* next;
    int l, actualvalue, value;
};

#endif // POINT_H
