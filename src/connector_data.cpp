#include "connector_data.h"
#include "dayinfo_label.h"

ConnectorData::ConnectorData()
{
    connectToDataBase();
}

ConnectorData::~ConnectorData()
{
    disconnectFromDataBase();
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
    _instance->~ConnectorData();
}

DayInfo ConnectorData::getDayInfo(QDate date)
{
    QSqlQuery query;
    query.prepare("SELECT income, outcome FROM DayInfo_Table WHERE date=:date");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.exec();
    double in = 0;
    double out = 0;
    if(query.next())
    {
        in = query.value(0).toDouble();
        out = query.value(1).toDouble();
    }
    DayInfo d(in,out,date);
    d.setBaseBalance(calcBaseBalance(date));

    return d;
}

void ConnectorData::setData(QDate date, DayInfo dayInfo)
{
    QSqlQuery query;
    query.prepare("REPLACE INTO DayInfo_Table (date, baseBalance, income, outcome) VALUES (:date, :base, :in, :out)");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.bindValue(":base", dayInfo.getBaseBalance());
    query.bindValue(":in", dayInfo.getIncome());
    query.bindValue(":out", dayInfo.getOutcome());
    query.exec();
    refreshData(date);
    emit valueChanged();
}

double ConnectorData::calcBaseBalance(QDate date)
{
    QSqlQuery query;
    double baseBalance = 0;
    query.prepare("SELECT baseBalance, income, outcome FROM DayInfo_Table  WHERE date < :dateString ORDER BY date DESC");
    query.bindValue(":dateString", date.toString("yyyy-MM-dd"));
    query.exec();
    if(query.next())
    {
        baseBalance += query.value(0).toDouble();
        baseBalance += query.value(1).toDouble();
        baseBalance -= query.value(2).toDouble();
    }
    return baseBalance;
}

void ConnectorData::refreshData(QDate date)
{
    QSqlQuery query;
    QDate dateChange;
    double baseBalance = 0;
    double base = 0;
    double in = 0;
    double out = 0;
    query.prepare("SELECT date, baseBalance, income, outcome FROM DayInfo_Table WHERE date >= :date ORDER BY date");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.exec();

    query.next();
    base = query.value(1).toDouble();
    in = query.value(2).toDouble();
    out = query.value(3).toDouble();
    while(query.next())
    {
        baseBalance = base + in - out;
        dateChange = query.value(0).toDate();

        QSqlQuery query2;
        query2.prepare("UPDATE DayInfo_Table set baseBalance=:base WHERE date=:date");
        query2.bindValue(":base", baseBalance);
        query2.bindValue(":date", dateChange);
        query2.exec();

        base = baseBalance;
        in = query.value(2).toDouble();
        out = query.value(3).toDouble();
    }
}

void ConnectorData::connectToDataBase()
{
    _dataBase = QSqlDatabase::addDatabase("QSQLITE");
    if(QFile("DayInfo_Base.db").exists())
    {
        _dataBase.setDatabaseName("DayInfo_Base.db");
        _dataBase.open();
    }

    else
    {
        _dataBase.setDatabaseName("DayInfo_Base.db");
        _dataBase.open();
        QSqlQuery query;
        query.exec("CREATE TABLE DayInfo_Table (date DATE PRIMARY KEY, baseBalance DOUBLE, income DOUBLE, outcome DOUBLE);");
        _dataBase.open();
    }
}

void ConnectorData::disconnectFromDataBase()
{
    _dataBase.close();
}
