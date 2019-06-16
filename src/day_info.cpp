#include "day_info.h"

DayInfo::DayInfo(int num, double in, double out, QWidget* parent)
    : QWidget(parent)
{
    _numOfDay = num;
    _income = in;
    _outcome = out;
    calcBalance();
}

DayInfo::~DayInfo()
{
}

void DayInfo::calcBalance()
{
    _balance = _income - _outcome;
}

void DayInfo::onDayInfoClicked()
{
    DayInfoWindow dw;
    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::white);
    dw.setAutoFillBackground(true);
    dw.setPalette(pal);

    QGridLayout *layout = new QGridLayout;
    QLabel *day = new QLabel(QString::number(_numOfDay));
    day->setAlignment(Qt::AlignTop);
    day->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    QLabel *income = new QLabel("Доход");
    QDoubleSpinBox *incomeBox = new QDoubleSpinBox;
    incomeBox->setRange(0,10000000);
    incomeBox->setValue(_income);
    QLabel *outcome = new QLabel("Расход");
    QDoubleSpinBox *outcomeBox = new QDoubleSpinBox;
    outcomeBox->setRange(0,10000000);
    outcomeBox->setValue(_outcome);
    QLabel *balance = new QLabel("Остаток");
    QDoubleSpinBox *balanceBox = new QDoubleSpinBox;
    balanceBox->setRange(0,10000000);
    balanceBox->setValue(_balance);
    layout->addWidget(day,0,0);
    layout->addWidget(income,1,0);
    layout->addWidget(incomeBox,1,1);
    layout->addWidget(outcome,2,0);
    layout->addWidget(outcomeBox,2,1);
    layout->addWidget(balance,3,0);
    layout->addWidget(balanceBox,3,1);
    dw.setLayout(layout);
    dw.exec();
}
