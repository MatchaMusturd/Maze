#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    image=new QImage;
    fill=new Filter;
    timer = new QElapsedTimer ;
    point1list = new QVP;
    point2list = new QVP;
    isrunning = false;
    changable = false;
    connection1 = false;
    connection2 = false;
    teslist = new QVector<ExternalCall>;
    this->setFocusPolicy(Qt::StrongFocus);
    this->activateWindow();
    wid = this->frameGeometry().width();
    hei = this->frameGeometry().height();
    this->move(50, 50);

    ui->textBrowser->setFontPointSize(14);
    QString instructstring = "1 move the operation picture on the table\n"
                             "  Copy(Ctrl+C) and paste (Ctrl+V) the picture to the window show on the left top of the screen.\n"
                             "2 Scrole the mouse wheel to control the size of window and the picture\n"
                             "3 press the left and the right key to switch the pictures that has been saved\n"
                             "4 press the left mouse on the picture to set start points\n"
                             "  press the right mouse on the picture to set end points\n"
                             "  press Escape to delete points\n"
                             "5 Enter to run the picture to find the way from start points to end points";
    ui->textBrowser->setText(instructstring);
}

Widget::~Widget()
{
    delete ui;
    delete image;
    delete fill;
    delete mat;
    delete timer;
    delete point1list;
    delete point2list;
    delete teslist;
    delete teslist_;
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


void Widget::initial(){
    if(!connectpoint&&!initialise){
        initialise = true;
        hideline = true;
        teslist->clear();
        countpoint1 = 0;
        countpoint2 = 0;
        point1list->clear();
        point2list->clear();
        this->update();
    }else{
        hidepoints = false;
    }
}

bool Widget::ifconnect(){
    returncheck = true;
    //通过判断所有点是否都在路上来判断是否可以跑图
    append(resize_((*mat)));
    auto dividcolor = [&](QVP* l){
        pv = image->pixel(l->at(0));
        r = qRed(pv);
        g = qGreen(pv);
        b = qBlue(pv);
        if(r!=255||g!=255||b!=255)
            returncheck = false;
    };
    if(point1list->empty()||point2list->empty()){
        returncheck = false;
        return returncheck;
    }else if(countpoint1 == 1){
        dividcolor(point1list);
        if(!returncheck) return returncheck;
        for(i2 = point2list->begin(); i2!= point2list->end(); ){
            if(pv != image->pixel(*i2)){
                i2 = point2list->erase(i2);
            }else i2++;
        }
    }else if(countpoint2 == 1){
        dividcolor(point2list);
        if(!returncheck) return returncheck;
        for(i1 = point1list->begin(); i1!= point1list->end(); ){
            if(pv != image->pixel(*i1)){
                i1 = point1list->erase(i1);
            }else i1++;
        }
    }
    append_(resize_(*mat));
    if(point1list->empty()||point2list->empty()){
        returncheck = false;
    }
    return returncheck;
}

void Widget::signalthread(ExternalCall& t){
    //独立线程
    connect(&t, &Tes2::didntfindtheresult,
        this,[&](){
            qDebug()<<"didn't get the result";
//            Point point_0;
//            initialise = true;
//            t.lock->lockForWrite();
//            t.pointlist_->clear();
//            t.lock->unlock();
//            point_0.xy = t.point_2;
//            append(resize_((*mat)));
//            ExternalCall et(t.point_2, t.point_1, image);
//            append_(resize_(*mat));
//            tlist();
//            initialise = false;
//            isrunning = true;
//            timer->start();
//            qDebug()<<"run again from the ending point";

//            QtConcurrent::run([&](){
//                //异步执行
//                qDebug()<<"point_0.xy"<<point_0.xy;
//                et.Returnpoint(point_0);
//                isrunning = false;
//                connectpoint = false;
//            });
        },Qt::QueuedConnection);

    connection1 = connect(&t, &Tes2::showpoint,
        this, [&](){
            t.lock->lockForRead();
            Point currentpoint = t.pointlist_->back();
            t.lock->unlock();
            qDebug()<<"number"<<t.pointlist_->size()<<"point is"<<currentpoint.xy;
            this->update();

        },Qt::DirectConnection);

    connection2 = connect(&t, &Tes2::pushpoint,
        this, [&](){
            seconds = double(timer->elapsed()) / 1000;
            qDebug() << "The operation took" << seconds<< "seconds";
            size2 = t.pointlist_->size();
//            qDebug()<<"size_"<<t.pointlist_->size();
            size1 = t.pointreturn->size();
            qDebug()<<"steps count is "<<size1;
            ratio = size1 / size2;
            qDebug()<<"ratio is "<<ratio;
            this->update();
        },Qt::QueuedConnection);

    initialise = false;
    Point point0;
    point0.xy = t.point_1;
    timer->start();
    qDebug()<<"start running";
        //异步执行
    t.Returnpoint(point0);
    isrunning = false;
    connectpoint = false;
    t.disconnect();

}

QVector<ExternalCall>* Widget::tlist(){
    teslist_ = new QVector<ExternalCall>;
    append(resize_((*mat)));
    if(point1list->size() == 1&&point2list->size() == 1){
        et = new ExternalCall(point1list->at(0), point2list->at(0), image);
        teslist_->append(*et);
        signalthread(*et);
    }else if(point1list->size() == 1){
        p1 = point1list->at(0);
        for(i2 = point2list->begin(); i2 != point2list->end(); i2++){

            et = new ExternalCall(p1, *i2, image);
            teslist_->append(*et);
        }
    }else if(point2list->size() == 1){
        p2 = point2list->at(0);
        for(i1 = point1list->begin(); i1 != point1list->end(); i1++){
            et = new ExternalCall(*i1, p2, image);
//            qDebug()<<"append";
            teslist_->append(*et);
//            qDebug()<<"~append";
        }
    }
    append_(resize_(*mat));
    QtConcurrent::map(teslist_->begin(), teslist_->end(),
                      [&](ExternalCall& t){
                          signalthread(t);
                      });
    return teslist_;
}

void Widget::initialmat(cv::Mat mat1){
    //图像初始化  用于剪裁多余白边
    mat = new cv::Mat;
    cv::Mat mat__ = mat1;
    mat__ = fill->transColor(mat__);
    mat__ = fill->doublefilter(mat__);
    medianBlur(mat__, mat__, 11);
    //    mat=fill->dog(mat,0,5);
    mat__ = fill->lapulus(mat__, 0);//壹阶拉普拉斯金字塔采样
    mat__ = fill->threshold(mat__, 77);//二值化
    int cols = mat__.cols;
    int rows = mat__.rows;
    int col1 = 0, row1 = 0, col2 = 0, row2 = 0;
    bool bk = true;
    //下面是对原图像进行剪裁，将多余的空白去除
    for(int i = 0;i < cols - 1; i++){
        for(int j = 0;j < rows - 1; j++){
            if(mat__.at<uchar>(j, i) == 0){

                col1 = i;
                bk = false;
                break;
            }
        }
        if(bk == false) break;
    }
    bk = true;
    for(int i = cols - 1; i > 1; i--){
        for(int j = rows - 1; j > 1; j--){
            if(mat__.at<uchar>(j, i) == 0){

                col2 = i;
                bk = false;
                break;
            }
        }
        if(bk == false) break;
    }
    bk = true;
    for(int i = 0;i < rows - 1; i++){
        for(int j = 0; j < cols - 1; j++){
            if(mat__.at<uchar>(i, j) == 0){
                row1 = i;
                bk = false;
                break;
            }
        }
        if(bk == false) break;
    }
    bk = true;
    for(int i = rows - 1; i > 1; i--){
        for(int j = cols - 1; j > 1; j--){
            if(mat__.at<uchar>(i, j) == 0){
                row2 = i;
                bk = false;
                break;
            }
        }
        if(bk == false) break;
    }
    int len1, len2;
    len1 = col2 - col1;
    len2 = row2 - row1;
    //cols=y,rows=x
    cv::Rect rect(col1, row1, len1, len2);
    *mat = mat1(rect);
}

//图像初始化
void Widget::append_1(){
    QPixmap pix;
    int wid,hei;

    com = double(mat->cols) / double(mat->rows);
    pix = fill->qimage_(*mat);
    *image = pix.toImage();
    wid = image->width();
    hei = image->height();
    this->setGeometry(0, 50, wid - 5, hei - 5);
    this->update();
    this->setGeometry(0, 50, wid, hei);
    this->update();
    ui->textBrowser->hide();
    changable = true;
    initialise = true;
    hidepoints = false;
    hideline = true;
    connectpoint = false;
    teslist->clear();
    point1list->clear();
    point2list->clear();
    countpoint1 = 0;
    countpoint2 = 0;
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

