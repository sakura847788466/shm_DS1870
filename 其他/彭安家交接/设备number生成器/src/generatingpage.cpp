#include "generatingpage.h"
#include "precompiled.h"

GeneratingPage::GeneratingPage(QWidget *parent) : QWidget(parent)
{
    _whatLabel = new QLabel(this);
    _whatLabel->setStyleSheet("QLabel{color: darkgray; font: bold;font-size: 36px}");
    _percentLabel = new QLabel("00",this);
    _percentLabel->setStyleSheet("QLabel{color: darkgreen; font: bold italic large \"Times New Roman\"; font-size: 56px}");
    _indexLabel = new QLabel("0",this);
    _totolLabel = new QLabel("0",this);

    QHBoxLayout* percentLayout = new QHBoxLayout;
    percentLayout->addStretch(1);
    percentLayout->addWidget(_percentLabel);
    percentLayout->addWidget(new QLabel("%",this));
    percentLayout->addStretch(1);

    QHBoxLayout* progressLayout = new QHBoxLayout;
    progressLayout->addStretch(1);
    progressLayout->addWidget(_indexLabel);
    progressLayout->addWidget(new QLabel("/",this));
    progressLayout->addWidget(_totolLabel);
    progressLayout->addStretch(1);

    QHBoxLayout* whatLayout = new QHBoxLayout;
    whatLayout->addStretch(1);
    whatLayout->addWidget(_whatLabel);
    whatLayout->addStretch(2);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch(1);    
    mainLayout->addLayout(whatLayout);
    mainLayout->addStretch(2);
    mainLayout->addLayout(percentLayout);
    mainLayout->addLayout(progressLayout);
    mainLayout->addStretch(3);
}

void GeneratingPage::hideEvent(QHideEvent * event)
{
    _total = _index = 0;
    _indexLabel->setText("0");
    _percentLabel->setText( "0"  );
    _totolLabel->setText("0");

    QWidget::hideEvent(event);
}

void GeneratingPage::reset(QString what,ulong total)
{
    _total = total;
    _index = 0;
    _totolLabel->setText(QString::number(_total));
    _whatLabel->setText(what);    
}

void GeneratingPage::onCallback(const QStringList& items)
{
    _index += items.length();
    _indexLabel->setText(QString::number(_index));
    _percentLabel->setText(
                QString::number(
                    uint(   double(_index)/_total*100  )
                                )
                );
}

