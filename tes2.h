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
#include<QReadWriteLock>
#include"point.h"


class Tes2 : public QObject
{
    Q_OBJECT
private:

    int count=0;
    QPoint point_2;//终点
    QPoint point_1;//起点
    QImage image_;//图像
    bool Check;//全局断点
    QList<Point> *list;
    double size2,size1;
    QRgb rgb;

    double lengthjudge(const QPoint,const QPoint);
    bool checkif(const QRect,const double);
    bool checkifout(const QPoint,const int);
    QVector<QPoint> listreturn(Point);
    auto circlerect(Point&);
    auto checkifather(const QPoint);
    void creatl(Point&);
    bool checkpathclear(const QPoint&, const QPoint&);
    int actualvalue(const Point&);
    double lineratio(const QPoint&);

public:
    QReadWriteLock *lock;
    QVector<Point> *pointlist_;
    QElapsedTimer *timer;
    explicit Tes2(const QPoint,const QPoint,const QImage*);
    ~Tes2();
    void Returnpoint(Point&);//迭代函数：输入初始节点
signals:
    void pushpoint(QVector<QPoint>);
     void showpoint();
};

#endif // TES2_H
