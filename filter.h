#ifndef FILTER_H
#define FILTER_H

#include "qpixmap.h"
#include <core.hpp>       // OpenCV 核心功能
#include <imgproc.hpp>    // OpenCV 图像处理模块
#include <highgui.hpp>
#include<QDebug>

class Filter
{
public:
    Filter();

    cv::Mat cvTranf_(cv::Mat,double);//将图片缩小
    cv::Mat cvTranf(cv::Mat,cv::Size);//将图片缩小
    cv::Mat threshold(cv::Mat,int);//二值化
    cv::Mat lapulus(const cv::Mat,int);//拉普拉斯采样
    cv::Mat dog(const cv::Mat,int,int);//高斯不同采样
//    cv::Mat gauss(cv::Mat,int);//高斯滤波
    QPixmap qimage(cv::Mat);//转为灰度图
    QPixmap qimage_(cv::Mat);//转为彩图
    cv::Mat transColor(cv::Mat);//图片灰度化
    cv::Mat doublefilter(cv::Mat);//双边滤波
    cv::Mat cvInit(QByteArray);//直接导入cv图像
    //    point getpoint(point);//输入一个点，每次调用得到下一个点
};

#endif // FILTER_H
