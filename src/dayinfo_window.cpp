#include "dayinfo_window.h"
#include "qapplication.h"
#include <QLayout>
#include <QPushButton>
#include "connector_data.h"
#include <qdebug.h>

DayInfoWindow::DayInfoWindow(DayInfo d, QWidget *parent) :
    QDialog(parent)
{
    resize(400, 300);
    setWindowTitle(QApplication::translate("DayInfoWindow", "Edit", nullptr));

    _dayInfo = d;
    _date = _dayInfo.getDate();

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);

    QGridLayout *layout = new QGridLayout(this);
    QLabel *day = new QLabel(QString::number(_dayInfo.getDay()));
    day->setAlignment(Qt::AlignTop);
    day->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    QLabel *income = new QLabel("Доход",this);
    _incomeBox = new QDoubleSpinBox;
    _incomeBox->setRange(0,10000000);
    _incomeBox->setValue(_dayInfo.getIncome());
    connect(_incomeBox, SIGNAL(valueChanged(double)),this,SLOT(onValueChanged(double)));

    QLabel *outcome = new QLabel("Расход",this);
    _outcomeBox = new QDoubleSpinBox;
    _outcomeBox->setRange(0,10000000);
    _outcomeBox->setValue(_dayInfo.getOutcome());
    connect(_outcomeBox, SIGNAL(valueChanged(double)),this,SLOT(onValueChanged(double)));

    QLabel *balance = new QLabel("Остаток",this);
    _balanceBox = new QDoubleSpinBox;
    _balanceBox->setRange(-10000000,10000000);
    _balanceBox->setValue(_dayInfo.getBalance());
    _balanceBox->setDisabled(true);

    QPushButton *cancel = new QPushButton("Отмена",this);
    connect(cancel, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
    QPushButton *apply = new QPushButton("Принять",this);
    connect(apply, SIGNAL(clicked()), this, SLOT(onApplyClicked()));

    layout->addWidget(day,0,0);
    layout->addWidget(income,1,0);
    layout->addWidget(_incomeBox,1,1);
    layout->addWidget(outcome,2,0);
    layout->addWidget(_outcomeBox,2,1);
    layout->addWidget(balance,3,0);
    layout->addWidget(_balanceBox,3,1);
    layout->addWidget(apply,4,0);
    layout->addWidget(cancel,4,1);

    setLayout(layout);
    exec();
}

DayInfoWindow::~DayInfoWindow()
{
    this->close();
}

void DayInfoWindow::onValueChanged(double value)
{
    double balance = 0;
    balance += _dayInfo.getBaseBalance();
    balance += _incomeBox->value();
    balance -= _outcomeBox->value();
    _balanceBox->setValue(balance);
}

void DayInfoWindow::onCancelClicked()
{
    this->close();
}

void DayInfoWindow::onApplyClicked()
{
    _dayInfo.setIncome(_incomeBox->value());
    _dayInfo.setOutcome(_outcomeBox->value());
    ConnectorData::instance()->setData(_date, _dayInfo);
    this->close();
}
