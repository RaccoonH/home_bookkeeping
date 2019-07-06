#include "registration_menu.h"

RegistrationMenu::RegistrationMenu(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *registerHLayout = new QHBoxLayout(this);
    setLayout(registerHLayout);
    QWidget *registerVLayoutWidget = new QWidget(this);
    QVBoxLayout *registerVLayout = new QVBoxLayout(registerVLayoutWidget);

    QLabel *headline = new QLabel("Домашняя бухгалтерия" ,registerVLayoutWidget);
    QFont textFont;
    textFont.setPixelSize(30);
    headline->setFont(textFont);

    QLabel *pass = new QLabel("Введите пароль для регистрации", registerVLayoutWidget);
    QLineEdit *linePass = new QLineEdit(registerVLayoutWidget);
    linePass->setObjectName("linePassRegister");
    linePass->setEchoMode(QLineEdit::Password);

    QLabel *errorLabelRegister = new QLabel("",this);
    errorLabelRegister->setObjectName("errorLabelRegister");
    QPalette textColor;
    textColor.setColor(QPalette::WindowText, Qt::red);
    errorLabelRegister->setPalette(textColor);

    QPushButton *signButton = new QPushButton("Зарегистрироваться", registerVLayoutWidget);
    connect(signButton, SIGNAL(clicked()), this, SLOT(onRegistClicked()));

    registerVLayout->addWidget(headline);
    registerVLayout->addWidget(pass);
    registerVLayout->addWidget(linePass);
    registerVLayout->addWidget(errorLabelRegister);
    registerVLayout->addWidget(signButton);
    registerVLayoutWidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    registerVLayout->setAlignment(Qt::AlignCenter);

    registerHLayout->addWidget(registerVLayoutWidget);
}

void RegistrationMenu::onRegistClicked()
{
    emit registration();
}

RegistrationMenu::~RegistrationMenu()
{

}
