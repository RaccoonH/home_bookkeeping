#include "main_window.h"
#include "instruction_window.h"
#include "about_window.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent)
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("MainWindow"));
    resize(900, 600);
    setMinimumSize(QSize(600, 400));
    setLayoutDirection(Qt::LeftToRight);
    _centralWidget = new QWidget(this);
    _centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    setCentralWidget(_centralWidget);

    createMenu();
}

void MainWindow::createMenu()
{
    _menuBar = new QMenuBar(this);
    _menuBar->setObjectName(QString::fromUtf8("menuBar"));
    _menuBar->setGeometry(QRect(0, 0, 916, 25));
    this->setMenuBar(_menuBar);
    this->_menu = new QMenu("&Menu");
    QAction* helpAction = this->_menu->addAction("Help");
    connect(helpAction, SIGNAL(triggered()), this, SLOT(onHelpClicked()));
    QAction* aboutAction = this->_menu->addAction("About");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(onAboutClicked()));
    QAction* exitAction = this->_menu->addAction("Exit");
    connect(exitAction, SIGNAL(triggered()), this, SLOT(onExitClicked()));
    this->_menuBar->addMenu(this->_menu);
    this->_menuBar->show();
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
    this->destroy();
}
