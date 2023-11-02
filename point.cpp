#include "point.h"


Point::Point(){
//        Point::count++;
//        pointcount=Point::count;
}

Point::~Point(){
}

Queue::Queue(){
        front=rear=nullptr;

}

Queue::~Queue(){
    delete front;
    delete rear;

}

bool Queue::isEmpty(){
    return front==nullptr;
}

void Queue::enqueue(const QPoint xy,const QPoint dad,const int value_){
    Point* point_ =nullptr;
    try {
        point_=new Point;

    } catch (std::bad_alloc& k) {
        qDebug()<<"bad_alloc"<<k.what()<<Qt::endl;
    }

    point_->fatherpoint=dad;
    point_->xy=xy;
//    point_->actualvalue=actual_value;
    point_->value=value_;
    point_->next=nullptr;
    if(isEmpty()) front=rear=point_;
    else{
        rear->next=point_;
        rear=point_;
    }
    count++;
}

void Queue::dequeue(Point &returnpoint){
    if(front==nullptr) rear=nullptr;
    else{

        returnpoint.xy=front->xy;
        returnpoint.fatherpoint=front->fatherpoint;
        Point* deletepoint=front;
        front=deletepoint->next;
        count--;
        if(front==nullptr) rear=nullptr;
        delete deletepoint;
    }
}
