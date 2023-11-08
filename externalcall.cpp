#include "externalcall.h"

ExternalCall::ExternalCall(const QPoint point1,
                           const QPoint point2,
                           const QImage* image)
{
    point_1 = point1;
    point_2 = point2;
    image_ = *image;
    rgb = image_.pixel(point_2);
    Check = true;
    pointreturn = new QVector<QPoint>;
}

ExternalCall::~ExternalCall(){

    delete pointreturn;
    pointreturn = nullptr;
}

ExternalCall::ExternalCall(const ExternalCall& t){
//    qDebug()<<"chongzaigouzao";
    point_1 = t.point_1;
    point_2 = t.point_2;
    image_ = t.image_;
    rgb = t.rgb;
    Check = t.Check;
    lock = t.lock;
    hasrun = t.hasrun;
    list = new QList<Point>(*t.list);
    pointlist_ = new QVector<Point>(*t.pointlist_);
    pointreturn = new QVector<QPoint>(*t.pointreturn);
}

void ExternalCall::operator= (ExternalCall const& t){
    qDebug()<<"chongzaifuzhi";
    point_1 = t.point_1;
    point_2 = t.point_2;
    image_ = t.image_;
    rgb = t.rgb;
    Check = t.Check;
    lock = t.lock;
    hasrun = t.hasrun;
    if(this != &t){
        delete pointlist_;
        delete list;
        delete pointreturn;
        list = new QList<Point>(*t.list);
        pointlist_ = new QVector<Point>(*t.pointlist_);
        pointreturn = new QVector<QPoint>(*t.pointreturn);
    }

}

QVector<QPoint> ExternalCall::listreturn(Point point){
    QVector<QPoint> listreturn;
    listreturn.prepend(point_2);
    listreturn.prepend(point.xy);
    Point point1=point;
    QVector<Point>::iterator iter1;
    lock->lockForRead();
    for(iter1=pointlist_->end();
         iter1!=pointlist_->begin();iter1--){
        if(iter1->xy==point1.fatherpoint){
            listreturn.prepend(iter1->xy);
            point1=*iter1;
        }
    }
    lock->unlock();
    listreturn.prepend(point_1);
    return listreturn;
}

bool ExternalCall::checkpathclear(const QPoint &qpoint, const QPoint &qpoint2){
    checkresult = true;
    len = lengthjudge(qpoint, qpoint2);
    xlen = qpoint.x() - qpoint2.x();
    ylen = qpoint.y() - qpoint2.y();
    tan = xlen / ylen;
    degree = atan(tan);
    for(int l = 1; l < len; l++){
        x_ = l * cos(degree);
        y_ = l * sin(degree);
        if((xlen > 0 && ylen > 0)||(xlen < 0 && ylen > 0)){
            x_ = -x_;
            y_ = -y_;
        }
        x = qpoint.x() + x_;
        y = qpoint.y() + y_;
        QRect rect(x - 1, y - 1, 2, 2);
        if(!checkif(rect, 0.8)){
            checkresult = false;
            break;
        }
    }

    return checkresult;
}

void ExternalCall::Returnpoint(Point &point){
//    qDebug()<<"first loop";
    while(Check){
        if(!list->isEmpty()){
            point22 = list->first();
            list->removeFirst();
            if(checkifout(point22.xy, 2)&&checkifather(point22.xy)){
                creatl(point22);
                lock->lockForWrite();
                pointlist_->append(point22);
                lock->unlock();
//                qDebug()<<"point22"<<point22.xy;
                emit showpoint();
                length = lengthjudge(point22.xy, point_2);
                if(length <= point22.l){
                    //判断与终点的距离，如果小于l，则将终点输入该节点坐标库
                    if(checkpathclear(point22.xy, point_2)){
                        *pointreturn = listreturn(point22);
                        //将所有point的父节点加入一个新的队列
                        emit pushpoint(); //将路径队列传给Widget类中
                        Check=false;
                    }else{
                        circlerect(point22);//qt进行类内调用
                    }
                }else circlerect(point22);//qt进行类内调用
            }
        }else if(pointlist_->isEmpty()){
            //            qDebug()<<"point1 is"<<point.xy;
            creatl(point);
            qDebug()<<"point1 is"<<point.xy;
            lock->lockForWrite();
            pointlist_->append(point);
            lock->unlock();
            length = lengthjudge(point.xy, point_2);

            if(length < point.l / 2){//判断与终点的距离，如果小于l，则将终点输入该节点坐标库
                *pointreturn = listreturn(point);
                //将所有point的父节点加入一个新的队列
                emit pushpoint(); //将路径队列传给Widget类中
                Check = false;
            }else{
                circlerect(point);//qt进行类内调用
                hasrun = true;
            }
        }else{
            Check=false;
            qDebug()<<"_________";
            emit showpoint();
            emit didntfindtheresult();
        }

    }

}
