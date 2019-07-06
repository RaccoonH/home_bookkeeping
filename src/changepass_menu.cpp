#include "changepass_menu.h"

ChangePassMenu::ChangePassMenu(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *passHLayout = new QHBoxLayout(this);
    setLayout(passHLayout);
    QWidget *passVLayoutWidget = new QWidget(this);
    QVBoxLayout *passVLayout = new QVBoxLayout(passVLayoutWidget);

    QLabel *headline = new QLabel("Смена пароля" ,passVLayoutWidget);
    QFont textFont;
    textFont.setPixelSize(30);
    headline->setFont(textFont);

    QLabel *oldPass = new QLabel("Введите старый пароль", passVLayoutWidget);
    QLineEdit *oldLinePass = new QLineEdit(passVLayoutWidget);
    oldLinePass->setObjectName("oldLinePass");
    oldLinePass->setEchoMode(QLineEdit::Password);

    QLabel *newPass = new QLabel("Введите новый пароль", passVLayoutWidget);
    QLineEdit *newLinePass = new QLineEdit(passVLayoutWidget);
    newLinePass->setObjectName("newLinePass");
    newLinePass->setEchoMode(QLineEdit::Password);

    QLabel *errorLabel = new QLabel("",this);
    errorLabel->setObjectName("errorLabelChangePass");
    QPalette textColor;
    textColor.setColor(QPalette::WindowText, Qt::red);
    errorLabel->setPalette(textColor);

    QWidget *buttonsWidget = new QWidget(passVLayoutWidget);
    QHBoxLayout *buttonsLayout = new QHBoxLayout(buttonsWidget);

    QPushButton *applyButton = new QPushButton("Принять", buttonsWidget);
    buttonsLayout->addWidget(applyButton);
    connect(applyButton, SIGNAL(clicked()), this, SLOT(onApplyButtonClicked()));

    QPushButton *cancelButton = new QPushButton("Отмена", buttonsWidget);
    buttonsLayout->addWidget(cancelButton);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));

    passVLayout->addWidget(headline);
    passVLayout->addWidget(oldPass);
    passVLayout->addWidget(oldLinePass);
    passVLayout->addWidget(newPass);
    passVLayout->addWidget(newLinePass);
    passVLayout->addWidget(errorLabel);
    passVLayout->addWidget(buttonsWidget);
    passVLayoutWidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    passVLayout->setAlignment(Qt::AlignCenter);

    passHLayout->addWidget(passVLayoutWidget);
}

void ChangePassMenu::onCancelButtonClicked()
{
    emit canceled();
}

void ChangePassMenu::onApplyButtonClicked()
{
    emit applied();
}

ChangePassMenu::~ChangePassMenu()
{

}
