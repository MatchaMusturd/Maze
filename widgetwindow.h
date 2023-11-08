#ifndef WIDGETWINDOW_H
#define WIDGETWINDOW_H

#include"widget.h"

class WidgetWindow : public Widget
{
public:
    WidgetWindow();
    ~WidgetWindow();
private:
    QClipboard *clipboard;
    cv::Mat mat2;
    int siz;
    QPoint point1, point2;
    QVector<ExternalCall>::iterator tesiter;
    QVector<QByteArray> *adresslist;
    Point pi, pj;

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void focusInEvent(QFocusEvent *);
    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent *);
    void wheelEvent(QWheelEvent*);

};

#endif // WIDGETWINDOW_H
