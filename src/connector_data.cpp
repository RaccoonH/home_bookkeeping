#include "connector_data.h"
#include "dayinfo.h"
#include "QDate"
#include "QVector"
#include "QDebug"
#include "dayinfo_label.h"

ConnectorData::ConnectorData()
{

}

ConnectorData * ConnectorData::_instance = 0;

//тут должна быть работа с БД, но пока что контейнер arrDayInfo
void ConnectorData::initialization(QDate* d)
{
    QDate *date = new QDate;
    date->setDate(d->year(),d->month(),d->day());
    date->addDays(-(date->day())+1);
    _instance = new ConnectorData();
    _instance->arrDayInfo = new std::vector<DayInfo>;
    for(int i = 1;i<=date->daysInMonth();i++)
    {
        DayInfo *dayInfo = new DayInfo(i,i,*date);
        _instance->arrDayInfo->push_back(*dayInfo);
        *date = date->addDays(1);
    }
}

DayInfo* ConnectorData::getDayInfo(int index)
{
    auto j = _instance->arrDayInfo->begin();
    for(int i=1;i<=index;i++)
    {
        ++j;
    }

    return &*j;
}

void ConnectorData::changeData(double in, double out, QDate date)
{
    for(auto it = _instance->arrDayInfo->begin(), end = _instance->arrDayInfo->end(); it != end; ++it)
    {
        if(date==it->getDate())
        {
            it->setIncome(in);
            it->setOutcome(out);
            it->calcBalance();
            break;
        }
    }
}
