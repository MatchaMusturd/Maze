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

#include"filter.h"
#include"tes2.h"
#include"point.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
private:

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:

    QClipboard *clipboard;
    QTime time;
    int windowwid,windowhei;
    cv::Mat *mat,mat2,mat3;
    float wid,hei;
    double com;
    bool initialise=false,
        changable=false,
        hidepoint1=false,
        hidepoint2=false,
        isrunning=false,
        connectpoint=false,
        connection1=false,
        connection2=false,
        hideline=true;
    QVector<QByteArray> *adresslist;
    Tes2 *tes;
    QImage *image;
    bool check;
    Ui::Widget *ui;
    QPoint point1=QPoint(NULL,NULL),
        point2=QPoint(NULL,NULL);
    int point_count;
    int point_count2;
    QRect rect1,rect2;
    Point point0;
    QVector<QPoint> qpointlist,qpointlist2;
    Filter *fill;

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void focusInEvent(QFocusEvent *);
    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent *);
    void wheelEvent(QWheelEvent*);

    void initialmat(cv::Mat);//对*mat初始化
    void append(cv::Mat);//显示二值化的图
    void append_(cv::Mat);//显示原图
    void append_1();
    cv::Mat resize_(cv::Mat);
};
#endif // WIDGET_H
