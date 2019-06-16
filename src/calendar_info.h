#ifndef CALENDAR_INFO_H
#define CALENDAR_INFO_H

#include <QDateTime>

class CalendarInfo
{
public:
    QString _month;
    QString _year;
    int _intMonth;
    int _intYear;
    int _countOfDays;
    CalendarInfo();
};

#endif // CALENDAR_INFO_H
