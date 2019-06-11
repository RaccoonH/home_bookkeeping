#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "instructionwindow.h"
#include "aboutwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonHelp_clicked()
{
    InstructionWindow iw;
    iw.exec();

}

void MainWindow::on_buttonAbout_clicked()
{
    AboutWindow aw;
    aw.exec();
}
