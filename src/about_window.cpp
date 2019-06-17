#include "about_window.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent)
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("AboutWindow"));
    resize(400, 300);
    setWindowTitle(QApplication::translate("AboutWindow", "О программе", nullptr));
}


AboutWindow::~AboutWindow()
{
    this->close();
}
