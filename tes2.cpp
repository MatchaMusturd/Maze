#include "tes2.h"
#include <iostream>

Tes2::Tes2(const QPoint point2,
           const QImage* image)
{
    point_2=point2;
    image_=*image;
    pointlist_.clear();
//    q=new Queue;
    timer=new QElapsedTimer;
    list=new QList<Point>;
//    queue=new Queue;
}

Tes2::~Tes2(){
//    delete q;
    delete timer;
    delete list;
}


double Tes2::lengthjudge(const QPoint point,
                         const QPoint point2){
    float x1,y1;
    double length;
    x1=point.x()-point2.x();
    y1=point.y()-point2.y();
    length=qPow(x1,2)+qPow(y1,2);
    length=qSqrt(length);
    return length;
}

bool Tes2::checkifout(const QPoint qpoint,const int l){
    bool check;
    if(qpoint.x()<image_.width()-l
        &&qpoint.x()>l
        &&qpoint.y()<image_.height()-l
        &&qpoint.y()>l){
        check=true;
    }else check=false;
    return check;
}


auto Tes2::checkifather(const QPoint qpoint){
    bool returncheck=true;
    int length;
    QVector<Point>::iterator iter;
    for(iter=pointlist_.begin();
         iter!=pointlist_.end();
         iter++){
        length=iter->l-1;
        if(lengthjudge(qpoint,iter->xy)<length){
            returncheck=false;
            break;
        }
    }
    return returncheck;
};

int Tes2::actualvalue(const QPoint& qpoint,const Point& point){
    int actualvalue;
    int x_,y_;
    QPoint qpoint1=point.xy;
    x_ = abs(qpoint.x() - qpoint1.x());
    y_ = abs(qpoint.y() - qpoint1.y());
    if(point.actualvalue != 0)
        actualvalue = x_ + y_ + point.actualvalue;
    else actualvalue = x_ + y_;
    return actualvalue;
}

int Tes2::estivalue(const QPoint& qpoint){
    int value;
    int x_,y_;
    x_=abs(qpoint.x()-point_2.x());
    y_=abs(qpoint.y()-point_2.y());
    value=x_+y_;
    return value;
}

auto Tes2::circlerect(Point &point){
    float px,py;
    double rx,ry,rx_,ry_;
    int k;
    double angle;
    double arc;
    int l=point.l;
    QPoint qpoint=point.xy;
    px=qpoint.x();
    py=qpoint.y();
    for(int i=0;i<360;i+=5){
        QPointF qpoint1;
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

                QPoint point_ = qpoint1.toPoint();
                int actual_value = actualvalue(point_,point);
                int estivalue_ = estivalue(point_);
                Point point_1;
                int value_ = actual_value + estivalue_;
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
                                list->insert(i+1, point_1);
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
    for(iter1=pointlist_.end();
         iter1!=pointlist_.begin();iter1--){
        if(iter1->xy==point1.fatherpoint){
            listreturn.prepend(iter1->xy);
            point1=*iter1;
        }
    }
    listreturn.prepend(point_1);
    size1=listreturn.size();
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
    double len=lengthjudge(qpoint, qpoint2);
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

QVector<QPoint> Tes2::pointlist2return(){
    QVector<QPoint> listreturn;
    QVector<Point>::iterator iter1;
    for(iter1=pointlist_.end();
         iter1!=pointlist_.begin();
         iter1--) listreturn.prepend(iter1->xy);
    return listreturn;
}

void Tes2::Returnpoint(Point &point){
    float length;
    while(Check){

        if(!list->isEmpty()){
            Point point22;
            point22=list->first();
            list->removeFirst();
//            q->dequeue(point22);
            if(checkifout(point22.xy,2)&&checkifather(point22.xy)){
                count++;
                qDebug()<<"number "<<count<<"point is "<<point22.xy;
                creatl(point22);
                pointlist_.append(point22);
                length=lengthjudge(point22.xy, point_2);

                if(length<point22.l){
                    //判断与终点的距离，如果小于l，则将终点输入该节点坐标库
                    if(checkpathclear(point22.xy, point_2)){
                        qDebug() << "The operation took" << timer->elapsed()<< "milliseconds";
                        QVector<QPoint> pointreturn=listreturn(point22);
                        QVector<QPoint> pointlist2=pointlist2return();
                        size2=pointlist2.size();
                        //将所有point的父节点加入一个新的队列
                        emit pushpoint(pointreturn); //将路径队列传给Widget类中
                        emit showpoint(pointlist2);
                        double ratio;
                        ratio=size1/size2;
                        qDebug()<<"ratio is "<<ratio;
                        Check=false;
                    }else{
                        circlerect(point22);//qt进行类内调用
//                        qDebug()<<"found the point but there's a wall"<<Qt::endl;
                    }
                }else  circlerect(point22);//qt进行类内调用
            }
//            else if(!checkifather(point22.xy)) qDebug()<<"father point";
        }else if(pointlist_.isEmpty()){
            creatl(point);
            point_1=point.xy;
            pointlist_.append(point);
            length=lengthjudge(point.xy,point_2);

            if(length<point.l/2){//判断与终点的距离，如果小于l，则将终点输入该节点坐标库
                QVector<QPoint> pointreturn=listreturn(point);
                //将所有point的父节点加入一个新的队列
                emit pushpoint(pointreturn); //将路径队列传给Widget类中
                Check=false;
            }else{
                circlerect(point);//qt进行类内调用
                QVector<QPoint> pointlist2=pointlist2return();
                emit showpoint(pointlist2);
            }
        }else{
//            qDebug()<<"size "<<list->size();
            QVector<QPoint> pointlist2=pointlist2return();
//            qDebug()<<"pointlist is empty";
            emit showpoint(pointlist2);
            Check=false;
            pointlist_.clear();
            qDebug()<<"didn't get the result";
        }

    }

}


bool Tes2::checkif(const QRect rect,const double persent){
    bool returncheck;
    float count = 0,k = 0;
    int rx,ry,x,y;
    float checkresult;
    QRgb rgb = image_.pixel(point_2);
    rx = rect.topLeft().x();
    ry = rect.topLeft().y();
    for(int i = 0; i <= rect.height(); i++){
        for(int j = 0; j <= rect.width(); j++){
            count++;
            x = rx + j;
            y = ry + i;
            if(rgb == image_.pixel(QPoint(x,y))) k++;
        }
    }
    checkresult=k/count;
//    qDebug()<<"checkresult is"<<checkresult<<Qt::endl;
    if(checkresult>=persent) returncheck=true;
    else returncheck=false;
    return returncheck;
}
