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
    {
        d = new DayInfo(0,0,date);
    }
    d->setBaseBalance(calcBaseBalance(date));
    return *d;
}

void ConnectorData::setData(DayInfo dayInfo, QDate date)
{
    _instance->mapDayInfo.insert(date, dayInfo);
    refreshData();
    emit valueChanged();
}

double ConnectorData::calcBaseBalance(QDate date)
{
    QMap<QDate, DayInfo>::iterator it = mapDayInfo.begin();
    double baseBalance = 0;
    foreach(QDate d, mapDayInfo.keys())
    {
        if(it->getDate()<=d)
        {
            if(date>d)
            {
                    it = mapDayInfo.find(d);
                    baseBalance = it->getBalance();
            }
        }
    }
    return baseBalance;
}

void ConnectorData::refreshData()
{
    foreach(DayInfo d, mapDayInfo.values())
    {
        d.setBaseBalance(calcBaseBalance(d.getDate()));
        _instance->mapDayInfo.insert(d.getDate(),d);
    }
}
