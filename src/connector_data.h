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
    static void setData(DayInfo*, QDate);
    static void initialization(QDate, QMainWindow*);
    static DayInfo getDayInfo(QDate);

private:
    ConnectorData();
    static ConnectorData *_instance;
    QMap<QDate, DayInfo*> mapDayInfo;
    void sendSignal();

signals:
    void valueChanged();

};
#endif // CONNECTOR_DATA_H
