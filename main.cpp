#include "widgetwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetWindow *ww;
    ww = new WidgetWindow;
    ww->show();

    return a.exec();
}
