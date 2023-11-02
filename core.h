#ifndef CORE_H
#define CORE_H

#include "qimage.h"
#include<QVector>
#include<QObject>
#include<QtConcurrent>
#include<QFuture>

class Point_{//每一个节点

public:
    Point_();
    ~Point_();
    QPoint xy;
//    bool checky=false;
    inline static int count=0;//计数器
//    QVector<int> *furtherpoint;
    QVector<QPoint> *pointlist_;
//    int angle;
    int pointcount;

};

class Core:public QObject
{
     Q_OBJECT
private:
     int length_=50;
    int count_1;
//    static QPoint point_2;
//    static QImage image_;
    bool Check=true;//全局断点

    bool inputi_returnk(const int,const Point_);
    //输入角度、初始点坐标，获得判断路径是否通行的值
    QVector<double> checkifatherpoint(int *,QVector<double>*,const Point_);
    //当前角度、可行角度列表
    QVector<double> middleangle(const QVector<double>);
    //输入可行节点列表，输出可行节点中值列表
    QPoint getpoint(const double,const Point_);
    //输入可行角度和父节点，获得此节点坐标
    void pointistrue(const QPoint,const double,Point_ *);
    //当前节点坐标、角度.判断条件是否符合进行下次迭代，如果可以，将该节点输入到节点列表
    void judgeanglepushpoint(const QVector<double>,Point_ *);
    //输入总可行角度列表、父节点
    QVector<double> angle(const Point_);
    //输入父节点，返回可行角度列表
    bool pointisfalse(const QPoint);
    //输入当前节点坐标，检查当前节点是否合法
    double lengthjudge(const Point_);
    //判断与终点的距离

public:
//    static QVector<Point_> pointlist_;
    explicit Core(const Point_,const QPoint,const QImage*);
    ~Core();
    void Returnpoint(Point_ *);//迭代函数：输入初始节点
signals:
    void pushpoint(Point_);
//    void showpoint();

};

#endif // CORE_H
