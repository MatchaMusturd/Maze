#include "generatelength.h"

GenerateLength::GenerateLength()
{
    hasrun = false;
}

GenerateLength::~GenerateLength()
{
    if(hasrun){

        delete lenlist;
        lenlist = nullptr;
    }
}

void GenerateLength::creatl(Point &point){
    lenlist = new QVector<int>;
    px = point.xy.x();
    py = point.xy.y();
    for(int i = 0; i < 360; i += 10){
        check_ = true;
        r_ = 2;
        if(i > 180) angle = i - 180;
        else angle = i;
        arc = qDegreesToRadians(angle);
        rx = qCos(arc);
        ry = qSin(arc);
        if(i > 180){
            rx = -rx;
            ry = -ry;
        }
        while(check_){
            rx_ = r_ * rx;
            ry_ = r_ * ry;
            r_2 = r_ - 2;
            qpoint1 = QPointF(px + rx_, py + ry_);
            //            qDebug()<<"qpoint1"<<qpoint1;
            if(checkifout(qpoint1.toPoint(), 2)){

                QRect rect2(px + rx_ - 1, py + ry_ - 1, 2, 2);
                if(!checkif(rect2, 1)){
                    //                    qDebug()<<"r_2"<<r_2;
                    lenlist->append(r_2);
                    check_ = false;
                }
            }else{
                lenlist->append(r_2);
                check_ = false;
            }
            r_ += 2;
        }
    }
    sum = std::accumulate(lenlist->begin(), lenlist->end(), 0);
    //    qDebug()<<"sum"<<sum;
    size = lenlist->size();
    //    qDebug()<<"size"<<size;
    length = sum / size;
    //    qDebug()<<"length2"<<length2;
    //    qDebug()<<"point.xy"<<point.xy;
    if(length < 21) point.l = length;
    else point.l = length / 2;
    if(point.l % 2 == 1) point.l += 1;
}
