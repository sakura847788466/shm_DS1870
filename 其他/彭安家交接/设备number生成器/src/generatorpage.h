#ifndef GENERATORPAGE_H
#define GENERATORPAGE_H
#include <QStyleOption>
#include <QPainter>
#include <QGridLayout>
#include <QLineEdit>

class QPushButton;

class GeneratorInfoPanel : public QWidget
{
    Q_OBJECT
public:

    QLineEdit* _verEdit;
    QLineEdit* _reservedEdit;
    QLineEdit* _countEdit;
    QLineEdit* _remarkEdit;

    GeneratorInfoPanel(QWidget *parent = 0): QWidget(parent)
    {
        setStyleSheet("GeneratorInfoPanel{border: 2px dot-dash gray ; margin: 0px;}");
        setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

        _verEdit = new QLineEdit("0.0.0.0",this);
        _verEdit->setInputMask("B.B.B.B");
        QHBoxLayout* verLayout = new QHBoxLayout;
        verLayout->addWidget(new QLabel(tr("版本："),this));
        verLayout->addSpacing(6);
        verLayout->addWidget(_verEdit,1);
        verLayout->addWidget(new QLabel(" (bit7 - bit4 in byte0)",this),4);

        _reservedEdit = new QLineEdit("00",this);
        _reservedEdit->setInputMask("HH");
        QHBoxLayout* reservedLayout = new QHBoxLayout;
        reservedLayout->addWidget(new QLabel(tr("保留："),this));
        reservedLayout->addSpacing(6);
        reservedLayout->addWidget(_reservedEdit,1);
        reservedLayout->addWidget(new QLabel(" (Hexadecimal string of byte7)",this),6);

        _countEdit = new QLineEdit("0",this);
        _countEdit->setInputMask("000000000000000");
        QHBoxLayout* countLayout = new QHBoxLayout;
        countLayout->addWidget(new QLabel(tr("数量："),this));
        countLayout->addSpacing(6);
        countLayout->addWidget(_countEdit,1);
        countLayout->addStretch(2);

        _remarkEdit = new QLineEdit(this);
        QHBoxLayout* remarkLayout = new QHBoxLayout;
        remarkLayout->addWidget(new QLabel(tr("备注："),this));
        remarkLayout->addSpacing(6);
        remarkLayout->addWidget(_remarkEdit,1);


        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(20,0,20,0);
        mainLayout->addStretch(1);
        mainLayout->addLayout(verLayout);
        mainLayout->addSpacing(26);
        mainLayout->addLayout(reservedLayout);
        mainLayout->addSpacing(26);
        mainLayout->addLayout(countLayout);
        mainLayout->addSpacing(26);
        mainLayout->addLayout(remarkLayout);
        mainLayout->addStretch(1);
    }
    void paintEvent(QPaintEvent *)
    {
        QStyleOption opt;
        opt.init(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }
};


class GeneratorPage : public QWidget
{
    Q_OBJECT
public:
    explicit GeneratorPage(QWidget *parent = 0);
private:
    GeneratorInfoPanel* _infoPanel;
    QPushButton* _btnCreate;
    QPushButton* _btnHome;
signals:
    void btnHomeClicked();
    void btnGenClicked(QString ver, QString reserved, ulong count,QString remark);
public slots:

};

#endif // GENERATORPAGE_H
