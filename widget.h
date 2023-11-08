#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPainter>
#include<QMouseEvent>
#include<QWheelEvent>
#include<QTime>
#include <QClipboard>
#include <QApplication>
#include<QMimeData>
#include <QPainterPath>
#include<QtConcurrent>
#include<QFuture>
#include<QElapsedTimer>

#include"filter.h"
#include "externalcall.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

#define QVP QVector<QPoint>

class Widget : public QWidget
{
    Q_OBJECT
private:

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QElapsedTimer *timer;
    Ui::Widget *ui;
    QVector<ExternalCall>* teslist_;
    QRgb pv;
    bool returncheck;
    QVP::iterator i1,i2;
    int r, g, b, l1, l2;
    QPoint p1, p2;
    ExternalCall* et;
    double size1, size2, ratio, seconds;

protected:
    QVector<ExternalCall>* teslist;
    double com;
    float wid,hei;
    cv::Mat *mat;
    Filter *fill;
    QImage *image;
    int countpoint1, countpoint2;
    QVP::iterator iter_1, iter_2, iter_;
    QVP *point1list, *point2list;
    bool initialise, changable, hidepoints, isrunning,
        connectpoint, connection1, connection2, hideline, point1first;


    bool ifconnect();
    void initial();
    void signalthread(ExternalCall&);
    QVector<ExternalCall>* tlist();
    void initialmat(cv::Mat);//对*mat初始化
    void append(cv::Mat);//显示二值化的图
    void append_(cv::Mat);//显示原图
    void append_1();
    cv::Mat resize_(cv::Mat);

};
#endif // WIDGET_H
