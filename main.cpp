#include "UI/mainwindow.h"
#include <QApplication>
/*!
 * Default QT Widget main function all the fun stuff is in the mainwindow class
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
