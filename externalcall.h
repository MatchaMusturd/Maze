#ifndef EXTERNALCALL_H
#define EXTERNALCALL_H

//#include"generatelength.h"
#include"generpoint.h"
//#include"tes2.h"

class ExternalCall : public GenerPoint
{
public:

    QVector<QPoint>* pointreturn;

    ExternalCall(const QPoint,const QPoint, const QImage*);
    ExternalCall(const ExternalCall&);//重载构造函数
    void operator= (ExternalCall const&);//重载赋值函数
    ~ExternalCall();
    void Returnpoint(Point&);//迭代函数：输入初始节点
private:
    bool Check;//全局断点
    float length;
    bool checkresult;
    double degree, tan, len, xlen, ylen, x, y, x_, y_;
    Point point22;
//    GenerPoint* gp;
//    GenerateLength* gl;
    QVector<QPoint> listreturn(Point);
    bool checkpathclear(const QPoint&, const QPoint&);
};

#endif // EXTERNALCALL_H
