#include "dayinfo_label.h"
#include "dayinfo_window.h"

DayInfoLabel::DayInfoLabel(DayInfo d, QWidget* parent)
    : QLabel(parent)
{
    QString *dayInfoText = new QString();
    dayInfo = new DayInfo();
    *dayInfo = d;
    *dayInfoText += QString::number(dayInfo->getDay());
    *dayInfoText += "\nДоход = ";
    *dayInfoText += QString::number(dayInfo->getIncome());
    *dayInfoText += "\nРасход = ";
    *dayInfoText += QString::number(dayInfo->getOutcome());
    *dayInfoText += "\nОстаток = ";
    *dayInfoText += QString::number(dayInfo->getBalance());
    setText(*dayInfoText);
    setFrameShape(QFrame::Box);
    setLineWidth(1);
    setAlignment(Qt::AlignTop);
    connect(this, SIGNAL(clicked()), this, SLOT(onDayInfoLabelClicked()));
}

DayInfoLabel::~DayInfoLabel()
{
}

void DayInfoLabel::onDayInfoLabelClicked()
{

    DayInfoWindow dw(*dayInfo,this);
}

void DayInfoLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}
