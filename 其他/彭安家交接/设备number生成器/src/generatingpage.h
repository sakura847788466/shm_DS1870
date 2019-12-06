#ifndef GENERATINGPAGE_H
#define GENERATINGPAGE_H

class QLabel;
class GeneratingPage : public QWidget
{
    Q_OBJECT
public:
    explicit GeneratingPage(QWidget *parent = 0);
    void reset(QString what,ulong total);

    void hideEvent(QHideEvent * event);
private:
    QLabel* _whatLabel;
    QLabel* _percentLabel;
    QLabel* _indexLabel;
    QLabel* _totolLabel;

    ulong _index;
    ulong _total;
signals:

public slots:
    void onCallback(const QStringList&);
};

#endif // GENERATINGPAGE_H
