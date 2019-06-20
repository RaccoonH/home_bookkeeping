#ifndef DAY_INFO_H
#define DAY_INFO_H

#include <QLabel>
#include "dayinfo.h"

class DayInfoLabel : public QLabel
{
    Q_OBJECT

public:
    explicit DayInfoLabel(DayInfo ,QWidget *parent = 0);
    ~DayInfoLabel();
    void createLabelWidget();

signals:
    void clicked();

private:
    DayInfo *dayInfo;

private slots:
    void onDayInfoLabelClicked();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // DAY_INFO_H
