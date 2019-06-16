#include "calendar_info.h"

CalendarInfo::CalendarInfo()
{
    QString m;
    std::string mm;
    m = QDateTime::currentDateTime().toString("MM");
    mm = m.toUtf8().constData();
    _intMonth = std::stoi(mm);
    _year = QDateTime::currentDateTime().toString("yyyy");
    mm = _year.toUtf8().constData();
    _intYear = std::stoi(mm);

    switch (_intMonth)
    {
    case 1:
        _month = "Январь";
        _countOfDays = 31;
        break;
    case 2:
        _month = "Февраль";
        _countOfDays = 28;
        break;
    case 3:
        _month = "Март";
        _countOfDays = 31;
        break;
    case 4:
        _month = "Апрель";
        _countOfDays = 30;
        break;
    case 5:
        _month = "Май";
        _countOfDays = 31;
        break;
    case 6:
        _month = "Июнь";
        _countOfDays = 30;
        break;
    case 7:
        _month = "Июль";
        _countOfDays = 31;
        break;
    case 8:
        _month = "Август";
        _countOfDays = 31;
        break;
    case 9:
        _month = "Сентябрь";
        _countOfDays = 30;
        break;
    case 10:
        _month = "Октябрь";
        _countOfDays = 31;
        break;
    case 11:
        _month = "Ноябрь";
        _countOfDays = 30;
        break;
    case 12:
        _month = "Декабрь";
        _countOfDays = 31;
        break;
    }


}
