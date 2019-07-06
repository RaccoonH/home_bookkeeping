#include "main_window.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent)
{
    resize(1000, 700);
    setMinimumSize(QSize(800, 600));
    setLayoutDirection(Qt::LeftToRight);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);

    _stackWidget = new QStackedWidget(this);
    setCentralWidget(_stackWidget);

    if(!_settings.contains("password"))
    {
        _regMenu = new RegistrationMenu(this);
        _stackWidget->addWidget(_regMenu);
        connect(_regMenu, SIGNAL(registration()), this, SLOT(onRegistButtonClicked()));
    }
    _loginMenu = new LoginMenu(this);
    _stackWidget->addWidget(_loginMenu);
    connect(_loginMenu, SIGNAL(login()), this, SLOT(onSignButtonClicked()));

    _calendarMenu = new CalendarMenu(this);
    _stackWidget->addWidget(_calendarMenu);

    createMenuBar();
    _menuBar->hide();
}

QMenu* MainWindow::createFileMenu()
{
    QMenu *file = new QMenu("Файл",this);
    QAction *changePass = file->addAction("Сменить пароль");
    connect(changePass, SIGNAL(triggered()), this, SLOT(onChangePassClicked()));

    QAction *exitAction = file->addAction("Выход");
    connect(exitAction, SIGNAL(triggered()), this, SLOT(onExitClicked()));

    return file;
}

QMenu* MainWindow::createHelpMenu()
{
    QMenu *menu = new QMenu("Справка",this);
    QAction *helpAction = menu->addAction("Инструкция");
    connect(helpAction, SIGNAL(triggered()), this, SLOT(onHelpClicked()));
    QAction *aboutAction = menu->addAction("О программе");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(onAboutClicked()));
    return menu;
}

void MainWindow::onChangePassClicked()
{
    _passMenu = new ChangePassMenu(this);
    _stackWidget->addWidget(_passMenu);
    _stackWidget->setCurrentWidget(_passMenu);
    connect(_passMenu,SIGNAL(canceled()),this,SLOT(onButtonChangeCanceled()));
    connect(_passMenu,SIGNAL(applied()),this,SLOT(onButtonChangeApplied()));
    _menuBar->hide();
}

void MainWindow::onButtonChangeCanceled()
{
    _stackWidget->setCurrentWidget(_calendarMenu);
    _menuBar->show();
}

void MainWindow::onButtonChangeApplied()
{
    QString oldPass;
    oldPass = _stackWidget->currentWidget()->findChild<QLineEdit*>("oldLinePass")->text();
    QString newPass;
    newPass = _stackWidget->currentWidget()->findChild<QLineEdit*>("newLinePass")->text();
    if(oldPass==_settings.value("password"))
    {
        if(newPass.length()>3)
        {
            _settings.setValue("password", newPass);
            _settings.sync();
            _stackWidget->setCurrentWidget(_loginMenu);
        }
        else
        {
            _stackWidget->currentWidget()->findChild<QLabel*>("errorLabelChangePass")->setText("Ваш новый пароль слишком короткий!");
        }
    }
    else
    {
        _stackWidget->currentWidget()->findChild<QLabel*>("errorLabelChangePass")->setText("Неверный старый пароль!");
    }
}

void MainWindow::onSignButtonClicked()
{
    QString pass;
    pass = _stackWidget->currentWidget()->findChild<QLineEdit*>("linePassLogin")->text();
    _stackWidget->currentWidget()->findChild<QLineEdit*>("linePassLogin")->setText("");
    if(pass==_settings.value("password"))
    {
        _stackWidget->currentWidget()->findChild<QLabel*>("errorLabelLogin")->setText("");
        _stackWidget->setCurrentWidget(_calendarMenu);
        _menuBar->show();
    }
    else
    {
        _stackWidget->currentWidget()->findChild<QLabel*>("errorLabelLogin")->setText("Неправильный пароль!");
    }

}

void MainWindow::onRegistButtonClicked()
{
    QString pass;
    pass = _stackWidget->currentWidget()->findChild<QLineEdit*>("linePassRegister")->text();
    if(pass.length()>3)
    {
        _settings.setValue("password", pass);
        _settings.sync();
        _stackWidget->setCurrentWidget(_loginMenu);
    }
    else
    {
        _stackWidget->currentWidget()->findChild<QLabel*>("errorLabelRegister")->setText("Ваш пароль слишком короткий!");
    }
}

void MainWindow::createMenuBar()
{
    _menuBar = new QMenuBar(this);
    auto *fileMenu = createFileMenu();
    auto *helpMenu = createHelpMenu();
    _menuBar->addMenu(fileMenu);
    _menuBar->addMenu(helpMenu);
    setMenuBar(_menuBar);
}

void MainWindow::onHelpClicked()
{
    InstructionWindow iw;
    iw.exec();
}

void MainWindow::onAboutClicked()
{
    AboutWindow aw;
    aw.exec();
}

void MainWindow::onExitClicked()
{
    QCoreApplication::quit();
}

MainWindow::~MainWindow()
{
    ConnectorData::deinit();
    this->destroy();
}
