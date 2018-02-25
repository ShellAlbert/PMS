#ifndef ZSYSPICDIA_H
#define ZSYSPICDIA_H

#include <QDialog>
#include <QLabel>
#include <QListWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
class ZSysPicDia : public QDialog
{
    Q_OBJECT
public:
    ZSysPicDia(QString prefix,QWidget *parent=0);
    ~ZSysPicDia();

    QString ZGetSelectedPic();
private slots:
    void ZSlotOkay();
    void ZSlotCancel();
private:
    void ZLoadSysPic(QString prefix);
private:
    QLabel *m_llPicPath;
    QListWidget *m_listWidget;
    QToolButton *m_btnOkay;
    QToolButton *m_btnCancel;
    QHBoxLayout *m_hLayoutBtn;
    QVBoxLayout *m_vLayoutMain;
    QString m_pathPrefix;
};

#endif // ZSYSPICDIA_H
