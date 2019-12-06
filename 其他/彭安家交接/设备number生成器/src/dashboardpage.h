#ifndef DASHBOARDPAGE_H
#define DASHBOARDPAGE_H

class QPushButton;

class DashboardPage : public QWidget
{
    Q_OBJECT
public:
    explicit DashboardPage(QWidget *parent = 0);
private:
    QPushButton* _btnCreate;
    QPushButton* _btnHistory;
signals:
    void btnCreateClicked();
    void btnHistoryClicked();
public slots:
};

#endif // DASHBOARDPAGE_H
