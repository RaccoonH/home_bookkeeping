#include "main_window.h"
#include "connector_data.h"
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
    if(_settings.allKeys().count()==0)
    {
        createRegisterMenu();
    }
    createLoginMenu();
    createMainMenu();
}

QMenu* MainWindow::createFileMenu()
{
    QMenu *file = new QMenu("Файл",this);
    QAction* exitAction = file->addAction("Выход");
    connect(exitAction, SIGNAL(triggered()), this, SLOT(onExitClicked()));
    return file;
}

QMenu* MainWindow::createHelpMenu()
{
    QMenu *menu = new QMenu("Справка",this);
    QAction* helpAction = menu->addAction("Инструкция");
    connect(helpAction, SIGNAL(triggered()), this, SLOT(onHelpClicked()));
    QAction* aboutAction = menu->addAction("О программе");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(onAboutClicked()));
    return menu;
}

QWidget* MainWindow::createHeadline()
{
    QWidget *monthAndYearLayoutWidget = new QWidget(_centralWidget);
    QHBoxLayout *monthAndYearLayout = new QHBoxLayout(monthAndYearLayoutWidget);

    QPushButton *pastMonthButton = new QPushButton("<");
    pastMonthButton->setObjectName("pastMonthButton");
    pastMonthButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(pastMonthButton,SIGNAL(clicked()),this,SLOT(onCalendarRefreshed()));

    QString stringMonthAndYear = _date.toString("MMM") + " " +  _date.toString("yyyy");
    QLabel *monthAndYear = new QLabel(stringMonthAndYear);
    monthAndYear->setAlignment(Qt::AlignCenter);

    QPushButton *nextMonthButton = new QPushButton(">");
    nextMonthButton->setObjectName("nextMonthButton");
    connect(nextMonthButton,SIGNAL(clicked()),this,SLOT(onCalendarRefreshed()));
    nextMonthButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    monthAndYearLayout->addWidget(pastMonthButton);
    monthAndYearLayout->addWidget(monthAndYear);
    monthAndYearLayout->addWidget(nextMonthButton);
    monthAndYearLayoutWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    return monthAndYearLayoutWidget;
}

QWidget* MainWindow::createDaysOfWeek()
{
    QWidget *daysLayoutWidget = new QWidget(_centralWidget);
    QHBoxLayout *daysLayout = new QHBoxLayout(daysLayoutWidget);
    QDate date(1,1,1);
    for(int i = 0;i<7;i++)
    {
        QLabel *nameOfDay = new QLabel;
        nameOfDay->setText(date.toString("ddd"));
        date = date.addDays(1);
        daysLayout->addWidget(nameOfDay);
    }
    daysLayoutWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    return daysLayoutWidget;
}

QWidget* MainWindow::createCalendar()
{
    QWidget *calendarLayoutWidget = new QWidget(_centralWidget);
    QGridLayout *calendarLayout = new QGridLayout(calendarLayoutWidget);
    calendarLayoutWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    int week = 1;
    int day;
    int month;

    _date = _date.addDays(1-(_date.day()));
    day = _date.dayOfWeek();
    month = _date.daysInMonth();
    for(int i = 1;i<=month;i++)
    {
        DayInfo dayInfo = ConnectorData::instance()->getDayInfo(_date);
        DayInfoLabel *dayInfoLabel = new DayInfoLabel(dayInfo,this);
        calendarLayout->addWidget(dayInfoLabel,week,day);
        _date = _date.addDays(1);
        day++;
        if(day==8)
        {
            day = 1;
            week++;
        }
    }
    _date = _date.addMonths(-1);
    calendarLayout->setHorizontalSpacing(2);
    calendarLayout->setVerticalSpacing(2);

    return calendarLayoutWidget;
}

void MainWindow::onCalendarRefreshed()
{
    if (QObject::sender()->objectName() == "pastMonthButton")
    {
        _date = _date.addMonths(-1);
    }
    if(QObject::sender()->objectName() == "nextMonthButton")
    {
        _date = _date.addMonths(1);
    }

//    delete _centralWidget;
//    _centralWidget = new QWidget(this);
//    setCentralWidget(_centralWidget);
//    _mainLayout = new QVBoxLayout();
//    _centralWidget->setLayout(_mainLayout);

    QLayoutItem *child;
    QLayoutItem *child2;
    int i = 0;
    while ((child = _mainLayout->takeAt(0)) != 0) {
        while((child2 = child->widget()->layout()->takeAt(0)) != 0)
        {
            delete child2->widget();
            delete child2;
            i++;
        }
        delete child->widget()->layout();
        delete child->widget();
    }

    auto headline = createHeadline();
    _mainLayout->addWidget(headline);

    auto daysOfWeekLabel = createDaysOfWeek();
    _mainLayout->addWidget(daysOfWeekLabel);

    auto calendar = createCalendar();
    _mainLayout->addWidget(calendar);
}

void MainWindow::createRegisterMenu()
{
    _registerMenuWidget = new QWidget(_stackWidget);
    _stackWidget->insertWidget(0,_registerMenuWidget);

    QHBoxLayout *registerHLayout = new QHBoxLayout(_registerMenuWidget);
    _registerMenuWidget->setLayout(registerHLayout);
    QWidget *registerVLayoutWidget = new QWidget(_registerMenuWidget);
    QVBoxLayout *registerVLayout = new QVBoxLayout(registerVLayoutWidget);

    QLabel *headline = new QLabel("Домашняя бухгалтерия" ,registerVLayoutWidget);
    QFont textFont;
    textFont.setPixelSize(30);
    headline->setFont(textFont);

    QLabel *pass;
    QPushButton *signButton;
    QLabel *errorLabelRegister = new QLabel("",this);
    errorLabelRegister->setObjectName("errorLabelRegister");

    pass = new QLabel("Введите пароль для регистрации", registerVLayoutWidget);
    QLineEdit *linePass = new QLineEdit(registerVLayoutWidget);
    linePass->setObjectName("linePassRegister");
    linePass->setEchoMode(QLineEdit::Password);
    signButton = new QPushButton("Зарегистрироваться");
    signButton->setObjectName("regist");

    connect(signButton, SIGNAL(clicked()), this, SLOT(onSignButtonClicked()));
    registerVLayout->addWidget(headline);
    registerVLayout->addWidget(pass);
    registerVLayout->addWidget(linePass);
    registerVLayout->addWidget(errorLabelRegister);
    registerVLayout->addWidget(signButton);
    registerVLayoutWidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    registerVLayout->setAlignment(Qt::AlignCenter);

    registerHLayout->addWidget(registerVLayoutWidget);
}

void MainWindow::createLoginMenu()
{
    _loginMenuWidget = new QWidget(_stackWidget);
    _stackWidget->insertWidget(1,_loginMenuWidget);

    QHBoxLayout *loginHLayout = new QHBoxLayout(_loginMenuWidget);
    _loginMenuWidget->setLayout(loginHLayout);
    QWidget *loginVLayoutWidget = new QWidget(_loginMenuWidget);
    QVBoxLayout *loginVLayout = new QVBoxLayout(loginVLayoutWidget);

    QLabel *headline = new QLabel("Домашняя бухгалтерия" ,_loginMenuWidget);
    QFont textFont;
    textFont.setPixelSize(30);
    headline->setFont(textFont);

    QLabel *pass;
    QLabel *errorLabel = new QLabel("",this);
    errorLabel->setObjectName("errorLabelLogin");
    QPushButton *signButton;
    QPushButton *changePassButton;

    pass = new QLabel("Введите пароль для входа", _loginMenuWidget);
    QLineEdit *linePass = new QLineEdit(_loginMenuWidget);
    linePass->setObjectName("linePassLogin");
    linePass->setEchoMode(QLineEdit::Password);
    signButton = new QPushButton("Войти");
    signButton->setObjectName("sign");
    changePassButton = new QPushButton("Сменить пароль");
    changePassButton->setObjectName("change");

    connect(signButton, SIGNAL(clicked()), this, SLOT(onSignButtonClicked()));
    loginVLayout->addWidget(headline);
    loginVLayout->addWidget(pass);
    loginVLayout->addWidget(linePass);
    loginVLayout->addWidget(errorLabel);
    loginVLayout->addWidget(signButton);
    loginVLayout->addWidget(changePassButton);
    loginVLayoutWidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    loginVLayout->setAlignment(Qt::AlignCenter);

    loginHLayout->addWidget(loginVLayoutWidget);
}

void MainWindow::onSignButtonClicked()
{
    QString pass;
    if(QObject::sender()->objectName() == "sign")
    {
        pass = _stackWidget->currentWidget()->findChild<QLineEdit*>("linePassLogin")->text();
        if(pass==_settings.value("password"))
        {
            _stackWidget->setCurrentIndex(3);
            _loginMenuWidget->~QWidget();
        }
        else
        {
            _stackWidget->currentWidget()->findChild<QLabel*>("errorLabelLogin")->setText("Неправильный пароль");
            qDebug() << _settings.fileName();
        }
    }
    else
    {
        pass = _stackWidget->currentWidget()->findChild<QLineEdit*>("linePassRegister")->text();
        if(pass.length()>3)
        {
            _settings.setValue("password", pass);
            _settings.sync();
            _stackWidget->setCurrentIndex(1);
        }
        else
        {
            _stackWidget->currentWidget()->findChild<QLabel*>("errorLabelRegister")->setText("Ваш пароль слишком короткий!");
        }
    }
}

void MainWindow::createMainMenu()
{

    QMenuBar *menuBar = new QMenuBar(this);
    auto *fileMenu = createFileMenu();
    auto *helpMenu = createHelpMenu();
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(helpMenu);
    setMenuBar(menuBar);

    _centralWidget = new QWidget(_stackWidget);
    _mainLayout = new QVBoxLayout(_centralWidget);
    _centralWidget->setLayout(_mainLayout);
    _stackWidget->insertWidget(3,_centralWidget);

    _date = QDate::currentDate();
    ConnectorData::init();
    connect(ConnectorData::instance(),SIGNAL(valueChanged()),this,SLOT(onCalendarRefreshed()));

    auto headline = createHeadline();
    _mainLayout->addWidget(headline);

    auto daysOfWeekLabel = createDaysOfWeek();
    _mainLayout->addWidget(daysOfWeekLabel);

    auto calendar = createCalendar();
    _mainLayout->addWidget(calendar);
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
