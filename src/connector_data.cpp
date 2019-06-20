#include "connector_data.h"
#include "dayinfo.h"
#include "QDebug"
#include "dayinfo_label.h"

ConnectorData::ConnectorData()
{

}

ConnectorData * ConnectorData::_instance = 0;

void ConnectorData::initialization(QDate date, QMainWindow *main)
{
    date = date.addDays(-(date.day())+1);
    int month = date.daysInMonth();
    _instance = new ConnectorData();
    for(int i = 1;i<=month;i++)
    {
        DayInfo *dayInfo = new DayInfo(i,i,date);
        _instance->mapDayInfo.insert(dayInfo->getDate(), dayInfo);
        date = date.addDays(1);
    }
    connect(_instance,SIGNAL(valueChanged()),main,SLOT(onValueChanged()));
}

DayInfo ConnectorData::getDayInfo(QDate date)
{
    DayInfo *d = _instance->mapDayInfo[date];
    return *d;
}

void ConnectorData::setData(DayInfo *dayInfo, QDate date)
{
    _instance->mapDayInfo.insert(date, dayInfo);
    _instance->sendSignal();
}

void ConnectorData::sendSignal()
{
    emit valueChanged();
}
