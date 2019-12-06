#include "mymodel.h"
#include "precompiled.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QUuid>

MyModel myModel;
MyModel::MyModel(QObject *parent) : QObject(parent)
{


}

MyModel::~MyModel()
{
    _db.close();
}

void MyModel::setDB(QString db)
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(db);
    if( _db.open() ){
        QSqlQuery sql_query;
        QString create_sql = "create table outlines (tablename varchar(64) primary key, ver varchar(16), reserve varchar(8), count INTEGER, remark TEXT, time varchar(24))";
        sql_query.prepare(create_sql);
        if(!sql_query.exec())
        {
            //qDebug() << "Error: Fail to create table(outlines)" << sql_query.lastError();
        }
        else
        {

        }
    }
}

void MyModel::newOutline(QString ver, QString reserved, ulong count,QString remark)
{
    if( !_db.isOpen() )
        return;
    if(count == 0)
        return;

    QSqlQuery sql_query;
    _currentTable = QString("t") + QUuid::createUuid().toString().remove("{").remove("}").remove("-");
    QString insert_sql = "insert into outlines values (?, ?, ?, ?, ?, ?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(_currentTable);
    sql_query.addBindValue(ver);
    sql_query.addBindValue(reserved);
    sql_query.addBindValue(uint(count));
    sql_query.addBindValue(remark);
    sql_query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        QSqlQuery query;
        QString create_sql = QString("create table %1 (devid varchar(64) primary key, upload TEXT)").arg(_currentTable);
        if(!query.exec(create_sql))
        {
            qDebug() << "Error: Fail to create table " <<  _currentTable << query.lastError();
        }
        else
        {

        }
    }
}

void MyModel::insertIDs(const QStringList& ids)
{
    if( !_db.isOpen() )
        return;
    if(ids.isEmpty())
        return;
    if(_currentTable.isEmpty())
        return;


    _db.transaction();
    for(auto id:ids){

        QSqlQuery sql_query;
        QString insert_sql = QString("insert into %1 values (?, ?)").arg(_currentTable);
        sql_query.prepare(insert_sql);
        sql_query.addBindValue(id);
        sql_query.addBindValue("");
        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {

        }
    }
    _db.commit();
}

QList<IDOutline> MyModel::getAllOutlines()
{
    QList<IDOutline> res;

    if( !_db.isOpen() )
        return res;


    QSqlQuery query;
    query.prepare("SELECT * FROM  outlines");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    else
    {
        while(query.next())
        {
            res.append(IDOutline(
                       query.value(0).toString(),
                       query.value(1).toString(),
                       query.value(2).toString(),
                       query.value(3).toUInt(),
                       query.value(4).toString(),
                       query.value(5).toString()
                           )
                       );
        }
    }

    return res;
}

IDStatistics MyModel::getStatistics(QString tablename)
{
    IDStatistics res{0,0};

    if( !_db.isOpen() )
        return res;

    _currentTable = tablename;

    QSqlQuery query;
    query.prepare( QString("SELECT upload FROM %1").arg(tablename) );
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    else
    {
        while(query.next())
        {
            res._created++;
            if(query.value(0).toString().isEmpty()==false){
                res._uploaded++;
            }
        }
    }

    return res;
}


void MyModel::rangeUnuploadedRecords(IDOutline id,RANGECALLBACK callback)
{
    _abordUpload = false;
    if( !_db.isOpen() )
        return;

    QStringList chunk;

    QSqlQuery query;
    query.prepare( QString("SELECT * FROM %1 WHERE upload=''").arg(_currentTable) );
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    else
    {
        while(query.next() && !_abordUpload)
        {
            chunk.append(query.value(0).toString());
            if( chunk.length() >= 100 ){
                callback(id._remark,chunk);
                chunk.clear();
            }
        }

        if( chunk.isEmpty() == false ){
            callback(id._remark,chunk);
            chunk.clear();
        }
    }
}

void MyModel::updateUploadFlag(const QMap<QString,QString>& res)
{
    if( !_db.isOpen() )
        return;

    _db.transaction();
    for(auto r:res.keys()){

        QSqlQuery sql_query;
        QString sql = QString("UPDATE %1 SET upload=? WHERE devid=?").arg(_currentTable);
        sql_query.prepare(sql);
        sql_query.addBindValue(res[r]);
        sql_query.addBindValue(r);
        if(!sql_query.exec())
        {
            qDebug() << "updateUploadFlag()  sql=" << sql << sql_query.lastError();
        }
        else
        {

        }
    }
    _db.commit();
}
