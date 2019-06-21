#ifndef CONNECTOR_DATA_H
#define CONNECTOR_DATA_H

#include "dayinfo.h"
#include <QObject>
#include <QMap>
#include <QDate>
#include "main_window.h"

class ConnectorData : public QObject
{
    Q_OBJECT

public:
    static void init();
    static ConnectorData* instance();
    static void deinit();
    void setData(DayInfo, QDate);
    DayInfo getDayInfo(QDate);

private:
    ConnectorData();
    static ConnectorData *_instance;
    QMap<QDate, DayInfo> mapDayInfo;

signals:
    void valueChanged();

};
#endif // CONNECTOR_DATA_H
