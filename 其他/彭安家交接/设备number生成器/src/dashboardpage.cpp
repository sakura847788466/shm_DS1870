#include "dashboardpage.h"
#include "precompiled.h"

DashboardPage::DashboardPage(QWidget *parent) : QWidget(parent)
{
    _btnCreate = new QPushButton();
    _btnCreate->setMinimumSize(128,128);
    _btnCreate->setStyleSheet("QPushButton { \
                                border: none; \
                                border-image: url(:/resource/image/new.png);\
                              }\
                              QPushButton:pressed {\
                                 background-color: darkgreen;\
                              }\
                              QPushButton:hover {\
                                 margin: 5px;\
                              }"
                              );
    connect(_btnCreate,&QPushButton::clicked,this,&DashboardPage::btnCreateClicked);
    _btnHistory = new QPushButton();
    _btnHistory->setMinimumSize(128,128);
    _btnHistory->setStyleSheet("QPushButton { \
                                border: none; \
                                border-image: url(:/resource/image/history.png);\
                              }\
                              QPushButton:pressed {\
                                 background-color: darkgreen;\
                              }\
                              QPushButton:hover {\
                                 margin: 5px;\
                              }"
                              );
    connect(_btnHistory,&QPushButton::clicked,this,&DashboardPage::btnHistoryClicked);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addStretch(1);
    mainLayout->addWidget(_btnCreate);
    mainLayout->addStretch(1);
    mainLayout->addWidget(_btnHistory);
    mainLayout->addStretch(1);


}

