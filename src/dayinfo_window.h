#ifndef DAYINFO_WINDOW_H
#define DAYINFO_WINDOW_H

#include <QDialog>
#include <QDoubleSpinBox>
#include "dayinfo.h"

class DayInfoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DayInfoWindow(DayInfo ,QWidget *parent = 0);
    ~DayInfoWindow();

private slots:
    void onValueChanged(double);
    void onCancelClicked();
    void onApplyClicked();

private:
    QDoubleSpinBox *_balanceBox;
    QDoubleSpinBox *_incomeBox;
    QDoubleSpinBox *_outcomeBox;
    DayInfo _dayInfo;
    QDate _date;

};

#endif // DAYINFO_WINDOW_H
