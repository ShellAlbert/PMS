#ifndef ZAUXSHEET_H
#define ZAUXSHEET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
class ZAuxSheet : public QWidget
{
    Q_OBJECT
public:
    explicit ZAuxSheet(QWidget *parent = 0);
    ~ZAuxSheet();

public:
    QString ZGetWorkShop();
    void ZSetWorkShop(QString workShop);

    QString ZGetWorkShift();
    void ZSetWorkShift(QString workShift);

    QString ZGetOrderNo();
    void ZSetOrderNo(QString orderNo);

    qint32 ZGetTaskState();
    void ZSetTaskState(qint32 taskState);

    //task creator.
    QString ZGetTaskCreator();
    void ZSetTaskCreator(QString taskCreator);
    //task checker.
    QString ZGetTaskChecker();
    void ZSetTaskChecker(QString taskChecker);
signals:
    void ZSignalDataChanged();
public slots:

private:
    QLabel *m_labelWorkShop;
    QLineEdit *m_lineEditWorkShop;
    QLabel *m_labelWorkShift;
    QLineEdit *m_lineEditWorkShift;
    QLabel *m_labelOrderNo;
    QLineEdit *m_lineEditOrderNo;

    QLabel *m_labelTaskState;
    qint32 m_taskState;
    //layout.
    QHBoxLayout *m_hLayout;

    //task auxili data.
    QString m_taskCreator;
    QString m_taskChecker;

};

#endif // ZAUXSHEET_H
