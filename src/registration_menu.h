#ifndef REGISTRATION_MENU_H
#define REGISTRATION_MENU_H

#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>

class RegistrationMenu : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationMenu(QWidget *parent = 0);
    ~RegistrationMenu();

signals:
    void registration();

private slots:
    void onRegistClicked();
};

#endif // REGISTRATION_MENU_H
