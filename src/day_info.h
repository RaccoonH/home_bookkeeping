#ifndef DAY_INFO_H
#define DAY_INFO_H

#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include "qlayout.h"
#include "dayinfo_window.h"

class DayInfo : public QLabel
{
    Q_OBJECT

public:
    explicit DayInfo(int, double, double, QWidget *parent = 0);
    ~DayInfo();

    void setNumOfDay(int);
    void setIncome(double);
    void setOutcome(double);
    double getIncome();
    double getOutcome();
    void createLabelWidget();

private:
    int _numOfDay;
    double _income;
    double _outcome;
    double _balance;

private:
    void calcBalance();

signals:
    void clicked();

private slots:
    void onDayInfoClicked();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // DAY_INFO_H
