#ifndef GENERPOINT_H
#define GENERPOINT_H

#include"generatelength.h"

class GenerPoint : public GenerateLength
{
public:
    GenerPoint();
    ~GenerPoint();
protected:
    void circlerect(Point&);
    QList<Point> *list;
//protected:
private:
    int l, k, value_, actual_value;
    float px, py;
    double angle, arc, rx, ry, rx_, ry_, ratio, estivalue_, l1, l2, r__;
    QPointF qpoint1;//临时坐标
    QPoint point_;//临时坐标

    double lineratio(const QPoint&);
    void actualvalue(const Point&);
};

#endif // GENERPOINT_H
