#include "tes2.h"
#include <iostream>

Tes2::Tes2(const QPoint point1,
            const QPoint point2,
            const QImage* image)
{
    point_1 = point1;
    point_2 = point2;
    image_ = *image;
//    pointlist_.clear();
    pointlist_ = new QVector<Point>;
    Check = true;
//    q=new Queue;
    timer = new QElapsedTimer;
    list = new QList<Point>;
    rgb = image_.pixel(point_2);
    lock = new QReadWriteLock;
//    queue=new Queue;
}

Tes2::~Tes2(){
    delete pointlist_;
    delete timer;
    delete list;
    delete lock;
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
    bool check;
    if(qpoint.x() < image_.width() - l
        &&qpoint.x() > l
        &&qpoint.y() < image_.height() - l
        &&qpoint.y() > l){
        check = true;
    }else check = false;
    return check;
}


auto Tes2::checkifather(const QPoint qpoint){
    bool returncheck=true;
    int length;
    QVector<Point>::iterator iter;
//    lock->lockForRead();
    for(iter=pointlist_->begin();
         iter!=pointlist_->end();
         iter++){
        length=iter->l-1;
        if(lengthjudge(qpoint, iter->xy) < length){
            returncheck=false;
            break;
        }
    }
//    lock->unlock();
    return returncheck;
};

int Tes2::actualvalue(const Point& point){
    int actualvalue;
    if(point.actualvalue != 0)
        actualvalue = point.l + point.actualvalue;
    else actualvalue = point.l;
    return actualvalue;
}

double Tes2::lineratio(const QPoint& qpoint){
    double l1, l2, r;
    l1 = lengthjudge(qpoint, point_1);
    l2 = lengthjudge(qpoint, point_2);
    r = l2 / l1;
    return r;
}


auto Tes2::circlerect(Point &point){
//    qDebug()<<"into the criclerect";
    float px, py;
    double rx,ry,rx_,ry_;
    int k;
    double angle;
    double arc;
    int l = point.l;
    QPoint point_;//临时坐标
    QPointF qpoint1;//临时坐标
    int actual_value;//实际代价
    double ratio;//距离终点距离与距离起点距离比值
    double estivalue_;//预估代价
    int value_;//总代价
    px=point.xy.x();
    py=point.xy.y();
    for(int i=0;i<360;i+=5){
        k=0;
        if(i > 180) angle = i - 180;
        else angle = i;
        arc = qDegreesToRadians(angle);
        rx = qCos(arc);
        ry = qSin(arc);
        if(i>180){
            rx = -rx;
            ry = -ry;
        }
        qpoint1 = QPointF(px + l * rx, py + l * ry);
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
                actual_value = actualvalue(point);
                //第一个参数是当前节点，第二个参数是上一个节点
                ratio = lineratio(point_);
                //实际代价除实际直线代价
                estivalue_ = ratio * actual_value;
                value_ = actual_value + estivalue_;
                Point point_1;

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
};

QVector<QPoint> Tes2::listreturn(Point point){
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
    size1 = listreturn.size();
    qDebug()<<"steps count is "<<size1;

//    QPoint qpoint1;
//    for(int j = 0; j < listreturn.size() - 1; j++){
//        qpoint1 = listreturn.at(j);
//        for(int i = j + 1; i < listreturn.size() ; i++){
//            if(!checkpathclear(qpoint1, listreturn.at(i))){
//                while(i - j > 2){
//                    listreturn.remove(j + 1);
//                    i--;
//                }
//                break;
//            }

//        }
//    }
    return listreturn;
}

void Tes2::creatl(Point &point){
    QVector<int> *lenlist=nullptr;
    int r;
    double angle,arc,rx,ry,px,py,rx_,ry_;
    bool check;
    lenlist=new QVector<int>;
    px=point.xy.x();
    py=point.xy.y();
    for(int i=0;i<360;i+=10){
        QPointF qpoint1;
        int r_2;
        check=true;
        r=2;
        if(i>180) angle=i-180;
        else angle=i;
        arc=qDegreesToRadians(angle);
        rx=qCos(arc);
        ry=qSin(arc);
        if(i>180){
            rx=-rx;
            ry=-ry;
        }
        while(check){
            rx_=r*rx;
            ry_=r*ry;
            r_2=r-2;

            qpoint1=QPointF(px+rx_,py+ry_);

            if(checkifout(qpoint1.toPoint(),2)){

                QRect rect2(px+rx_-1,py+ry_-1,2,2);
                if(!checkif(rect2,0.85)){
                    lenlist->append(r_2);
                    check=false;
                }
            }else{
                lenlist->append(r_2);
                check=false;
            }
            r+=2;
        }
    }
    int sum=std::accumulate(lenlist->begin(),lenlist->end(),0);
    int size=lenlist->size();
    int length2=sum/size;
    if(length2<21)point.l=length2;
    else point.l=length2/2;

    if(point.l%2==1) point.l+=1;
    delete lenlist;
}

bool Tes2::checkpathclear(const QPoint &qpoint,const QPoint &qpoint2){
    bool checkresult=true;
    double xlen,ylen;
    double len = lengthjudge(qpoint, qpoint2);
    xlen=qpoint.x() - qpoint2.x();
    ylen=qpoint.y() - qpoint2.y();
    double tan=xlen/ylen;
    double degree=atan(tan);
    double x_,y_,x,y;
    for(int l = 1; l < len; l++){
        x_=l*cos(degree);
        y_=l*sin(degree);
        if((xlen>0&&ylen>0)||(xlen<0&&ylen>0)){
            x_ = -x_;
            y_ = -y_;
        }
        x=qpoint.x()+x_;
        y=qpoint.y()+y_;
        QRect rect(x-1,y-1,2,2);
        if(!checkif(rect, 0.8)){
            checkresult=false;
            break;
        }
    }

    return checkresult;
}


void Tes2::Returnpoint(Point &point){
    float length;
    while(Check){

        if(!list->isEmpty()){
            Point point22;
            point22=list->first();
            list->removeFirst();
            if(checkifout(point22.xy, 2)&&checkifather(point22.xy)){
                count++;
                creatl(point22);
                lock->lockForWrite();
                pointlist_->append(point22);
                lock->unlock();
                emit showpoint();
                length=lengthjudge(point22.xy, point_2);
                if(length<point22.l){
                    //判断与终点的距离，如果小于l，则将终点输入该节点坐标库
                    if(checkpathclear(point22.xy, point_2)){
                        double seconds = double(timer->elapsed()) / 1000;
                        qDebug() << "The operation took" << seconds<< "seconds";
                        QVector<QPoint> pointreturn = listreturn(point22);
                        lock->lockForRead();
                        size2 = pointlist_->size();
                        //将所有point的父节点加入一个新的队列
                        lock->unlock();
                        emit pushpoint(pointreturn); //将路径队列传给Widget类中
                        double ratio;
                        ratio=size1 / size2;
                        qDebug()<<"ratio is "<<ratio;
                        Check=false;
                    }else{
                        circlerect(point22);//qt进行类内调用
//                        qDebug()<<"found the point but there's a wall"<<Qt::endl;
                    }
                }else  circlerect(point22);//qt进行类内调用
            }
//            else if(!checkifather(point22.xy)) qDebug()<<"father point";
        }else if(pointlist_->isEmpty()){
            creatl(point);
//            point_1 = point.xy;
//            qDebug()<<"point_1"<<point.xy;
            lock->lockForWrite();
            pointlist_->append(point);
            lock->unlock();
            length = lengthjudge(point.xy,point_2);

            if(length < point.l/2){//判断与终点的距离，如果小于l，则将终点输入该节点坐标库
                QVector<QPoint> pointreturn = listreturn(point);
                //将所有point的父节点加入一个新的队列
                emit pushpoint(pointreturn); //将路径队列传给Widget类中
                Check = false;
            }else{
                circlerect(point);//qt进行类内调用
//                QVector<QPoint> pointlist2=pointlist2return();
//                emit showpoint();
            }
        }else{
//            qDebug()<<"size "<<list->size();
//            QVector<QPoint> pointlist2=pointlist2return();
            emit showpoint();
            Check=false;
//            lock->lockForWrite();
//            pointlist_->clear();
//            lock->unlock();
            qDebug()<<"didn't get the result";
        }

    }

}


bool Tes2::checkif(const QRect rect,const double persent){
    bool returncheck;
    float count = 0,k = 0;
    int rx, ry, x, y;
    float checkresult;

    rx = rect.topLeft().x();
    ry = rect.topLeft().y();
    for(int i = 0; i <= rect.height(); i++){
        for(int j = 0; j <= rect.width(); j++){
            count++;
            x = rx + j;
            y = ry + i;
            if(rgb == image_.pixel(QPoint(x, y))) k++;
        }
    }
    checkresult = k / count;
//    qDebug()<<"checkresult is"<<checkresult<<Qt::endl;
    if(checkresult >= persent) returncheck = true;
    else returncheck = false;
    return returncheck;
}
