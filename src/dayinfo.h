#ifndef DAYINFO_H
#define DAYINFO_H

#include <QDate>

class DayInfo
{

public:
    DayInfo(double,double,QDate);
    void setIncome(double);
    void setOutcome(double);
    double getIncome();
    double getOutcome();
    double getBalance();
    void calcBalance();
    int getDay();
    int getMonth();
    int getYear();
    QDate getDate();

private:
    QDate _date;
    double _income;
    double _outcome;
    double _balance;
};

#endif // DAYINFO_H
