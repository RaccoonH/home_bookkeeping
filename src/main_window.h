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
#include "instruction_window.h"
#include "about_window.h"
#include "registration_menu.h"
#include "login_menu.h"
#include "calendar_menu.h"


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
    void onSignButtonClicked();
    void onRegistButtonClicked();

private:
    void createRegisterMenu();
    void createLoginMenu();
    void createMenuBar();
    QMenu* createFileMenu();
    QMenu* createHelpMenu();

private:
    CalendarMenu *_calendarMenu;
    QMenuBar *_menuBar;
    QStackedWidget *_stackWidget;    
    RegistrationMenu *_regMenu;
    LoginMenu *_loginMenu;
    QSettings _settings;

};

#endif // MAINWINDOW_H
