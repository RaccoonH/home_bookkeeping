#include "calendar_menu.h"

CalendarMenu::CalendarMenu(QWidget *parent):
    QWidget(parent)
{
        _mainLayout = new QVBoxLayout(this);
        setLayout(_mainLayout);

        _date = QDate::currentDate();
        ConnectorData::init();
        connect(ConnectorData::instance(),SIGNAL(valueChanged()),this,SLOT(onCalendarRefreshed()));

        auto headline = createHeadline();
        _mainLayout->addWidget(headline);

        auto daysOfWeekLabel = createDaysOfWeek();
        _mainLayout->addWidget(daysOfWeekLabel);

        auto calendar = createCalendar();
        _mainLayout->addWidget(calendar);
}

QWidget* CalendarMenu::createHeadline()
{
    QWidget *monthAndYearLayoutWidget = new QWidget(this);
    QHBoxLayout *monthAndYearLayout = new QHBoxLayout(monthAndYearLayoutWidget);

    QPushButton *pastMonthButton = new QPushButton("<");
    pastMonthButton->setObjectName("pastMonthButton");
    pastMonthButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(pastMonthButton,SIGNAL(clicked()),this,SLOT(onCalendarRefreshed()));

    QString stringMonthAndYear = _date.toString("MMM") + " " +  _date.toString("yyyy");
    QLabel *monthAndYear = new QLabel(stringMonthAndYear);
    monthAndYear->setAlignment(Qt::AlignCenter);

    QPushButton *nextMonthButton = new QPushButton(">");
    nextMonthButton->setObjectName("nextMonthButton");
    connect(nextMonthButton,SIGNAL(clicked()),this,SLOT(onCalendarRefreshed()));
    nextMonthButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    monthAndYearLayout->addWidget(pastMonthButton);
    monthAndYearLayout->addWidget(monthAndYear);
    monthAndYearLayout->addWidget(nextMonthButton);
    monthAndYearLayoutWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    return monthAndYearLayoutWidget;
}

QWidget* CalendarMenu::createDaysOfWeek()
{
    QWidget *daysLayoutWidget = new QWidget(this);
    QHBoxLayout *daysLayout = new QHBoxLayout(daysLayoutWidget);
    QDate date(1,1,1);
    for(int i = 0;i<7;i++)
    {
        QLabel *nameOfDay = new QLabel;
        nameOfDay->setText(date.toString("ddd"));
        date = date.addDays(1);
        daysLayout->addWidget(nameOfDay);
    }
    daysLayoutWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    return daysLayoutWidget;
}

QWidget* CalendarMenu::createCalendar()
{
    QWidget *calendarLayoutWidget = new QWidget(this);
    QGridLayout *calendarLayout = new QGridLayout(calendarLayoutWidget);
    calendarLayoutWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    int week = 1;
    int day;
    int month;

    _date = _date.addDays(1-(_date.day()));
    day = _date.dayOfWeek();
    month = _date.daysInMonth();
    for(int i = 1;i<=month;i++)
    {
        DayInfo dayInfo = ConnectorData::instance()->getDayInfo(_date);
        DayInfoLabel *dayInfoLabel = new DayInfoLabel(dayInfo,this);
        calendarLayout->addWidget(dayInfoLabel,week,day);
        _date = _date.addDays(1);
        day++;
        if(day==8)
        {
            day = 1;
            week++;
        }
    }
    _date = _date.addMonths(-1);
    calendarLayout->setHorizontalSpacing(2);
    calendarLayout->setVerticalSpacing(2);

    return calendarLayoutWidget;
}

void CalendarMenu::onCalendarRefreshed()
{
    if (QObject::sender()->objectName() == "pastMonthButton")
    {
        _date = _date.addMonths(-1);
    }
    if(QObject::sender()->objectName() == "nextMonthButton")
    {
        _date = _date.addMonths(1);
    }

    QLayoutItem *child;
    QLayoutItem *child2;
    int i = 0;
    while ((child = _mainLayout->takeAt(0)) != 0) {
        while((child2 = child->widget()->layout()->takeAt(0)) != 0)
        {
            delete child2->widget();
            delete child2;
            i++;
        }
        delete child->widget()->layout();
        delete child->widget();
    }

    auto headline = createHeadline();
    _mainLayout->addWidget(headline);

    auto daysOfWeekLabel = createDaysOfWeek();
    _mainLayout->addWidget(daysOfWeekLabel);

    auto calendar = createCalendar();
    _mainLayout->addWidget(calendar);
}

CalendarMenu::~CalendarMenu()
{

}
