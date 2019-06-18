#include "dayinfo_window.h"
#include "qapplication.h"

DayInfoWindow::DayInfoWindow(QWidget *parent) :
    QDialog(parent)
{
    resize(400, 300);
    setWindowTitle(QApplication::translate("DayInfoWindow", "Edit", nullptr));
}

DayInfoWindow::~DayInfoWindow()
{
    this->close();
}
