#include "main_window.h"
#include "ui_main_window.h"
#include "instruction_window.h"
#include "about_window.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->menu = new QMenu("&Menu");
    QAction* helpAction = ui->menu->addAction("Help");
    connect(helpAction, SIGNAL(triggered()), this, SLOT(onHelpClicked()));
    QAction* aboutAction = ui->menu->addAction("About");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(onAboutClicked()));
    QAction* exitAction = ui->menu->addAction("Exit");
    connect(exitAction, SIGNAL(triggered()), this, SLOT(onExitClicked()));
    ui->menuBar->addMenu(ui->menu);
    ui->menuBar->show();
}

void MainWindow::onHelpClicked()
{
    InstructionWindow iw;
    iw.exec();
}

void MainWindow::onAboutClicked()
{
    AboutWindow aw;
    aw.exec();
}

void MainWindow::onExitClicked()
{
    QCoreApplication::quit();
}

MainWindow::~MainWindow()
{
    delete ui;
}
