#ifndef CONNECTOR_DATA_H
#define CONNECTOR_DATA_H

#include "dayinfo.h"
#include <QObject>
#include <QMap>
#include <QDate>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

class ConnectorData : public QObject
{
    Q_OBJECT

public:
    static void init();
    static ConnectorData* instance();
    static void deinit();
    void setData(QDate, DayInfo);
    DayInfo getDayInfo(QDate);
    double calcBaseBalance(QDate);

private:
    ConnectorData();
    ~ConnectorData();
    void refreshData(QDate date);
    void connectToDateBase();
    void disconnectFromDateBase();

private:
    static ConnectorData *_instance;
    QSqlDatabase _dateBase;

signals:
    void valueChanged();

};
#endif // CONNECTOR_DATA_H
