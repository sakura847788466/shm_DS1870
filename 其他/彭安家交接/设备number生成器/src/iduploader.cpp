#include "iduploader.h"
#include <QThread>
#include <QSettings>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>


ServerInfo g_serverInfo;
ServerInfo::ServerInfo()
{
    _addr = "yun.ifengwo.com.cn";
    _port = 80;

    QSettings settings("dascom", "iduploader");
    QString addr = settings.value("addr").toString();
    if( addr.isEmpty() == false ){
        _addr = addr;
    }

    uint port = settings.value("port").toUInt();
    if( port > 0 ){
        _port = port;
    }
}

void ServerInfo::set(QString addr,uint port)
{
    _addr = addr;
    _port = port;

    QSettings settings("dascom", "iduploader");
    settings.setValue("addr",addr);
    settings.setValue("port",port);
}

IDUploader::IDUploader(QObject *parent) : QObject(parent)
{
     _manager = new QNetworkAccessManager(this);
}
IDUploader::~IDUploader()
{
    if ( _manager ){
        delete _manager;
        _manager = 0;
    }
}



QMap<QString,QString> IDUploader::upload(QString remark,const QStringList& items)
{
    _done = false;
    _items.clear();

    QString json("{\"numbers\":[");
    for(int i=0;i<items.length();++i){
        json += QString("\"%1\"").arg(items[i]);
        if( i != items.length()-1 ){
            json += ",";
        }
        _items[items[i]] = "ok";
    }
    json += QString("],\"remark\":\"%1\"}").arg(remark);


    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setUrl(QUrl(QString("http://%1:%2/cloudprint/common/printPoolJudge").arg(g_serverInfo._addr).arg(g_serverInfo._port)));

    _reply = _manager->post(request,json.toUtf8());
    connect(_reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slotError(QNetworkReply::NetworkError)));

    int timeout = 0;
    while (_done == false) {
        QCoreApplication::processEvents();

        if( timeout>=3000 ){
            _reply->abort();
            _reply->deleteLater();
            break;
        }else{
            QThread::msleep(50);
            timeout += 50;
        }

        QCoreApplication::processEvents();
    }

    return _items;
}

void IDUploader::slotReadyRead()
{
    QString res = _reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(res.toUtf8());
    if(!doc.isObject()){
        for(QString key:_items.keys()){
            _items[key] = "json parse error";
        }
    }

    QJsonObject jo = doc.object();
    QString errStr = jo.value("errorReason").toString();
    QJsonArray array = jo.value("failureNumbers").toArray();
    for(auto it = array.constBegin(); it != array.constEnd(); it++){
        QJsonObject subObj = (*it).toObject();
        _items[subObj.value("number").toString()] = errStr;
    }

    _done = true;
}

void IDUploader::slotError(QNetworkReply::NetworkError )
{
    for(QString key:_items.keys()){
        _items[key] = "";
    }
    _done = true;
}

