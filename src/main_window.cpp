#include "main_window.h"
#include "connector_data.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent)
{
    resize(900, 600);
    setMinimumSize(QSize(600, 400));
    setLayoutDirection(Qt::LeftToRight);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);

    QMenuBar *menuBar = new QMenuBar(this);
    auto *fileMenu = createFileMenu();
    auto *helpMenu = createHelpMenu();
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(helpMenu);
    setMenuBar(menuBar);

    _centralWidget = new QWidget(this);
    setCentralWidget(_centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    _centralWidget->setLayout(mainLayout);

    _date = new QDate();
    *_date = QDate::currentDate();
    ConnectorData::init();
    connect(ConnectorData::instance(),SIGNAL(valueChanged()),this,SLOT(onValueChanged()));

    auto headline = createHeadline();
    mainLayout->addWidget(headline);

    auto daysOfWeekLabel = createDaysOfWeek();
    mainLayout->addWidget(daysOfWeekLabel);

    auto calendar = createCalendar();
    mainLayout->addWidget(calendar);
}

QMenu* MainWindow::createFileMenu()
{
    QMenu *file = new QMenu("Файл");
    QAction* exitAction = file->addAction("Выход");
    connect(exitAction, SIGNAL(triggered()), this, SLOT(onExitClicked()));
    return file;
}

QMenu* MainWindow::createHelpMenu()
{
    QMenu *menu = new QMenu("Справка");
    QAction* helpAction = menu->addAction("Инструкция");
    connect(helpAction, SIGNAL(triggered()), this, SLOT(onHelpClicked()));
    QAction* aboutAction = menu->addAction("О программе");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(onAboutClicked()));
    return menu;
}

QWidget* MainWindow::createHeadline()
{
    QWidget *monthAndYearLayoutWidget = new QWidget(_centralWidget);
    QHBoxLayout *monthAndYearLayout = new QHBoxLayout(monthAndYearLayoutWidget);

    QPushButton *pastMonthButton = new QPushButton("<");
    pastMonthButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(pastMonthButton,SIGNAL(clicked()),this,SLOT(onPastMonthClicked()));

    QString stringMonthAndYear = _date->toString("MMM") + " " +  _date->toString("yyyy");
    QLabel *monthAndYear = new QLabel(stringMonthAndYear);
    monthAndYear->setAlignment(Qt::AlignCenter);

    QPushButton *nextMonthButton = new QPushButton(">");
    connect(nextMonthButton,SIGNAL(clicked()),this,SLOT(onNextMonthClicked()));
    nextMonthButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    monthAndYearLayout->addWidget(pastMonthButton);
    monthAndYearLayout->addWidget(monthAndYear);
    monthAndYearLayout->addWidget(nextMonthButton);
    monthAndYearLayoutWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    return monthAndYearLayoutWidget;
}

QWidget* MainWindow::createDaysOfWeek()
{
    QWidget *daysLayoutWidget = new QWidget(_centralWidget);
    QHBoxLayout *daysLayout = new QHBoxLayout(daysLayoutWidget);
    QDate *date = new QDate(1,1,1);
    for(int i = 0;i<7;i++)
    {
        QLabel *nameOfDay = new QLabel;
        nameOfDay->setText(date->toString("ddd"));
        *date = date->addDays(1);
        daysLayout->addWidget(nameOfDay);
    }
    daysLayoutWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    return daysLayoutWidget;
}

QWidget* MainWindow::createCalendar()
{
    QWidget *calendarLayoutWidget = new QWidget(_centralWidget);
    QGridLayout *calendarLayout = new QGridLayout(calendarLayoutWidget);
    calendarLayoutWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    int week = 1;
    int day;
    int month;

    *_date = _date->addDays(1-(_date->day()));
    day = _date->dayOfWeek();
    month = _date->daysInMonth();
    for(int i = 1;i<=month;i++)
    {
        DayInfo dayInfo = ConnectorData::instance()->getDayInfo(*_date);
        DayInfoLabel *dayInfoLabel = new DayInfoLabel(dayInfo,this);
        calendarLayout->addWidget(dayInfoLabel,week,day);
        *_date = _date->addDays(1);
        day++;
        if(day==8)
        {
            day = 1;
            week++;
        }
    }
    *_date = _date->addMonths(-1);
    calendarLayout->setHorizontalSpacing(2);
    calendarLayout->setVerticalSpacing(2);

    return calendarLayoutWidget;
}

void MainWindow::onPastMonthClicked()
{
    _centralWidget = new QWidget(this);
    setCentralWidget(_centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    _centralWidget->setLayout(mainLayout);
    *_date = _date->addMonths(-1);

    auto headline = createHeadline();
    mainLayout->addWidget(headline);

    auto daysOfWeekLabel = createDaysOfWeek();
    mainLayout->addWidget(daysOfWeekLabel);

    auto calendar = createCalendar();
    mainLayout->addWidget(calendar);
}

void MainWindow::onNextMonthClicked()
{
    _centralWidget = new QWidget(this);
    setCentralWidget(_centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    _centralWidget->setLayout(mainLayout);
    *_date = _date->addMonths(1);

    auto headline = createHeadline();
    mainLayout->addWidget(headline);

    auto daysOfWeekLabel = createDaysOfWeek();
    mainLayout->addWidget(daysOfWeekLabel);

    auto calendar = createCalendar();
    mainLayout->addWidget(calendar);
}

void MainWindow::onValueChanged()
{
    _centralWidget = new QWidget(this);
    setCentralWidget(_centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    _centralWidget->setLayout(mainLayout);

    auto headline = createHeadline();
    mainLayout->addWidget(headline);

    auto daysOfWeekLabel = createDaysOfWeek();
    mainLayout->addWidget(daysOfWeekLabel);

    auto calendar = createCalendar();
    mainLayout->addWidget(calendar);
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
