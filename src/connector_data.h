#ifndef CONNECTOR_DATA_H
#define CONNECTOR_DATA_H

#include "main_window.h"
#include "dayinfo.h"
#include <QObject>
#include <QMap>
#include <QDate>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>

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
    void refreshData();
    void connectToDateBase();
    void disconnectFromDateBase();

private:
    static ConnectorData *_instance;
    QSqlDatabase _dateBase;

signals:
    void valueChanged();

};
#endif // CONNECTOR_DATA_H
