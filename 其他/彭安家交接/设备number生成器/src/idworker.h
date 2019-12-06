#ifndef IDWORKER_H
#define IDWORKER_H

class IDWorker : public QObject
{
    Q_OBJECT
public:
    explicit IDWorker();

signals:
    void callback(const QStringList&);
public slots:
    void start(QString ver, QString reserved, ulong count);
    void abord();
private:
    volatile bool _cancel;
};

#endif // IDWORKER_H
