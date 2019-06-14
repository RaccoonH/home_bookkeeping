#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>


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

private:
    QWidget *_centralWidget;
    QMenuBar *_menuBar;
    QMenu *_menu;
    QGridLayout *_calendarLayout;
    QWidget *_calendarLayoutWidget;
    QVBoxLayout *_mainLayout;
    QWidget *_mainLayoutWidget;

    void createMenu();
    void createCalendar();
};

#endif // MAINWINDOW_H
