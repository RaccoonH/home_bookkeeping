#include "day_info.h"

DayInfo::DayInfo(int num, double in, double out, QWidget* parent)
    : QLabel(parent)
{
    _numOfDay = num;
    _income = in;
    _outcome = out;
    calcBalance();
}

DayInfo::~DayInfo()
{
}

void DayInfo::createLabelWidget()
{
    QString *dayInfoText = new QString();
    *dayInfoText += QString::number(_numOfDay);
    *dayInfoText += "\nДоход = ";
    *dayInfoText += QString::number(_income);
    *dayInfoText += "\nРасход = ";
    *dayInfoText += QString::number(_outcome);
    *dayInfoText += "\nОстаток = ";
    *dayInfoText += QString::number(_balance);
    setText(*dayInfoText);
    setFrameShape(QFrame::Box);
    setLineWidth(1);
    setAlignment(Qt::AlignTop);
    connect(this, SIGNAL(clicked()), this, SLOT(onDayInfoClicked()));
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

void DayInfo::calcBalance()
{
    _balance = _income - _outcome;
}

void DayInfo::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}

void DayInfo::setNumOfDay(int day)
{
    _numOfDay = day;
}

void DayInfo::setIncome(double in)
{
    _income = in;
}

void DayInfo::setOutcome(double out)
{
    _outcome = out;
}

double DayInfo::getIncome()
{
    return _income;
}

double DayInfo::getOutcome()
{
    return  _outcome;
}
