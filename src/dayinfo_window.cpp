#include "dayinfo_window.h"
#include "qapplication.h"

DayInfoWindow::DayInfoWindow(QWidget *parent) :
    QDialog(parent)
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("DayInfoWindow"));
    resize(400, 300);
    setWindowTitle(QApplication::translate("DayInfoWindow", "Edit", nullptr));
}

DayInfoWindow::~DayInfoWindow()
{
    this->close();
}
