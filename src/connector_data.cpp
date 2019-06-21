#include "connector_data.h"
#include "dayinfo_label.h"

ConnectorData::ConnectorData()
{

}

ConnectorData * ConnectorData::_instance = nullptr;

ConnectorData *ConnectorData::instance()
{
    return  _instance;
}

void ConnectorData::init()
{
    _instance = new ConnectorData();
}



void ConnectorData::deinit()
{
    delete _instance;
}

DayInfo ConnectorData::getDayInfo(QDate date)
{
    QMap<QDate, DayInfo>::iterator it = mapDayInfo.find(date);
    DayInfo *d = new DayInfo(0,0,date);
    *d = it.value();
    if(it == mapDayInfo.end())
        d = new DayInfo(0,0,date);
    return *d;
}

void ConnectorData::setData(DayInfo dayInfo, QDate date)
{
    _instance->mapDayInfo.insert(date, dayInfo);
    emit valueChanged();
}
