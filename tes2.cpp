#include "tes2.h"
#include <iostream>

Tes2::Tes2()
{
    pointlist_ = new QVector<Point>;
    lock = new QReadWriteLock;
}

Tes2::~Tes2(){
    qDebug()<<"~";
    delete pointlist_;
    pointlist_ = nullptr;
//    lock = nullptr;

}

double Tes2::lengthjudge(const QPoint point,
                         const QPoint point2){
    float x1, y1;
    double length;
    x1 = point.x() - point2.x();
    y1 = point.y() - point2.y();
    length = qPow(x1, 2) + qPow(y1, 2);
    length = qSqrt(length);
    return length;
}

bool Tes2::checkifout(const QPoint qpoint, const int l){
    if(qpoint.x() < image_.width() - l
        &&qpoint.x() > l
        &&qpoint.y() < image_.height() - l
        &&qpoint.y() > l){
        cio = true;
    }else cio = false;
    return cio;
}


bool Tes2::checkifather(const QPoint qpoint){
    returncheck=true;
    lock->lockForRead();
    for(iter = pointlist_->end() - 1;
         iter != pointlist_->begin();
         iter--){
        length = iter->l - 1;
        if(lengthjudge(qpoint, iter->xy) < length){
            returncheck = false;
            break;
        }else if(qpoint == iter->xy){
            returncheck = false;
            break;
        }
    }
    lock->unlock();
    return returncheck;
};

bool Tes2::checkif(const QRect rect,const double persent){

    count = 0;
    k_ = 0;
//    int rx, ry, x, y;
    cix = rect.topLeft().x();
    ciy = rect.topLeft().y();
    for(int i = 0; i <= rect.height(); i++){
        for(int j = 0; j <= rect.width(); j++){
            count++;
            x = cix + j;
            y = ciy + i;
            if(rgb == image_.pixel(QPoint(x, y))){
//                qDebug()<<"k_++";
                k_++;
            }
        }
    }
    checkr = k_ / count;
//    qDebug()<<"checkresult is"<<checkr<<Qt::endl;
    if(checkr >= persent) returncheck = true;
    else returncheck = false;
    return returncheck;
}
