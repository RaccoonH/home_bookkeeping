#include "about_window.h"
#include "ui_about_window.h"
#include "qlabel.h"
#include "qgridlayout.h"
#include "qpushbutton.h"
#include <QApplication>

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
}


AboutWindow::~AboutWindow()
{
    delete ui;
}
