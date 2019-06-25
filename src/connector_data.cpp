#include "connector_data.h"
#include "dayinfo_label.h"
#include <QDebug>


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
    _instance->connectToDateBase();
}

void ConnectorData::deinit()
{
    _instance->disconnectFromDateBase();
    delete _instance;
}

DayInfo ConnectorData::getDayInfo(QDate date)
{
    QSqlQuery query;
    query.prepare("SELECT income, outcome FROM DayInfo_Table WHERE date=:dateString");
    query.bindValue(":dateString", date.toString("yyyy-MM-dd"));
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
    query.prepare("SELECT income FROM DayInfo_Table WHERE date=:dateString");
    query.bindValue(":dateString", date.toString("yyyy-MM-dd"));
    query.exec();
    if(query.next())
    {
        QSqlQuery query2;
        query2.prepare("UPDATE DayInfo_Table SET baseBalance =:base, income=:in, outcome=:out WHERE date=:date;");
        query2.bindValue(":base", dayInfo.getBaseBalance());
        query2.bindValue(":in", dayInfo.getIncome());
        query2.bindValue(":out", dayInfo.getOutcome());
        query2.bindValue(":date", date.toString("yyyy-MM-dd"));
        query2.exec();
    }
    else
    {
        QSqlQuery query2;
        query2.prepare("INSERT INTO DayInfo_Table (date, baseBalance, income, outcome) VALUES (:date ,:base, :in, :out);");
        query2.bindValue(":date", date.toString("yyyy-MM-dd"));
        query2.bindValue(":base", dayInfo.getBaseBalance());
        query2.bindValue(":in", dayInfo.getIncome());
        query2.bindValue(":out", dayInfo.getOutcome());
        query2.exec();
    }
    refreshData();
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

void ConnectorData::refreshData()
{
    QSqlQuery query;
    double baseBalance = 0;
    query.exec("SELECT date FROM DayInfo_Table DESC");
    while(query.next())
    {
        QDate date = query.value(0).toDate();
        baseBalance = calcBaseBalance(date);
        QSqlQuery query2;
        query2.prepare("UPDATE DayInfo_Table set baseBalance=:base WHERE date=:date");
        query2.bindValue(":base", baseBalance);
        query2.bindValue(":date", date);
        query2.exec();
    }
}

void ConnectorData::connectToDateBase()
{
    _instance->_dateBase = QSqlDatabase::addDatabase("QSQLITE");
    if(QFile("DayInfo_Base.db").exists())
    {
        _instance->_dateBase.setDatabaseName("DayInfo_Base.db");
        _instance->_dateBase.open();
    }

    else
    {
        _instance->_dateBase.setDatabaseName("DayInfo_Base.db");
        _instance->_dateBase.open();
        QSqlQuery query;
        query.exec("CREATE TABLE DayInfo_Table (date DATE PRIMARY KEY, baseBalance DOUBLE, income DOUBLE, outcome DOUBLE);");
        _instance->_dateBase.open();
    }
}

void ConnectorData::disconnectFromDateBase()
{
    _instance->_dateBase.close();
}
