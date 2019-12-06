#ifndef IDUPLOADER_H
#define IDUPLOADER_H
#include "precompiled.h"
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

struct ServerInfo
{
    explicit ServerInfo();
    void set(QString addr,uint port);

    QString _addr;
    uint _port;


};

class QNetworkAccessManager;
class IDUploader : public QObject
{
    Q_OBJECT
public:
    explicit IDUploader(QObject *parent = 0);
    ~IDUploader();

    QMap<QString,QString> upload(QString remark,const QStringList&);
    QNetworkAccessManager* _manager;
    volatile bool _done;
    QNetworkReply* _reply;
    QMap<QString,QString> _items;
signals:

public slots:
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError);
};

#endif // IDUPLOADER_H
