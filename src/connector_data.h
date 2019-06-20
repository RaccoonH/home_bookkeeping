#ifndef CONNECTOR_DATA_H
#define CONNECTOR_DATA_H

#include "dayinfo.h"
#include <vector>

class ConnectorData
{
public:
    static void changeData(double,double, QDate);
    static void initialization(QDate*);
    static void addDayInfo(DayInfo*);
    static DayInfo* getDayInfo(int);

private:
    static ConnectorData *_instance;
    ConnectorData();
    //Пока что контейнер
    std::vector <DayInfo> *arrDayInfo;
};
#endif // CONNECTOR_DATA_H
