#include "dayinfo_label.h"
#include "dayinfo_window.h"

DayInfoLabel::DayInfoLabel(DayInfo d, QWidget* parent)
    : QLabel(parent)
{

    QString dayInfoText;
    dayInfo = d;
    dayInfoText += QString::number(dayInfo.getDay());
    dayInfoText += "\nДоход = ";
    dayInfoText += QString::number(dayInfo.getIncome());
    dayInfoText += "\nРасход = ";
    dayInfoText += QString::number(dayInfo.getOutcome());
    dayInfoText += "\nОстаток = ";
    dayInfoText += QString::number(dayInfo.getBalance());
    setText(dayInfoText);

    QFont textFont;
    textFont.setPixelSize(15);
    setFont(textFont);

    if(dayInfo.getIncome()>dayInfo.getOutcome())
    {
        QPalette pall;
        pall.setColor(QPalette::Window,Qt::green);
        setPalette(pall);
        setAutoFillBackground(true);
    }
    if(dayInfo.getOutcome()>dayInfo.getIncome())
    {
        QPalette pall;
        pall.setColor(QPalette::Window,Qt::red);
        setPalette(pall);
        setAutoFillBackground(true);
    }

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
    DayInfoWindow dw(dayInfo);
}

void DayInfoLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}
