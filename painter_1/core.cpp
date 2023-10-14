#include "core.h"
#include "qdebug.h"
#include "qmath.h"


Core::Core(const Point_ point_,
           const QPoint point2,
           const QImage *image){
//    pointlist_.append(point_);
//    point_2=point2;
//    image_=*image;

}

Core::~Core(){

}

Point_::Point_(){
    Point_::count++;
    pointcount=Point_::count;
//    furtherpoint=new QVector<int>;
    pointlist_=new QVector<QPoint>;
}

Point_::~Point_(){

}

void Core::Returnpoint(Point_ *point){

//    pointlist_.append(*point);
    double length=lengthjudge(*point);
    if(length<30){//判断与终点的距离，如果小于50，则将终点输入该节点坐标库
        qDebug()<<"length less than 50"<<Qt::endl;
        Check=false;
        emit pushpoint(*point);
    }else if(Check){//进行类内调用

//        emit showpoint();
//        QVector<double> angle_;
//        angle_=angle(*point);//获取可行角度列表
//        judgeanglepushpoint(angle_,point);
    }
}

double Core::lengthjudge(const Point_ point){
    float x1,y1;
    double length;
//    x1=point.xy.x()-point_2.x();
//    y1=point.xy.y()-point_2.y();
    length=qPow(x1,2)+qPow(y1,2);
    length=qSqrt(length);
    return length;
}

//QVector<double> Core::angle(const Point point){
//    bool check;
//    QVector<double> *angle_=new QVector<double>;
//    for(int i=0;i<360;i+=10){//围绕初始点的一周每隔10°进行一次检查
//        check=inputi_returnk(i,point);//5个检查点都能通过
//        if(check) *angle_=checkifatherpoint(&i,angle_,point);
//    }
//    return *angle_;
//}

//bool Core::inputi_returnk(const int i,const Point point){
//    QPoint point_1;
//    double degree=0;
//    int k=0;
//    float degree__;
//    bool checkit;
//    float qs,qc;
//    if(i>180) degree=i-180;
//    else degree=i;
//    degree__=qDegreesToRadians(double(degree));
//    for(int r=1;r<length_+1;r+=1){//检查一条长为50的线上的每隔5一个检查点是否都是可行的
//        qs=r*qSin(degree__);
//        qc=r*qCos(degree__);
//        if(qs<1) qs=0;
//        if(qc<1) qc=0;
//        if(i>=0&&i<180){
//            point_1.setX(point.xy.x()+ qc);
//            point_1.setY(point.xy.y()+ qs);
//        }else{
//            point_1.setX(point.xy.x()- qc);
//            point_1.setY(point.xy.y()- qs);
//        }
//        if(point_1.y()<image_.height()&&
//            point_1.x()<image_.width()){
//            if(image_.pixel(point.xy)==image_.pixel(point_1)) k++;
//            else{
//                k=0;
//                break;
//            }
//        }else{
//            k=0;
//            break;
//        }
//    }
//    if(k==length_) checkit=true;
//    else checkit=false;
//    return checkit;
//}

//QVector<double> Core::checkifatherpoint(int *i,
//                                        QVector<double> *angle_,
//                                        const Point point){

////    int reverangle;
//    bool check=true;

////    if(*i>180) reverangle=*i-180;
////    else reverangle=*i;
//    QVector<double>::iterator iter_;
//    if(point.angle!=NULL){

//        if(abs(*i-point.angle)<10){

//            for(iter_=angle_->begin();iter_!=angle_->end();){
//                if(*i-*iter_<60) iter_=angle_->erase(iter_);
//                else iter_++;
//            }
//            (*i)+=60;
//            check=false;
//        }
//    }
//    break;
//    QVector<Point>::iterator iter;
//    for(iter=pointlist_.begin();iter!=pointlist_.end();iter++){
//        if(iter->pointcount==Point::count-1){//是否是上一级的节点
//            if(abs(iter->angle-reverangle)<=10){//角度是否与父节点相同
//                qDebug()<<"same angle"<<iter->xy<<Qt::endl;
//                if(point->pointlist_->isEmpty()){
//                    if(!iter->pointlist_->isEmpty()){
//                        QVector<QPoint>::iterator iter_;
//                        for(iter_=iter->pointlist_->begin();
//                             iter_!=iter->pointlist_->end();
//                             iter_++){
////                            qDebug()<<"pointlist_ element"<<*iter_<<Qt::endl;
//                            point->pointlist_->append(*iter_);
//                        }
////                        point->pointlist_=iter->pointlist_;
//                    }
//                    point->pointlist_->append(iter->xy);
//                }else if(!point->pointlist_->contains(iter->xy)){
//                    point->pointlist_->append(iter->xy);
//                }

//            }
//        }
//    }
//    if(check) angle_->append(*i);
//    //角度与父节点不相同，将可行角度输入这次迭代的角度库中

//    return *angle_;
//}

//void Core::judgeanglepushpoint(const QVector<double> angle_,Point *point){
//    QVector<double> angle1;
//    int size;
////    int siz=point.pointlist_->size();
////    qDebug()<<"size of pointlist_ is"<<siz<<Qt::endl;
//    if(!angle_.isEmpty()){
//        angle1=middleangle(angle_);
//        size=angle1.size();
//        qDebug()<<"size of angle list is"<<size<<Qt::endl;
////        count_1=0;
//        QPoint qpoint;

//        for(int i=0;i<size;i++){
//            qDebug()<<"angles"<<angle1.at(i)<<Qt::endl;
//            qpoint=getpoint(angle1.at(i),*point);
//            //对于每个可行角度，返回一个可行点
////            QtConcurrent::run(this,
////                              &Core::pointistrue,
////                              qpoint,angle1.at(i),point);
//            pointistrue(qpoint,angle1.at(i),point);
//        }

//    }
//}

//QVector<double> Core::middleangle(const QVector<double> angle_){
//    QVector<double> angle1;
//    int size_=angle_.size();

//    if(size_==1) angle1.append(angle_.at(0));
//    else{
//        int ini=0;

//        for(int i=0;i<size_;i++){//取出每组角度中值
//            int endi;
//            if(i!=size_-1){
//                if(angle_.at(i)+10==angle_.at(i+1)){
//                    if(i+1==size_-1){
//                        endi=(angle_.at(i+1)+angle_.at(ini))/2;
//                        angle1.append(endi);
//                    }
//                    continue;
//                }else {
//                    endi=(angle_.at(i)+angle_.at(ini))/2;
//                    ini=i+1;
//                    angle1.append(endi);
//                }
//            }else if(angle_.at(i)-10!=angle_.at(i-1)){
//                angle1.append(angle_.at(i));
//            }
//        }
//    }
//    return angle1;
//}


//QPoint Core::getpoint(const double anglei,const Point point){
//    QPoint point_1;
//     double angle__,angles;
//    float qs,qc;

//    if(anglei>180) angles=anglei-180;
//    else angles=anglei;

//    angle__=qDegreesToRadians(angles);
//    qs=length_*qSin(angle__);
//    qc=length_*qCos(angle__);
//    if(qs<1) qs=0;
//    if(qc<1) qc=0;
//    if(anglei>=0&&anglei<180){
//        point_1.setX(point.xy.x()+ qc);
//        point_1.setY(point.xy.y()+ qs);
//    }else{
//        point_1.setX(point.xy.x()- qc);
//        point_1.setY(point.xy.y()- qs);
//    }
//    return point_1;
//}

//bool Core::pointisfalse(const QPoint point_1){
//    bool check=false;
//    bool returncheck;
//    QPoint tempoint;
//    int si=pointlist_.size();
//    for(int b=0;b<si;b++){
//        tempoint=pointlist_.at(b).xy;
//        if(point_1.x()>tempoint.x()-30&&
//            point_1.x()<tempoint.x()+30&&
//            point_1.y()>tempoint.y()-30&&
//            point_1.y()<tempoint.y()+30){
//            check=true;
//            break;
//        }
//    }
//    if(point_1.x()<image_.width()
//        &&point_1.y()<image_.height()
//        &&!check&&Check) returncheck=true;
//    else returncheck=false;
//    return returncheck;
//}

//void Core::pointistrue(const QPoint point_1,const double anglei,Point *point){
//    bool check=pointisfalse(point_1);
//    double angleii;
//    if(anglei>180) angleii=anglei-180;
//    else angleii=anglei+180;
//    if(check){
////        count_1++;
////        if(count_1==1) Point::count++;
//        Point point11;
//        point->furtherpoint->append(point11.pointcount);
//        qDebug()<<"count is"<<point11.pointcount<<Qt::endl;
////        qDebug()<<"point is"<<point_1<<Qt::endl;
//        point11.xy=point_1;
//        point11.angle=angleii;
//        Returnpoint(&point11);

//    }
//}
