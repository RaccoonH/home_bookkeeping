#include "main_window.h"
#include "instruction_window.h"
#include "about_window.h"
#include "qdebug.h"
#include "clickable_label.h"
#include "dayinfo_window.h"

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

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);

    createCalendar();
    createMenu();
}

void MainWindow::createMenu()
{
    _menuBar = new QMenuBar(this);
    _menuBar->setObjectName(QString::fromUtf8("menuBar"));
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

void MainWindow::createCalendar()
{    
    _mainLayoutWidget = new QWidget(_centralWidget);
    _mainLayout = new QVBoxLayout(_mainLayoutWidget);
    QLabel *monthAndYear = new QLabel("Test label, здесь будет отображаться месяц и год");
    monthAndYear->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    _mainLayout->addWidget(monthAndYear);

    QWidget *daysLayoutWidget = new QWidget(_centralWidget);
    QHBoxLayout *daysLayout = new QHBoxLayout(daysLayoutWidget);
    QLabel *monday = new QLabel("Понедельник");
    QLabel *tuesday = new QLabel("Вторник");
    QLabel *wednesday = new QLabel("Среда");
    QLabel *thursday = new QLabel("Четверг");
    QLabel *friday = new QLabel("Пятница");
    QLabel *saturday = new QLabel("Суббота");
    QLabel *sunday = new QLabel("Воскресенье");
    daysLayout->addWidget(monday);
    daysLayout->addWidget(tuesday);
    daysLayout->addWidget(wednesday);
    daysLayout->addWidget(thursday);
    daysLayout->addWidget(friday);
    daysLayout->addWidget(saturday);
    daysLayout->addWidget(sunday);
    daysLayoutWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    _mainLayout->addWidget(daysLayoutWidget);

    _calendarLayoutWidget = new QWidget(_centralWidget);
    _calendarLayout = new QGridLayout(_calendarLayoutWidget);
    _calendarLayoutWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    int week = 0;
    int day = 0;
    for(int i = 1;i<=30;i++)
    {
        ClickableLabel *l = new ClickableLabel(QString::number(i));
        _calendarLayout->addWidget(l, week, day);
        l->setFrameShape(QFrame::Box);
        l->setLineWidth(1);
        l->setAlignment(Qt::AlignTop);
        connect(l, SIGNAL(clicked()), this, SLOT(onDayInfoClicked()));
        day++;
        if(day==7)
        {
            day = 0;
            week++;
        }
    }
    _calendarLayout->setHorizontalSpacing(0);
    _calendarLayout->setVerticalSpacing(0);
    _mainLayout->addWidget(_calendarLayoutWidget);
    _centralWidget->setLayout(_mainLayout);
}

void MainWindow::onDayInfoClicked()
{
    DayInfoWindow dw;
    dw.exec();
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
