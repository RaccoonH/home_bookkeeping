#ifndef CONNECTOR_DATA_H
#define CONNECTOR_DATA_H

#include <QObject>
#include <QMap>
#include <QDate>
#include "main_window.h"
#include "dayinfo.h"

class ConnectorData : public QObject
{
    Q_OBJECT

public:
    static void init();
    static ConnectorData* instance();
    static void deinit();
    void setData(DayInfo, QDate);
    DayInfo getDayInfo(QDate);
    double calcBaseBalance(QDate);

private:
    ConnectorData();
    void refreshData();

private:
    static ConnectorData *_instance;
    QMap<QDate, DayInfo> mapDayInfo;

signals:
    void valueChanged();

};
#endif // CONNECTOR_DATA_H
