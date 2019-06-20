#include "dayinfo.h"

DayInfo::DayInfo(double in, double out, QDate date)
{
    _income = in;
    _outcome = out;
    _date = date;
    calcBalance();
}

void DayInfo::calcBalance()
{
    _balance = _income - _outcome;
}

void DayInfo::setIncome(double in)
{
    _income = in;
}

void DayInfo::setOutcome(double out)
{
    _outcome = out;
}

double DayInfo::getIncome()
{
    return _income;
}

double DayInfo::getOutcome()
{
    return  _outcome;
}

double DayInfo::getBalance()
{
    return _balance;
}

QDate DayInfo::getDate()
{
    return _date;
}

int DayInfo::getDay()
{
    return _date.day();
}

int DayInfo::getMonth()
{
    return _date.month();
}

int DayInfo::getYear()
{
    return _date.year();
}
