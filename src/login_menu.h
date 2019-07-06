#ifndef LOGIN_MENU_H
#define LOGIN_MENU_H

#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>

class LoginMenu : public QWidget
{
    Q_OBJECT

public:
    explicit LoginMenu(QWidget *parent = 0);
    ~LoginMenu();

signals:
    void login();

private slots:
    void onLoginClicked();
};

#endif // LOGIN_MENU_H
