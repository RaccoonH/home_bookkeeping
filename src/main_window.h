#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDate>
#include "clickable_label.h"
#include "day_info.h"
#include "dayinfo_window.h"
#include "instruction_window.h"
#include "about_window.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onHelpClicked();
    void onAboutClicked();
    void onExitClicked();
    void onNextMonthClicked();
    void onPastMonthClicked();

private:
    QWidget *_centralWidget;
    QMenuBar *_menuBar;
    QMenu *_menu;
    QMenu *_file;
    QGridLayout *_calendarLayout;
    QWidget *_calendarLayoutWidget;
    QVBoxLayout *_mainLayout;
    QWidget *_mainLayoutWidget;
    QDate *_date;

    void createMenu();
    void createCalendar();
    void createClickableLabel(DayInfo*, int, int);
};

#endif // MAINWINDOW_H
