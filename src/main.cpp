#include "main_window.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("MySoft");
    QCoreApplication::setApplicationName("Home Bookkeeping");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
