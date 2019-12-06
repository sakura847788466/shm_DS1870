#include "historypage.h"
#include <QListWidget>
#include "mymodel.h"


HistoryPage::HistoryPage(QWidget *parent) : QWidget(parent)
{
    _outlinesWgt = new QListWidget(this);
    _outlinesWgt->setFixedWidth(160);
    connect(_outlinesWgt,&QListWidget::currentRowChanged,this,&HistoryPage::updateInfoPanel);

    _infoPanel = new IDInfoPanel(this);
    _dashboard = new DashboardPanel(this);
    connect(_dashboard,&DashboardPanel::btnHomeClicked,this,&HistoryPage::btnHomeClicked);
    connect(_dashboard,&DashboardPanel::btnCreateClicked,this,&HistoryPage::btnCreateClicked);
    connect(_dashboard,&DashboardPanel::btnUploadClicked,this,&HistoryPage::onUploadClicked);

    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->addWidget(_infoPanel,1);
    rightLayout->addWidget(_dashboard,1);

    auto mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(_outlinesWgt);
    mainLayout->addLayout(rightLayout,1);
}

void HistoryPage::onUploadClicked()
{
    IDOutline id;
    QString time = _outlinesWgt->currentItem()->text();
    for(auto node:_outlines){
         if(node._time == time){
            id = node;
            break;
         }
    }
    if( id._tablename.isEmpty() == false ){
        emit btnUploadClicked(id);
    }
}

void HistoryPage::updateOutlines()
{
   _outlinesWgt->clear();
   _outlines = myModel.getAllOutlines();

   QStringList keys;
   for(auto node:_outlines){
        keys.append(node._time);
   }
   for(auto it=keys.end(); it!=keys.begin(); ){
       --it;
       _outlinesWgt->addItem(*it);
   }
   _outlinesWgt->setCurrentRow(0);
}

void HistoryPage::showEvent(QShowEvent * e)
{
    updateOutlines();
    QWidget::showEvent(e);
}

void HistoryPage::updateInfoPanel()
{
    auto item = _outlinesWgt->currentItem();
    if( item ){
        QString time = item->text();
        for(auto node:_outlines){
             if(node._time==time){
                 _infoPanel->updateBasicInfo(node);
                 IDStatistics s = myModel.getStatistics(node._tablename);
                 _infoPanel->updateStatisticsInfo(s);
                break;
             }
        }
    }
}

void HistoryPage::setCurrentOutline()
{

}

