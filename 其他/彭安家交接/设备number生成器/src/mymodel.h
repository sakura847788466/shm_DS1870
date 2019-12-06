#ifndef MYMODEL_H
#define MYMODEL_H
#include <QSqlDatabase>
#include "idstructs.h"

typedef void (*RANGECALLBACK)(QString remark, const QStringList&);

class MyModel : public QObject
{
    Q_OBJECT
public:
    explicit MyModel(QObject *parent = 0);
    ~MyModel();
    void setDB(QString);
    void newOutline(QString ver, QString reserved, ulong count,QString remark);
    void insertIDs(const QStringList&);

    QList<IDOutline> getAllOutlines();
    IDStatistics getStatistics(QString tablename);
    void rangeUnuploadedRecords(IDOutline ,RANGECALLBACK);
    void updateUploadFlag(const QMap<QString,QString>&);

    volatile bool _abordUpload;
private:
    QString _currentTable;
    QSqlDatabase _db;
signals:

public slots:
};

extern MyModel myModel;

#endif // MYMODEL_H
