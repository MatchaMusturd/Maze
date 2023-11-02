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
    ~Point();
    QPoint xy;
    QPoint fatherpoint;
    int l;//每个点的步长
//    std::shared_ptr<Point> next;
//    QSharedPointer<Point> next;
    Point* next=nullptr;
    int actualvalue=0;//每个节点的实际代价
    int value=0;//节点总代价
//    double actualineratio;//实际代价除实际直线距离
//    inline static int count=0;//计数器
//    int pointcount;
};

class Queue{
//    QSharedPointer<Point> front;
//    QSharedPointer<Point> rear;
    Point* front;
    Point* rear;
//    QVector<Point*> pointslist;
public:
    int count=0;
    Queue();
    ~Queue();
    bool isEmpty();
    void enqueue(const QPoint,const QPoint,const int);
    void dequeue(Point&);
};

#endif // POINT_H
