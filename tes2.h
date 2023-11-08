#ifndef TES2_H
#define TES2_H

#include <QObject>
#include<QRect>

#include<QtMath>
#include<QImage>
#include<QList>
#include<QtMath>
#include<QMutex>

#include<QReadWriteLock>
#include"point.h"


class Tes2 : public QObject
{
    Q_OBJECT
private:
    QVector<Point>::iterator iter;
    float checkr, count, k_, x1, y1;
    bool returncheck, cio;
    double length_;
    int r_2, r, actual_value, sum, size, length2, cix, ciy, length, x, y;

protected:
    QRgb rgb;
    QImage image_;//图像

    bool checkif(const QRect,const double);
    bool checkifout(const QPoint,const int);
    bool checkifather(const QPoint);

public:
    QPoint point_1;//起点
    QPoint point_2;//终点
    QReadWriteLock* lock;
    QVector<Point>* pointlist_;
    static double lengthjudge(const QPoint,const QPoint);
    explicit Tes2();
    ~Tes2();

signals:
    void pushpoint();
    void showpoint();
    void didntfindtheresult();
};

#endif // TES2_H
