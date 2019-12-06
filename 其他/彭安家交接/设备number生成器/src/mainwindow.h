#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QThread>
#include "mymodel.h"

class DashboardPage;
class GeneratorPage;
class HistoryPage;
class QStackedWidget;
class GeneratingPage;


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void closeEvent(QCloseEvent * event);
signals:
    void fireGen(QString ver, QString reserved, ulong count);
    void abordGen();
public slots:
    void generateSlot(QString ver, QString reserved, ulong count,QString remark);
    void onCallback(const QStringList&);
    void onUpload(IDOutline);
public:
    DashboardPage* _dashboardPage;
    GeneratorPage* _generatorPage;
    HistoryPage* _historyPage;
    GeneratingPage* _progressPage;
    QStackedWidget* _statckedWgt;

    QThread workerThread;    
};

#endif // MAINWINDOW_H
