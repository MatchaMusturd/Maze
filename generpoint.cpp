#include "generpoint.h"

GenerPoint::GenerPoint()
{
    list = new QList<Point>;
}

GenerPoint::~GenerPoint()
{
    delete list;
    list = nullptr;
}

void GenerPoint::actualvalue(const Point& point){

    if(point.actualvalue != 0)
        actual_value = point.l + point.actualvalue;
    else actual_value = point.l;
    //    return actual_value;
}

double GenerPoint::lineratio(const QPoint& qpoint){

    l1 = lengthjudge(qpoint, point_1);
    l2 = lengthjudge(qpoint, point_2);
    r__ = l2 / l1;
    return r__;
}

void GenerPoint::circlerect(Point &point){

    l = point.l;
//    qDebug()<<"l"<<l;
    px=point.xy.x();
    py=point.xy.y();
    for(int i = 0; i < 360; i += 5){
        k = 0;
        if(i > 180) angle = i - 180;
        else angle = i;
        arc = qDegreesToRadians(angle);
        rx = qCos(arc);
        ry = qSin(arc);
        if(i > 180){
            rx = -rx;
            ry = -ry;
        }
        qpoint1 = QPointF(px + l * rx, py + l * ry);
        //        qDebug()<<"qpoint1"<<qpoint1;
        if(checkifout(qpoint1.toPoint(), 2)
            &&checkifather(qpoint1.toPoint())){

            for(int r = 2; r < l + 1;r += 2){
                rx_ = r * rx;
                ry_ = r * ry;
                QRect rect2(px + rx_ - 1, py + ry_ - 1, 2, 2);
                if(checkif(rect2, 1)) k++;
                else break;
            }
            if(k == l / 2){
                i += 55;
                point_ = qpoint1.toPoint();
                actualvalue(point);
                //第一个参数是当前节点，第二个参数是上一个节点
                ratio = lineratio(point_);
                //实际代价除实际直线代价
                estivalue_ = ratio * actual_value;
                value_ = actual_value + estivalue_;
                Point point_1;
                //                qDebug()<<"new point";
                point_1.actualvalue = actual_value;
                point_1.value = value_;
                point_1.fatherpoint = point.xy;
                point_1.xy = point_;

                if(list->isEmpty()) list->append(point_1);
                else{
                    if(value_ > list->last().value) list->append(point_1);
                    else if(value_ < list->first().value) list->prepend(point_1);
                    else{
                        for(int i = list->size() - 1; i >= 0; i--){
                            if(value_ >= list->at(i).value){
                                list->insert(i + 1, point_1);
                                break;
                            }
                        }
                    }
                }
                continue;
            }
        }

    }
//    qDebug()<<"size of list is "<<list->size();
    //    for(int i = 0; i < list->size(); i++){
    //        qDebug()<<"   "<<list->at(i).xy;
    //    }
};
