#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDate>
#include "dayinfo_label.h"
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
    void onCalendarRefreshed();

private:
    QMenu* createFileMenu();
    QMenu* createHelpMenu();
    QWidget* createHeadline();
    QWidget* createDaysOfWeek();
    QWidget* createCalendar();

private:
    QWidget *_centralWidget;
    QVBoxLayout *_mainLayout;
    QDate *_date;
};

#endif // MAINWINDOW_H
