#include "generatorpage.h"
#include "precompiled.h"

GeneratorPage::GeneratorPage(QWidget *parent) : QWidget(parent)
{
    _infoPanel = new GeneratorInfoPanel(this);
    QHBoxLayout* infoLayout = new QHBoxLayout;
    infoLayout->addStretch(1);
    infoLayout->addWidget(_infoPanel,6);
    infoLayout->addStretch(1);

    _btnCreate = new QPushButton(tr("生    成"));
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
    connect(_btnCreate,&QPushButton::clicked,this,[=](){
        auto total = _infoPanel->_countEdit->text().toULong();
        if(total <=0)
            return;

        emit btnGenClicked(_infoPanel->_verEdit->text(),
                           _infoPanel->_reservedEdit->text(),
                           total,
                           _infoPanel->_remarkEdit->text()
                );
    });
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
    connect(_btnHome,&QPushButton::clicked,this,&GeneratorPage::btnHomeClicked);
    QHBoxLayout* btnHomeLayout = new QHBoxLayout;
    btnHomeLayout->addStretch(1);
    btnHomeLayout->addWidget(_btnHome);
    btnHomeLayout->addStretch(1);



    auto mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(infoLayout,6);
    mainLayout->addStretch(2);
    mainLayout->addLayout(btnCreateLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(btnHomeLayout);
    mainLayout->addStretch(1);
}


