#include "about_window.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent)
{
    resize(400, 300);
    setWindowTitle(QApplication::translate("AboutWindow", "О программе", nullptr));
}


AboutWindow::~AboutWindow()
{
    this->close();
}
