#ifndef CALENDAR_MENU_H
#define CALENDAR_MENU_H

#include <QWidget>
#include <QDate>
#include <QLayout>
#include <QPushButton>
#include "dayinfo_label.h"
#include "dayinfo_window.h"
#include "connector_data.h"

class CalendarMenu : public QWidget
{
    Q_OBJECT
public:
    explicit CalendarMenu(QWidget *parent = 0);
    ~CalendarMenu();

private:
    QWidget* createHeadline();
    QWidget* createDaysOfWeek();
    QWidget* createCalendar();

private:
    QVBoxLayout *_mainLayout;
    QDate _date;

private slots:
    void onCalendarRefreshed();
};

#endif // CALENDAR_MENU_H
