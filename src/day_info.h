#ifndef DAY_INFO_H
#define DAY_INFO_H

#include <QWidget>
#include <dayinfo_window.h>
#include <QLabel>
#include <qlayout.h>
#include <QSpinBox>

class DayInfo : public QWidget
{
    Q_OBJECT

public:
    int _numOfDay;
    double _income;
    double _outcome;
    double _balance;
    explicit DayInfo(int, double, double, QWidget *parent = 0);
    ~DayInfo();

private slots:
    void onDayInfoClicked();

private:
    void calcBalance();
};

#endif // DAY_INFO_H
