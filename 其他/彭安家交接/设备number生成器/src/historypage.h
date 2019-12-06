#ifndef HISTORYPAGE_H
#define HISTORYPAGE_H
#include "idstructs.h"
#include "precompiled.h"
#include <QStyleOption>
#include "configdlg.h"

class QListWidget;

class IDInfoPanel : public QWidget
{
    Q_OBJECT
public:

    QLabel* _verLabel;
    QLabel* _reservedLabel;
    QLabel* _countLabel;
    QLabel* _remarkLabel;
    QLabel* _createLabel;
    QLabel* _uploadLabel;

    IDInfoPanel(QWidget *parent = 0): QWidget(parent)
    {
        setStyleSheet("IDInfoPanel{border: 2px dot-dash gray ; margin: 0px;}QLabel{color:DarkGreen}");
        setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

        _verLabel = new QLabel(this);
        QHBoxLayout* verLayout = new QHBoxLayout;
        verLayout->addWidget(new QLabel(tr("版    本："),this));
        verLayout->addSpacing(6);
        verLayout->addWidget(_verLabel,1);

        _reservedLabel = new QLabel(this);
        QHBoxLayout* reservedLayout = new QHBoxLayout;
        reservedLayout->addWidget(new QLabel(tr("保    留："),this));
        reservedLayout->addSpacing(6);
        reservedLayout->addWidget(_reservedLabel,1);

        _countLabel = new QLabel(this);
        QHBoxLayout* countLayout = new QHBoxLayout;
        countLayout->addWidget(new QLabel(tr("数    量："),this));
        countLayout->addSpacing(6);
        countLayout->addWidget(_countLabel,1);

        _remarkLabel = new QLabel(this);
        QHBoxLayout* remarkLayout = new QHBoxLayout;
        remarkLayout->addWidget(new QLabel(tr("备    注："),this));
        remarkLayout->addSpacing(6);
        remarkLayout->addWidget(_remarkLabel,1);

        _createLabel = new QLabel(this);
        QHBoxLayout* createLayout = new QHBoxLayout;
        createLayout->addWidget(new QLabel(tr("生成数量："),this));
        createLayout->addSpacing(6);
        createLayout->addWidget(_createLabel,1);

        _uploadLabel = new QLabel(this);
        QHBoxLayout* uploadLayout = new QHBoxLayout;
        uploadLayout->addWidget(new QLabel(tr("上传数量："),this));
        uploadLayout->addSpacing(6);
        uploadLayout->addWidget(_uploadLabel,1);


        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(60,0,10,0);
        mainLayout->addStretch(1);
        mainLayout->addLayout(verLayout);
        mainLayout->addSpacing(20);
        mainLayout->addLayout(reservedLayout);
        mainLayout->addSpacing(20);
        mainLayout->addLayout(countLayout);
        mainLayout->addSpacing(20);
        mainLayout->addLayout(remarkLayout);
        mainLayout->addSpacing(20);
        mainLayout->addLayout(createLayout);
        mainLayout->addSpacing(20);
        mainLayout->addLayout(uploadLayout);
        mainLayout->addStretch(1);
    }
    void paintEvent(QPaintEvent *)
    {
        QStyleOption opt;
        opt.init(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }

    void updateBasicInfo(IDOutline node)
    {
        _verLabel->setText(node._ver);
        _reservedLabel->setText(node._reserve);
        _remarkLabel->setText(node._remark);
        _countLabel->setText(QString::number(node._count));
    }

    void updateStatisticsInfo(IDStatistics node)
    {
        _createLabel->setText(QString::number(node._created));
        _uploadLabel->setText(QString::number(node._uploaded));
    }
};


class DashboardPanel : public QWidget
{
    Q_OBJECT
public:

    DashboardPanel(QWidget *parent = 0): QWidget(parent)
    {
        setStyleSheet("DashboardPanel{background-color: lightgray }");
        setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

        _btnConfig = new QPushButton("服务器配置");
        _btnConfig->setFixedSize(128,32);
        _btnConfig->setStyleSheet("QPushButton { \
                                    border-radius: 6px;\
                                    border: 1px solid CornflowerBlue; \
                                    background-color: CornflowerBlue;\
                                    color: white;\
                                  }\
                                  QPushButton:pressed {\
                                     color: GREEN;\
                                  }\
                                  QPushButton:hover {\
                                     border: 1px solid SKYBLUE; \
                                  }"
                                  );
        connect(_btnConfig,&QPushButton::clicked,this,[=](){
            ConfigDlg dlg;
            dlg.exec();
        });
        _btnUpload = new QPushButton(tr("上    传"));
        _btnUpload->setFixedSize(128,32);
        _btnUpload->setStyleSheet("QPushButton { \
                                    border-radius: 6px;\
                                    border: 1px solid CornflowerBlue; \
                                    background-color: CornflowerBlue;\
                                    color: white;\
                                  }\
                                  QPushButton:pressed {\
                                     color: GREEN;\
                                  }\
                                  QPushButton:hover {\
                                     border: 1px solid SKYBLUE; \
                                  }"
                                  );
        connect(_btnUpload,&QPushButton::clicked,this,&DashboardPanel::btnUploadClicked);
        QHBoxLayout* btnUploadLayout = new QHBoxLayout;
        btnUploadLayout->addStretch(1);
        btnUploadLayout->addWidget(_btnUpload);
        btnUploadLayout->addWidget(_btnConfig);
        btnUploadLayout->addStretch(1);


        _btnCreate = new QPushButton(tr("新建生成"));
        _btnCreate->setFixedSize(256,32);
        _btnCreate->setStyleSheet("QPushButton { \
                                    border-radius: 6px;\
                                    border: 1px solid DODGERBLUE; \
                                    background-color: DODGERBLUE;\
                                    color: white;\
                                  }\
                                  QPushButton:pressed {\
                                     color: GREEN;\
                                  }\
                                  QPushButton:hover {\
                                     border: 1px solid SKYBLUE; \
                                  }"
                                  );
        connect(_btnCreate,&QPushButton::clicked,this,&DashboardPanel::btnCreateClicked);
        QHBoxLayout* btnCreateLayout = new QHBoxLayout;
        btnCreateLayout->addStretch(1);
        btnCreateLayout->addWidget(_btnCreate);
        btnCreateLayout->addStretch(1);


        _btnHome = new QPushButton(tr("返回主页"));
        _btnHome->setFixedSize(256,32);
        _btnHome->setStyleSheet("QPushButton { \
                                    border-radius: 6px;\
                                    border: 1px solid TOMATO; \
                                    background-color: TOMATO;\
                                    color: white;\
                                  }\
                                  QPushButton:pressed {\
                                     color: GREEN;\
                                  }\
                                  QPushButton:hover {\
                                     border: 1px solid SKYBLUE; \
                                  }"
                                  );
        connect(_btnHome,&QPushButton::clicked,this,&DashboardPanel::btnHomeClicked);
        QHBoxLayout* btnHomeLayout = new QHBoxLayout;
        btnHomeLayout->addStretch(1);
        btnHomeLayout->addWidget(_btnHome);
        btnHomeLayout->addStretch(1);

        auto mainLayout = new QVBoxLayout(this);
        mainLayout->addStretch(1);
        mainLayout->addLayout(btnUploadLayout);
        mainLayout->addSpacing(20);
        mainLayout->addLayout(btnCreateLayout);
        mainLayout->addSpacing(20);
        mainLayout->addLayout(btnHomeLayout);
        mainLayout->addStretch(1);
    }
    void paintEvent(QPaintEvent *)
    {
        QStyleOption opt;
        opt.init(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }

    QPushButton* _btnUpload;
    QPushButton* _btnConfig;
    QPushButton* _btnCreate;
    QPushButton* _btnHome;
signals:
    void btnHomeClicked();
    void btnCreateClicked();
    void btnUploadClicked();
};

class HistoryPage : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryPage(QWidget *parent = 0);
    void updateOutlines();
    virtual void showEvent(QShowEvent * e);

    void setCurrentOutline();
private:
    QListWidget* _outlinesWgt;
    IDInfoPanel* _infoPanel;
    DashboardPanel* _dashboard;

    QList<IDOutline> _outlines;
signals:
    void btnHomeClicked();
    void btnCreateClicked();
    void btnUploadClicked(IDOutline);
public slots:
    void updateInfoPanel();
    void onUploadClicked();
};

#endif // HISTORYPAGE_H
