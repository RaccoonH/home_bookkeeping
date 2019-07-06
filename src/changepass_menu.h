#ifndef CHANGEPASS_MENU_H
#define CHANGEPASS_MENU_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class ChangePassMenu : public QWidget
{
    Q_OBJECT
public:
    explicit ChangePassMenu(QWidget *parent = nullptr);
    ~ChangePassMenu();

signals:
    void canceled();
    void applied();

public slots:
    void onCancelButtonClicked();
    void onApplyButtonClicked();
};

#endif // CHANGEPASS_MENU_H
