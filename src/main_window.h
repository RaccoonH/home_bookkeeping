#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDate>
#include <QLineEdit>
#include <QCryptographicHash>
#include <QSettings>
#include <QStackedWidget>
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
    void onSignButtonClicked();

private:
    void createRegisterMenu();
    void createLoginMenu();
    void createMainMenu();
    QMenu* createFileMenu();
    QMenu* createHelpMenu();
    QWidget* createHeadline();
    QWidget* createDaysOfWeek();
    QWidget* createCalendar();

private:
    QStackedWidget *_stackWidget;
    QWidget *_centralWidget;
    QVBoxLayout *_mainLayout;
    QWidget *_loginMenuWidget;
    QWidget *_registerMenuWidget;
    QSettings _settings;
    QDate _date;
};

#endif // MAINWINDOW_H
