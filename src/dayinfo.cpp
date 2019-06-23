#include "dayinfo.h"

DayInfo::DayInfo()
{

}

DayInfo::DayInfo(double in, double out, QDate date)
{
    _income = in;
    _outcome = out;
    _date = date;
    _baseBalance = 0;
    calcBalance();
}

void DayInfo::calcBalance()
{
    _balance = 0;
    _balance += _baseBalance;
    _balance += _income;
    _balance -= _outcome;
}

void DayInfo::setIncome(double in)
{
    _income = in;
    calcBalance();
}

void DayInfo::setOutcome(double out)
{
    _outcome = out;
    calcBalance();
}

void DayInfo::setBaseBalance(double balance)
{
    _baseBalance = balance;
    calcBalance();
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

double DayInfo::getBaseBalance()
{
    return _baseBalance;
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
