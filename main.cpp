#include "widget.h"

#include <QApplication>
#include <QFile>

class CommonHelper
{
public:
    static void setStyle(const QString &style)
    {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 加载QSS样式
    //CommonHelper::setStyle("style.qss");
    Widget w;
    w.show();
    return a.exec();
}
