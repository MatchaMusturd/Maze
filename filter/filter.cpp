#include "filter.h"

Filter::Filter()
{

}

cv::Mat Filter::transColor(cv::Mat mat){
    cv::Mat matReturn;
    cv::cvtColor(mat,matReturn,cv::COLOR_BGRA2GRAY,0);
    return matReturn;
}


cv::Mat Filter::doublefilter(cv::Mat mat1){
    cv::Mat mat2;
    bilateralFilter(mat1,mat2,30,255,0);
    return mat2;
}

//cv::Mat Filter::gauss(cv::Mat mat,int size){
//    cv::Mat mat3;
//    cv::GaussianBlur(mat,mat3,cv::Size(size,size),0,0);
//    return mat3;
//}

cv::Mat Filter::threshold(cv::Mat mat,int cubes){
    cv::Mat matReturn;
    cv::adaptiveThreshold(mat,matReturn,255,
                          cv::ADAPTIVE_THRESH_GAUSSIAN_C,
                          cv::THRESH_BINARY_INV,
                          cubes,0);
    return matReturn;

}

cv::Mat Filter::dog(const cv::Mat mat,int tm,int sz){
    cv::Mat mat_,mat_1,matReturn;
    QVector<cv::Mat> *matlist;
    matlist=new QVector<cv::Mat>;
    matlist->append(mat);
    for(int i=0;i<tm;i++){
        cv::GaussianBlur(matlist->at(i),
                         mat_,
                         cv::Size(sz,sz)
                         ,0,0);
        matlist->append(mat_);
    }
    cv::GaussianBlur(matlist->at(tm),
                     mat_1,
                     cv::Size(sz,sz)
                     ,0,0);
    cv::subtract(mat_1,matlist->at(tm),matReturn);
    delete matlist;
    return matReturn;
}

cv::Mat Filter::lapulus(const cv::Mat mat,int tm){
    cv::Mat matReturn,mat_,mat_1;
    mat_=mat;

    for(int i=0;i<tm;i++) cv::pyrDown(mat_,mat_);

    if(mat_.cols%2==1){
        cv::resize(mat_,mat_,cv::Size(mat_.cols+1,mat_.rows));
    }
    if(mat_.rows%2==1){
        cv::resize(mat_,mat_,cv::Size(mat_.cols,mat_.rows+1));
    }

    cv::pyrDown(mat_,matReturn);
    cv::pyrUp(matReturn,mat_1);
    cv::subtract(mat_,mat_1,matReturn);
    //mat_减mat_1结果赋值matReturn

    for(int i=0;i<tm;i++) matReturn=cvTranf_(matReturn,2);

    return matReturn;
}


cv::Mat Filter::cvTranf_(cv::Mat mat2,double pro){
    cv::Mat mat3;
    cv::resize(mat2,
               mat3,
               cv::Size(0,0),
               pro,
               pro,
               cv::INTER_CUBIC);
    return mat3;
}

cv::Mat Filter::cvTranf(cv::Mat mat2,cv::Size size){
    cv::Mat mat3;
    cv::resize(mat2,
               mat3,
               size,
               0,
               0,
               cv::INTER_CUBIC);
    return mat3;
}

QPixmap Filter::qimage_(cv::Mat mat){
    int channel=mat.channels();
    QPixmap map;
    if(channel==3){
        QImage image( mat.data,mat.cols, mat.rows,
                     static_cast<int>(mat.step),
                     QImage::Format_BGR888);
        map = QPixmap::fromImage(image);
    }else if(channel==4){

        QImage image( mat.data,mat.cols, mat.rows,
                     static_cast<int>(mat.step),
                     QImage::Format_ARGB32);
        map = QPixmap::fromImage(image);
    }

    return map;
}

QPixmap Filter::qimage(cv::Mat mat){

    QImage image( mat.data,mat.cols, mat.rows,
                 static_cast<int>(mat.step),
                 QImage::Format_Grayscale8 );

    QPixmap map = QPixmap::fromImage(image);
    return map;
}

cv::Mat Filter::cvInit(QByteArray array){
    cv::Mat mat2;
    char *adress=array.data();
    mat2=cv::imread(adress,-1);
    if(mat2.empty()){
        qDebug()<< "Error! Input image cannot be read...\n";
    }
    return mat2;
}
