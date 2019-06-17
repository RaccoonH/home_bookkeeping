#include "main_window.h"

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

    _date = new QDate();
    *_date = QDate::currentDate();
    createCalendar();
    createMenu();
}

void MainWindow::createMenu()
{
    _menuBar = new QMenuBar(this);
    _menuBar->setObjectName(QString::fromUtf8("menuBar"));
    setMenuBar(_menuBar);
    _file = new QMenu("Файл");
    QAction* exitAction = _file->addAction("Выход");
    connect(exitAction, SIGNAL(triggered()), this, SLOT(onExitClicked()));
    _menu = new QMenu("Справка");
    QAction* helpAction = _menu->addAction("Инструкция");
    connect(helpAction, SIGNAL(triggered()), this, SLOT(onHelpClicked()));
    QAction* aboutAction = _menu->addAction("О программе");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(onAboutClicked()));
    _menuBar->addMenu(_file);
    _menuBar->addMenu(_menu);
    _menuBar->show();
}

void MainWindow::createCalendar()
{    
    _mainLayoutWidget = new QWidget(_centralWidget);
    _mainLayout = new QVBoxLayout(_mainLayoutWidget);

    QWidget *monthAndYearLayoutWidget = new QWidget(_centralWidget);
    QHBoxLayout *monthAndYearLayout = new QHBoxLayout(monthAndYearLayoutWidget);
    QPushButton *pastMonthButton = new QPushButton("<");
    pastMonthButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(pastMonthButton,SIGNAL(clicked()),this,SLOT(onPastMonthClicked()));
    QPushButton *nextMonthButton = new QPushButton(">");
    connect(nextMonthButton,SIGNAL(clicked()),this,SLOT(onNextMonthClicked()));
    nextMonthButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    QString stringMonthAndYear = _date->toString("MMM") + " " +  _date->toString("yyyy");
    QLabel *monthAndYear = new QLabel(stringMonthAndYear);
    monthAndYearLayout->addWidget(pastMonthButton);
    monthAndYearLayout->addWidget(monthAndYear);
    monthAndYearLayout->addWidget(nextMonthButton);
    monthAndYearLayoutWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    monthAndYear->setAlignment(Qt::AlignCenter);
    _mainLayout->addWidget(monthAndYearLayoutWidget);

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
    _mainLayout->addWidget(daysLayoutWidget);

    _calendarLayoutWidget = new QWidget(_centralWidget);
    _calendarLayout = new QGridLayout(_calendarLayoutWidget);
    _calendarLayoutWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    int week = 1;
    int day;
    *_date = _date->addDays(-(_date->day())+1);
    day = _date->dayOfWeek();
    for(int i = 1;i<=_date->daysInMonth();i++)
    {
        DayInfo *dayInfo = new DayInfo(i,i,i);
        createClickableLabel(dayInfo,day,week);
        day++;
        if(day==8)
        {
            day = 1;
            week++;
        }
    }
    _calendarLayout->setHorizontalSpacing(0);
    _calendarLayout->setVerticalSpacing(0);
    _mainLayout->addWidget(_calendarLayoutWidget);
    _centralWidget->setLayout(_mainLayout);
}

void MainWindow::createClickableLabel(DayInfo *dayInfo, int day, int week)
{
    ClickableLabel *label;
    QString *dayInfoText = new QString();
    *dayInfoText += QString::number(dayInfo->_numOfDay);
    *dayInfoText += "\nДоход = ";
    *dayInfoText += QString::number(dayInfo->_income);
    *dayInfoText += "\nРасход = ";
    *dayInfoText += QString::number(dayInfo->_outcome);
    *dayInfoText += "\nОстаток = ";
    *dayInfoText += QString::number(dayInfo->_balance);
    label = new ClickableLabel(*dayInfoText);
    label->setFrameShape(QFrame::Box);
    label->setLineWidth(1);
    label->setAlignment(Qt::AlignTop);
    _calendarLayout->addWidget(label,week,day);
    connect(label, SIGNAL(clicked()), dayInfo, SLOT(onDayInfoClicked()));
}

void MainWindow::onPastMonthClicked()
{
    _centralWidget = new QWidget(this);
    _centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    setCentralWidget(_centralWidget);
    *_date = _date->addMonths(-1);
    createCalendar();
}

void MainWindow::onNextMonthClicked()
{
    _centralWidget = new QWidget(this);
    _centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    setCentralWidget(_centralWidget);
    *_date = _date->addMonths(1);
    createCalendar();
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
