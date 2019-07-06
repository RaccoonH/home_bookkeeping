#include "login_menu.h"

LoginMenu::LoginMenu(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *loginHLayout = new QHBoxLayout(this);
    setLayout(loginHLayout);
    QWidget *loginVLayoutWidget = new QWidget(this);
    QVBoxLayout *loginVLayout = new QVBoxLayout(loginVLayoutWidget);

    QLabel *headline = new QLabel("Домашняя бухгалтерия" ,loginVLayoutWidget);
    QFont textFont;
    textFont.setPixelSize(30);
    headline->setFont(textFont);

    QLabel *pass = new QLabel("Введите пароль для входа", loginVLayoutWidget);
    QLineEdit *linePass = new QLineEdit(loginVLayoutWidget);
    linePass->setObjectName("linePassLogin");
    linePass->setEchoMode(QLineEdit::Password);

    QLabel *errorLabel = new QLabel("",this);
    errorLabel->setObjectName("errorLabelLogin");
    QPalette textColor;
    textColor.setColor(QPalette::WindowText, Qt::red);
    errorLabel->setPalette(textColor);

    QPushButton *signButton;
    signButton = new QPushButton("Войти", loginVLayoutWidget);
    connect(signButton, SIGNAL(clicked()), this, SLOT(onLoginClicked()));

    loginVLayout->addWidget(headline);
    loginVLayout->addWidget(pass);
    loginVLayout->addWidget(linePass);
    loginVLayout->addWidget(errorLabel);
    loginVLayout->addWidget(signButton);
    loginVLayoutWidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    loginVLayout->setAlignment(Qt::AlignCenter);

    loginHLayout->addWidget(loginVLayoutWidget);
}

void LoginMenu::onLoginClicked()
{
    emit login();
}

LoginMenu::~LoginMenu()
{

}
