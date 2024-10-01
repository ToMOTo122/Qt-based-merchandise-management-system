#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 加载 QDarkStyleSheet 主题

    QFile file(":/themes/darkstyle2.qss");  // 使用资源路径
    if (file.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet);  // 应用样式表到整个应用程序
        file.close();
    }
    else
    {
        qDebug() << "Failed to open the stylesheet file.";  // 如果文件无法打开，输出错误信息
    }      

    MainWindow w;

    w.show();
    return a.exec();
}
