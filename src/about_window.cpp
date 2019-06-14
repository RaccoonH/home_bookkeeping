#include "about_window.h"
#include <QApplication>

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent)
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("AboutWindow"));
    resize(400, 300);
    setWindowTitle(QApplication::translate("AboutWindow", "About", nullptr));
}


AboutWindow::~AboutWindow()
{
    this->close();
}
