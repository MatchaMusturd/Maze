#include "controler.h"
#include "ui_controler.h"

Controler::Controler(QWidget *parent)
    : QWidget{parent}
    , ui(new Ui::Controler)
{

    ui->setupUi(this);
    mat=new cv::Mat;
    mat2=new cv::Mat;
    w=new Widget;
    w->show();

    ui->lineEdit->setText("C:/Users/CHH/Desktop/OIP-C (2).jpg");

//    ui->horizontalSlider->setRange(3,67);
//    ui->horizontalSlider->setTickInterval(2);
//    ui->horizontalSlider->setTickPosition(QSlider::TicksAbove);
//    ui->spinBox->setRange(3,67);
//    ui->spinBox->setSingleStep(2);


//    ui->doubleSpinBox_2->setRange(0.4,3);
//    ui->doubleSpinBox_2->setSingleStep(0.1);
//    ui->horizontalSlider_2->setRange(40,300);
//    ui->horizontalSlider_2->setSingleStep(1);
//    ui->horizontalSlider_2->setTickInterval(10);
//    ui->horizontalSlider_2->setTickPosition(QSlider::TicksAbove);


//    w->i->b=ui->horizontalSlider->value();
//    w->i->c=ui->horizontalSlider->value();

//    connect(ui->spinBox,
//            spinBoxSignal,
//            ui->horizontalSlider,
//            &QSlider::setValue);

//    connect(w,&Widget::keyPressEvent,this)

//    connect(ui->doubleSpinBox_2,
//            spinBox_Signal,this,
//            [=](){
//                double arg1=ui->doubleSpinBox_2->value();
//                ui->horizontalSlider_2->setValue(arg1*100);
//            });

//    connect(ui->horizontalSlider,
//            &QSlider::valueChanged,this,
//            [=](){
//                int value=ui->horizontalSlider->value();
//                ui->spinBox->setValue(value);
//                w->i->b=value;
//                w->i->c=value;
//                if(!w->i->mat.empty()) w->append(w->i);
//            });

//    connect(ui->horizontalSlider,
//            &QSlider::sliderMoved,this,
//            [=](){
//                int position=ui->horizontalSlider->sliderPosition();
//                if(position%2==0){
//                    ui->horizontalSlider->setSliderPosition(position+1);
//                }
//            });

//    connect(ui->horizontalSlider_2,
//            &QSlider::valueChanged,this,
//            [=](){

//                float value=ui->horizontalSlider_2->value();
//                float ft=value/100;
//                ui->doubleSpinBox_2->setValue(ft);
//                if(!mat_1.empty()){
//                    mat_1=w->cvTranf(*mat,ft);
////                    *mat_=i->mat;
//                    w->append_(mat_1);
//                }
//            });

    connect(ui->lineEdit,
            &QLineEdit::returnPressed,this,
            [=](){
                QString string;
                QByteArray array;
                string=ui->lineEdit->text();
                string= QDir::fromNativeSeparators(string);
                string.remove('"');
                ui->lineEdit->clear();
                ui->label_4->setText(string);
                array=string.toUtf8();
                mat_1=cvInit(array);
                if(!mat_1.empty()){
                    *mat2=mat_1;//留作彩图
                    *mat=mat_1;//留作放缩的图
//                    mat_1=transColor(mat_1);
                    w->append_1(*mat2);
                }
            });

}

Controler::~Controler()
{
    delete ui;
    delete mat;
    delete w;
}



cv::Mat Controler::cvInit(QByteArray array){
    cv::Mat mat2;
    char *adress=array.data();
    mat2=cv::imread(adress,-1);
    if(mat2.empty()){
        qDebug()<< "Error! Input image cannot be read...\n";
    }
    return mat2;
}





