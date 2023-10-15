#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    check=false;
    image=new QImage;
    fill=new Filter;
    clipboard=QApplication::clipboard();

    this->setFocusPolicy(Qt::StrongFocus);
    this->activateWindow();
    wid=this->frameGeometry().width();
    hei=this->frameGeometry().height();
    this->move(50,50);
    adresslist=new QVector<QByteArray>;
}

Widget::~Widget()
{
    delete ui;
    delete image;
    delete tes;
    delete fill;
    delete mat;
    delete adresslist;
}

void Widget::paintEvent(QPaintEvent *){
    if(!image->isNull()){
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawImage(QPoint(0,0),*image);

        if(!hidepoint1){

            painter.setPen(QPen(Qt::red,4));
            painter.drawPoint(point1);
        }
        if(!hidepoint2){
            painter.setPen(QPen(Qt::blue,4));
            painter.drawPoint(point2);
        }
        if(!hideline){
            painter.setPen(QPen(Qt::green,2));
            painter.drawLine(point1,point2);
        }
        if(!initialise){//连接之后不显示两点间连线  显示最终路径和搜索点
            int x,y1,y2,x1,x2;
            if(!qpointlist.isEmpty()&&point_count > 0){
                QPainterPath path(qpointlist.at(0));
                painter.setPen(QPen(Qt::blue,2));
//                int size_=qpointlist.size();
//                qDebug()<<"qpointlist.at(0) "<<qpointlist.at(0);
                for(int i = 0; i <= point_count; i++){
//                    painter.drawLine(qpointlist.at(i),
//                    qpointlist.at(i+1);
                    x1 = qpointlist.at(i).x();
                    x2 = qpointlist.at(i+1).x();
                    y1 = qpointlist.at(i).y();
                    y2 = qpointlist.at(i+1).y();
                    x = (x1 + x2) / 2;
                    path.cubicTo(QPointF(x, y1),
                                 QPointF(x, y2),
                                 qpointlist.at(i + 1));
                }

                painter.drawPath(path);
            }
            if(!qpointlist2.isEmpty()){
                painter.setPen(QPen(Qt::red,2));
                for(int i=0;i<point_count2;i++){
                    painter.drawPoint(qpointlist2.at(i));
                }
            }else qDebug()<<"qpointlist2 is empty"<<Qt::endl;
        }
//        }
//        painter.drawImage(QPoint(0,0),*image);
        painter.end();
    }
}

cv::Mat Widget::resize_(cv::Mat mat){
    wid=this->geometry().width();
    hei=this->geometry().height();
    cv::Mat mat_1;
    double com_=wid/hei;
    float heii,weii;

    if(com_>com){
        weii=hei*com;
        heii=hei;
    }else {
        heii=wid/com;
        weii=wid;
    }
    mat_1=fill->cvTranf(mat,cv::Size(weii,heii));
    return mat_1;
}

void Widget::resizeEvent(QResizeEvent *){

    if( changable){
        cv::Mat mat_11;

        mat_11=resize_(*mat);
        hidepoint1=true;
        hidepoint2=true;
        hideline=true;
        append_(mat_11);
    }

}

void Widget::focusInEvent(QFocusEvent *event)
{
    QWidget::focusInEvent(event);
}

void Widget::wheelEvent(QWheelEvent* event){
    wid=this->geometry().width();
    hei=this->geometry().height();
    if(changable){
        double rowschange=50 * com;
        if(event->angleDelta().y()>0)
            this->resize(QSize(wid + rowschange, hei + 50));
        else this->resize(QSize(wid - rowschange, hei - 50));
    }
}

void Widget::mousePressEvent(QMouseEvent *event){
    changable=false;
    //保护在鼠标点击事件过程中图像大小不会受到影响
    if(!image->isNull()&&!isrunning){
        this->setFocus(); //单单这句是无效的
        QWidget::mousePressEvent(event);
//        judgestring="clicked";
        if(event->button() == Qt::LeftButton)
        {
            check=!check;
            hidepoint1=false;
            if(check){
                point1=event->pos();
                qDebug()<<"point1 is"<<point1;
                this->update();
            }
            else{
                hidepoint2=false;
                hideline=false;
                point2=event->pos();
                qDebug()<<"point2 is"<<point2;
//                showpoint2=true;
                this->update();
            }
            if(!point1.isNull()&&!point2.isNull()){

                append(resize_((*mat)));

                if(image->pixel(point1)==image->pixel(point2)){
                    connectpoint=true;

                }else{
                    qDebug()<<"connect failed"<<Qt::endl;
                }
                append_(resize_(*mat));
            }

        }
        int wid,hei;
        int x,y;
        wid=image->width();
        hei=image->height();
        x=this->geometry().left();
        y=this->geometry().top();
        this->setGeometry(x,y,wid,hei+5);
    }
    changable=true;
    //解除鼠标事件对于图像大小改变的保护
}

void Widget::keyPressEvent(QKeyEvent *key){
    if(!isrunning){

        if(connectpoint){
            changable=false;
            //如果两个点像素值相同表示连接状态，可以通过回车跑图
            //同时将图像大小锁死
            if(key->key()==Qt::Key_Return){
                isrunning=true;
                append(resize_((*mat)));
                qDebug()<<"start running";
                Point point0;
                point0.xy=point1;
                qpointlist.clear();
                tes=new Tes2(point2,image);

                connection1=connect(tes,&Tes2::showpoint,
                    this,[&](QVector<QPoint> pointlist_2){
                        qpointlist2.clear();
                        qpointlist2=pointlist_2;
                        QPoint point_2;
                        point_count2=0;
                        for(int i=0;i<qpointlist2.size()-1;i++){
                            point_2=qpointlist2.at(i);
                            if(qpointlist.contains(point_2)){
                                point_count++;
                            }
                            time = QTime::currentTime().addMSecs(10);
                            while( QTime::currentTime() < time ){
                                QCoreApplication
                                    ::processEvents(QEventLoop::AllEvents, 10);
                            }
                            point_count2++;
                            this->update();
                        }
                    },Qt::QueuedConnection);

                qRegisterMetaType<Point>("Point");
                connection2=connect(tes,&Tes2::pushpoint,
                    this,[&](QVector<QPoint> pointlist){
                        qpointlist=pointlist;
//                        qpointlist.prepend(point1);
                        point_count=0;
                    },Qt::QueuedConnection);
                initialise=false;
                hideline=true;
                tes->timer->start();
                tes->Returnpoint(point0);
                tes->disconnect();
                isrunning=false;
                //断开与tes类的信号连接，直到下次连接
                append_(resize_(*mat));
                point1=QPoint(NULL,NULL);
                point2=QPoint(NULL,NULL);
            }
        }
        int size=adresslist->size();
        if(size>1){
            cv::Mat mat_1;
            QByteArray array1;
            if(key->key()==Qt::Key_Left){
                array1=adresslist->at(size-2);
                mat_1=fill->cvInit(array1);
                mat2=mat_1;
                initialmat(mat2);
                append_1();
                array1=adresslist->at(size-1);
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
        if((key->modifiers() == Qt::ControlModifier)
            && (key->key() == Qt::Key_V)){
            clipboard=QApplication::clipboard();
            const QMimeData *mimeData = clipboard->mimeData();
            QString addresstring=mimeData->text();
            addresstring.remove("file:///");
            QByteArray array=addresstring.toUtf8();
            cv::Mat mat_1=fill->cvInit(array);
            if(!mat_1.empty()){
                mat2=mat_1;
                initialmat(mat2);
                append_1();
                if(!adresslist->contains(array)){
                    adresslist->append(array);
                }
            }
        }
    }
}

void Widget::initialmat(cv::Mat mat1){
    mat=new cv::Mat;
    cv::Mat mat__=mat1;
    mat__=fill->transColor(mat__);
    mat__=fill->doublefilter(mat__);
    medianBlur(mat__,mat__,11);
    //    mat=fill->dog(mat,0,5);
    mat__=fill->lapulus(mat__,0);//壹阶拉普拉斯金字塔采样
    mat__=fill->threshold(mat__,77);//二值化
    int cols=mat__.cols;
    int rows=mat__.rows;
    int col1=0,row1=0,col2=0,row2=0;
    bool bk=true;
    //下面是对原图像进行剪裁，将多余的空白去除
    for(int i=0;i<cols-1;i++){
        for(int j=0;j<rows-1;j++){
            if(mat__.at<uchar>(j,i)==0){

                col1=i;
                bk=false;
                break;
            }
        }
        if(bk==false) break;
    }
    bk=true;
    for(int i=cols-1;i>1;i--){
        for(int j=rows-1;j>1;j--){
            if(mat__.at<uchar>(j,i)==0){

                col2=i;
                bk=false;
                break;
            }
        }
        if(bk==false) break;
    }
    bk=true;
    for(int i=0;i<rows-1;i++){
        for(int j=0;j<cols-1;j++){
            if(mat__.at<uchar>(i,j)==0){
                row1=i;
                bk=false;
                break;
            }
        }
        if(bk==false) break;
    }
    bk=true;
    for(int i=rows-1;i>1;i--){
        for(int j=cols-1;j>1;j--){
            if(mat__.at<uchar>(i,j)==0){
                row2=i;
                bk=false;
                break;
            }
        }
        if(bk==false) break;
    }
    int len1,len2;
    len1=col2-col1;
    len2=row2-row1;
    //cols=y,rows=x
    cv::Rect rect(col1,row1,len1,len2);
    *mat=mat1(rect);
}

//图像初始化
void Widget::append_1(){
    QPixmap pix;
    int wid,hei;

    com= double(mat->cols)/ double(mat->rows);
    pix=fill->qimage_(*mat);
    *image=pix.toImage();
    wid=image->width();
    hei=image->height();
    this->setGeometry(0,50,wid-5,hei-5);
    this->update();
    this->setGeometry(0,50,wid,hei);
    this->update();
    point1=QPoint(NULL,NULL);
    point2=QPoint(NULL,NULL);
    changable=true;
    initialise=true;
    hidepoint2=false;
    hidepoint1=false;
    hideline=true;
    connectpoint=false;
        //在下次两个点的像素值相同之前无法通过回车进行跑图
}

//显示原图
void Widget::append_(cv::Mat mat){
    QPixmap pix;
    pix=fill->qimage_(mat);
    *image=pix.toImage();
    this->update();
}

//显示处理过的图
void Widget::append(cv::Mat mat){
    cv::Mat mat_;
    QPixmap pix;
    mat=fill->transColor(mat);//图像灰度化
    mat=fill->doublefilter(mat);//双边滤波
    medianBlur(mat,mat,11);//中值滤波
//    mat=fill->dog(mat,0,5);
    mat=fill->lapulus(mat,0);//壹阶拉普拉斯金字塔采样
    mat=fill->threshold(mat,77);//二值化
    pix=fill->qimage(mat);//将cv::Mat转换为pixmap
    *image=pix.toImage();
    this->update();
};

