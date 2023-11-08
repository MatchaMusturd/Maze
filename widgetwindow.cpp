#include "widgetwindow.h"

WidgetWindow::WidgetWindow()
{
    countpoint1 = 0;
    countpoint2 = 0;
    adresslist = new QVector<QByteArray>;

}

WidgetWindow::~WidgetWindow()
{
    delete adresslist;

}

void WidgetWindow::focusInEvent(QFocusEvent *event)
{
    QWidget::focusInEvent(event);
}

void WidgetWindow::wheelEvent(QWheelEvent* event){
    wid=this->geometry().width();
    hei=this->geometry().height();
    if(changable){
        double rowschange=50 * com;
        if(event->angleDelta().y()>0)
            this->resize(QSize(wid + rowschange, hei + 50));
        else this->resize(QSize(wid - rowschange, hei - 50));
    }
}

void WidgetWindow::resizeEvent(QResizeEvent *){

    if( changable){
        cv::Mat mat_11;

        mat_11=resize_(*mat);
        hidepoints=true;
        hideline=true;
        append_(mat_11);
    }

}

void WidgetWindow::mousePressEvent(QMouseEvent *event){
    changable = false;
    //保护在鼠标点击事件过程中图像大小不会受到影响
    if(!image->isNull()&&!isrunning){
        this->setFocus(); //单单这句是无效的
        QWidget::mousePressEvent(event);
        if(event->button() == Qt::LeftButton)
        {
            point1 = event->pos();
            initial();
            if(countpoint2 > 1){
                if(countpoint1 == 1){
                    point1list->pop_back();
                    point1list->append(point1);
                }else if(point1list->empty()){
                    countpoint1++;
                    point1list->append(point1);
                }
            }else{
                if(point1list->empty()&&point2list->empty()){
                    point1first = true;
                }
                countpoint1++;
                point1list->append(point1);
            }
            qDebug()<<"the"<<countpoint1<<"th point start from"<<point1;
            this->update();
        }else if(event->button() == Qt::RightButton){
            point2 = event->pos();
            initial();
            if(countpoint1 > 1){
                if(countpoint2 == 1){
                    point2list->pop_back();
                    point2list->append(point2);
                }else if(point2list->empty()){
                    countpoint2++;
                    point2list->append(point2);
                }
            }else{
                if(point1list->empty()&&point2list->empty()){
                    point1first = false;
                }
                countpoint2++;
                point2list->append(point2);
            }
            qDebug()<<"the"<<countpoint2<<"th point end at"<<point2;
            this->update();
        }
        int wid,hei;
        int x,y;
        wid = image->width();
        hei = image->height();
        x = this->geometry().left();
        y = this->geometry().top();
        this->setGeometry(x, y, wid, hei );
        if(!point1list->isEmpty()&&!point2list->isEmpty()){
            hideline = false;
        }
    }
    changable = true;
    //解除鼠标事件对于图像大小改变的保护
}

void WidgetWindow::paintEvent(QPaintEvent *){
    if(!image->isNull()){
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawImage(QPoint(0, 0), *image);

        if(!hidepoints){
            painter.setPen(QPen(Qt::red, 5));
            for(iter_1 = point1list->begin(); iter_1 != point1list->end(); iter_1++){
                painter.drawPoint(*iter_1);
            }
            painter.setPen(QPen(Qt::blue, 5));
            for(iter_2 = point2list->begin(); iter_2 != point2list->end(); iter_2++){

                painter.drawPoint(*iter_2);
            }
        }
        if(!hideline){
            painter.setPen(QPen(Qt::green,1));
            if(countpoint1==1){
                for(iter_2 = point2list->begin(); iter_2 != point2list->end(); iter_2++){
                    painter.drawLine(point1list->at(0), *iter_2);
                }
            }else if(countpoint2==1){
                for(iter_1 = point1list->begin(); iter_1 != point1list->end(); iter_1++){
                    painter.drawLine(point2list->at(0), *iter_1);
                }
            }

        }
        if(!initialise){//连接之后不显示两点间连线  显示最终路径和搜索点
//            if(point1list->size() > 1||point2list->size() > 1){

//            }
            for(tesiter = teslist->begin(); tesiter != teslist->end(); tesiter++){
                if(!tesiter->pointlist_->isEmpty()){
//                    qDebug()<<"size"<<tesiter->pointlist_->size();
                    tesiter->lock->lockForRead();
                    for(int i = 0; i < tesiter->pointlist_->size(); i++){
                        pi = tesiter->pointlist_->at(i);
                        painter.setPen(QPen(Qt::red, 3));
                        painter.drawPoint(pi.xy);
                        for(int j = i - 1; j >= 0; j--){
                            pj = tesiter->pointlist_->at(j);
                            if(pi.fatherpoint == pj.xy){
                                painter.setPen(QPen(Qt::red, 1));
                                painter.drawLine(pi.xy, pj.xy);
                                break;
                            }
                        }
                    }
                    tesiter->lock->unlock();
                }
            }
            painter.setPen(QPen(Qt::blue,2));
            for(tesiter = teslist->begin(); tesiter != teslist->end(); tesiter++){
                for(int i = 0; i < tesiter->pointreturn->size() - 1; i++){
                    painter.drawLine(tesiter->pointreturn->at(i), tesiter->pointreturn->at(i + 1));
                }
            }

        }
        //        }
        //        painter.drawImage(QPoint(0,0),*image);
        painter.end();
    }
}

void WidgetWindow::keyPressEvent(QKeyEvent *key){
    if(!isrunning){
        if(key->key()==Qt::Key_Return){
            connectpoint = ifconnect();
            if(connectpoint){
                changable = false;
                //如果两个点像素值相同表示连接状态，可以跑图
                //同时将图像大小锁死
                isrunning = true;
                teslist = tlist();

            }else if(!initialise){
                initialise = true;
                hideline = true;
                teslist->clear();
                point1list->clear();
                point2list->clear();
                countpoint1 = 0;
                countpoint2 = 0;
                this->update();
            }
        }else if((key->modifiers() == Qt::ControlModifier)
                   && (key->key() == Qt::Key_V)){
            clipboard = QApplication::clipboard();
            const QMimeData *mimeData = clipboard->mimeData();
            QString addresstring = mimeData->text();
            addresstring.remove("file:///");
            QByteArray array = addresstring.toUtf8();
            cv::Mat mat_1 = fill->cvInit(array);
            if(!mat_1.empty()){
                mat2 = mat_1;
                initialmat(mat2);
                append_1();
                if(!adresslist->contains(array)){
                    adresslist->append(array);
                }
            }
        }else if(key->key()==Qt::Key_Escape){
//            qDebug()<<"delete";
            if(point1list->empty()&&!point2list->empty()){
                point2list->pop_back();
                countpoint2--;
            }else if(point2list->empty()&&!point1list->empty()){
                point1list->pop_back();
                countpoint1--;
            }else if(countpoint1 > 1){
                point1list->pop_back();
                countpoint1--;
            }else if(countpoint2 > 1){
                point2list->pop_back();
                countpoint2--;
            }else if(countpoint2 == 1&&countpoint1 == 1){
                if(point1first){
                    point1list->pop_back();
                    countpoint1--;
                }else{
                    point2list->pop_back();
                    countpoint2--;
                }
            }
            this->update();
        }

        siz = adresslist->size();
        if(siz > 1){
            cv::Mat mat_1;
            QByteArray array1;
            if(key->key()==Qt::Key_Left){
                array1=adresslist->at(siz - 2);
                mat_1=fill->cvInit(array1);
                mat2=mat_1;
                initialmat(mat2);
                append_1();
                array1=adresslist->at(siz - 1);
                adresslist->pop_back();
                adresslist->prepend(array1);
                qDebug()<<"the front picture";
            }else if(key->key()==Qt::Key_Right){
                array1=adresslist->at(0);
                mat_1=fill->cvInit(array1);
                mat2=mat_1;
                initialmat(mat2);
                append_1();
                adresslist->pop_front();
                adresslist->append(array1);
                qDebug()<<"the rear picture";
            }
        }

    }
}

