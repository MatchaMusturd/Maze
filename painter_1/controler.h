#ifndef CONTROLER_H
#define CONTROLER_H

#include <QWidget>
#include<QDebug>
#include <core.hpp>       // OpenCV 核心功能
#include <imgproc.hpp>    // OpenCV 图像处理模块
#include <highgui.hpp>
#include<QDir>
#include<QSpinBox>

//#include"widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Controler; }
QT_END_NAMESPACE


class Controler : public QWidget
{
    Q_OBJECT
public:

    explicit Controler(QWidget *parent = nullptr);
     ~Controler();
signals:
private:

//    Widget *w;
    Ui::Controler *ui;

    cv::Mat *mat,*mat2;
    cv::Mat mat_1;

    cv::Mat cvInit(QByteArray);//直接导入cv图像


    void (QSpinBox:: *spinBoxSignal)(int) = &QSpinBox::valueChanged;
    void (QDoubleSpinBox:: *spinBox_Signal)(double) = &QDoubleSpinBox::valueChanged;
};

#endif // CONTROLER_H
