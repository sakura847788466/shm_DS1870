#include "configdlg.h"
#include "precompiled.h"
#include "iduploader.h"

extern ServerInfo g_serverInfo;

ConfigDlg::ConfigDlg(QWidget *parent) : QDialog(parent)
{
    setFixedSize(400,280);

    _serverEdit = new QLineEdit("",this);
    QHBoxLayout* serverLayout = new QHBoxLayout;
    serverLayout->addWidget(new QLabel(tr("地址："),this));
    serverLayout->addSpacing(6);
    serverLayout->addWidget(_serverEdit,3);
    serverLayout->addStretch(1);

    _portEdit = new QLineEdit("",this);
    _portEdit->setInputMask("000000");
    QHBoxLayout* portLayout = new QHBoxLayout;
    portLayout->addWidget(new QLabel(tr("端口："),this));
    portLayout->addSpacing(6);
    portLayout->addWidget(_portEdit,1);
    portLayout->addStretch(2);

    _btnConfig = new QPushButton("配置",this);
    connect(_btnConfig,&QPushButton::clicked,this,&ConfigDlg::onConfig);
    _btnCancel = new QPushButton("取消",this);
    connect(_btnCancel,&QPushButton::clicked,this,[=](){
        this->close();
    });
    QHBoxLayout* ctrlLayout = new QHBoxLayout;
    ctrlLayout->addSpacing(6);
    ctrlLayout->addStretch(1);
    ctrlLayout->addWidget(_btnConfig);
    ctrlLayout->addWidget(_btnCancel);


    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20,0,20,20);
    mainLayout->addStretch(1);
    mainLayout->addLayout(serverLayout);
    mainLayout->addSpacing(26);
    mainLayout->addLayout(portLayout);
    mainLayout->addStretch(1);
    mainLayout->addLayout(ctrlLayout);


    _serverEdit->setText( g_serverInfo._addr );
    _portEdit->setText( QString::number(g_serverInfo._port) );
}

void ConfigDlg::onConfig()
{
    g_serverInfo.set(_serverEdit->text(), _portEdit->text().toUInt());
    this->close();
}
