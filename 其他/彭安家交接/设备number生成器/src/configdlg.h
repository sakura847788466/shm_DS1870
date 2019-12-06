#ifndef CONFIGDLG_H
#define CONFIGDLG_H
#include <QDialog>

class QLineEdit;
class QPushButton;

class ConfigDlg : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigDlg(QWidget *parent = 0);

private:
    QLineEdit* _serverEdit;
    QLineEdit* _portEdit;
    QPushButton* _btnCancel;
    QPushButton* _btnConfig;
signals:

public slots:
    void onConfig();
};

#endif // CONFIGDLG_H
