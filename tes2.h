#ifndef TES2_H
#define TES2_H

#include <QObject>
#include<QRect>

#include<QtMath>
#include<QImage>
#include<QList>
#include<QtMath>
#include<QMutex>
#include<QElapsedTimer>

#include"point.h"


class Tes2 : public QObject
{
    Q_OBJECT
private:

//     Queue* q;
    int count=0;
    QPoint point_2;//终点
    QPoint point_1;//起点
    QImage image_;//图像
    bool Check=true;//全局断点
    QList<Point> *list;
    double size2,size1;

    double lengthjudge(const QPoint,const QPoint);
    bool checkif(const QRect,const double);
    bool checkifout(const QPoint,const int);
    QVector<QPoint> listreturn(Point);
    QVector<QPoint> pointlist2return();
    auto circlerect(Point&);
    auto checkifather(const QPoint);
    void creatl(Point&);
    bool checkpathclear(const QPoint&, const QPoint&);
    int actualvalue(const QPoint&,const Point&);
    int estivalue(const QPoint&);
    QVector<Point> pointlist_;

public:
    QElapsedTimer *timer;
    explicit Tes2(const QPoint,const QImage*);
    ~Tes2();
    void Returnpoint(Point&);//迭代函数：输入初始节点
signals:
    void pushpoint(QVector<QPoint>);
     void showpoint(QVector<QPoint>);
};

#endif // TES2_H
