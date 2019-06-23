#ifndef DAYINFO_H
#define DAYINFO_H

#include <QDate>

class DayInfo
{

public:
    DayInfo(double,double,QDate);
    DayInfo();
    void setIncome(double);
    void setOutcome(double);
    void calcBalance();
    void setBaseBalance(double);
    double getIncome();
    double getOutcome();
    double getBalance();
    double getBaseBalance();
    int getDay();
    int getMonth();
    int getYear();
    QDate getDate();

private:
    QDate _date;
    double _income;
    double _outcome;
    double _balance;
    double _baseBalance;
};

#endif // DAYINFO_H
