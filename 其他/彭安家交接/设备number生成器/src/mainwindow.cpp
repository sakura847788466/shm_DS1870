#include "mainwindow.h"
#include "dashboardpage.h"
#include "generatorpage.h"
#include "historypage.h"
#include "generatingpage.h"
#include "idworker.h"
#include <QStackedWidget>
#include <QDir>
#include <QCoreApplication>
#include "iduploader.h"

MainWindow* g_mainWnd = NULL;
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    _dashboardPage = new DashboardPage(this);
    connect(_dashboardPage,&DashboardPage::btnCreateClicked,[=](){
        _statckedWgt->setCurrentWidget(_generatorPage);
    });    
    connect(_dashboardPage,&DashboardPage::btnHistoryClicked,[=](){
        _statckedWgt->setCurrentWidget(_historyPage);
    });


    _generatorPage = new GeneratorPage(this);
    _generatorPage->hide();
    connect(_generatorPage,&GeneratorPage::btnHomeClicked,[=](){
        _statckedWgt->setCurrentWidget(_dashboardPage);
    });
    connect(_generatorPage,&GeneratorPage::btnGenClicked,this,&MainWindow::generateSlot);


    _progressPage = new GeneratingPage(this);
    _progressPage->hide();


    _historyPage = new HistoryPage(this);
    _historyPage->hide();
    connect(_historyPage,&HistoryPage::btnHomeClicked,[=](){
        _statckedWgt->setCurrentWidget(_dashboardPage);
    });
    connect(_historyPage,&HistoryPage::btnCreateClicked,[=](){
        _statckedWgt->setCurrentWidget(_generatorPage);
    });
    connect(_historyPage,&HistoryPage::btnUploadClicked,this,&MainWindow::onUpload);

    _statckedWgt = new QStackedWidget(this);
    _statckedWgt->addWidget(_dashboardPage);
    _statckedWgt->addWidget(_generatorPage);
    _statckedWgt->addWidget(_historyPage);
    _statckedWgt->addWidget(_progressPage);
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(_statckedWgt);


    setMinimumSize(800,600);
    setStyleSheet("background:white");


    IDWorker *worker = new IDWorker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &MainWindow::fireGen, worker, &IDWorker::start);
    connect(this, &MainWindow::abordGen, worker, &IDWorker::abord);
    connect(worker, &IDWorker::callback, _progressPage, &GeneratingPage::onCallback);
    connect(worker, &IDWorker::callback, this, &MainWindow::onCallback);
    workerThread.start();

    auto exePath = QDir(QCoreApplication::applicationFilePath());
    exePath.cdUp();
    myModel.setDB(exePath.path() + "//idg.db");

    g_mainWnd = this;

    setWindowTitle(QString("ID生成器  ")+"v1.0.1");
}

MainWindow::~MainWindow()
{
    emit abordGen();
    QThread::msleep(600);
    workerThread.quit();
    workerThread.wait(1000);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    myModel._abordUpload = true;
    QThread::msleep(200);
    QWidget::closeEvent(event);
}

void myRangeCallback(QString remark,const QStringList& items)
{
    QCoreApplication::processEvents();

    IDUploader uploader;
    QMap<QString,QString> res = uploader.upload(remark,items);
    QCoreApplication::processEvents();

    myModel.updateUploadFlag(res);
    QCoreApplication::processEvents();

    g_mainWnd->_progressPage->onCallback(items);
    QCoreApplication::processEvents();

    QThread::msleep(300);
    QCoreApplication::processEvents();
}

void MainWindow::onUpload(IDOutline id)
{
    auto info = myModel.getStatistics(id._tablename);
    _progressPage->reset(tr("上传中:"),info._created-info._uploaded);
    _statckedWgt->setCurrentWidget(_progressPage);

    myModel.rangeUnuploadedRecords(id,myRangeCallback);

    _statckedWgt->setCurrentWidget(_historyPage);
}

void MainWindow::generateSlot(QString ver, QString reserved, ulong count,QString remark)
{
    myModel.newOutline(ver,reserved,count,remark);

    _progressPage->reset(tr("生成中:"),count);
    _statckedWgt->setCurrentWidget(_progressPage);
    emit fireGen(ver,reserved,count);
}


void MainWindow::onCallback(const QStringList& items)
{
    if( items.isEmpty() ){
        _statckedWgt->setCurrentWidget(_historyPage);
    }else{
        myModel.insertIDs(items);
    }
}
