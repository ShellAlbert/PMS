#ifndef ZFOLDERINFODIA_H
#define ZFOLDERINFODIA_H

#include "BasePart/zbaseinfodia.h"
#include <QToolButton>
#include <QLineEdit>
class ZFolderInfoDia : public ZBaseInfoDia
{
    Q_OBJECT
public:
    typedef enum{
        Type_NewFolder=0,
        Type_DelFolder=1,
    }FolderInfoDiaType;
    ZFolderInfoDia(FolderInfoDiaType type,QWidget *parent=0);
    ~ZFolderInfoDia();

    void ZSetFolderName(QString name);
    QString ZGetFolderName();

    void ZParseAckNetFrmXmlData();
private slots:
    void ZSlotOkay();
    void ZSlotCancel();
private:
    QLabel *m_llFolderName;
    QLineEdit *m_leFolderName;

    QToolButton *m_btnOkay;
    QToolButton *m_btnCancel;

    QGridLayout *m_gridLayout;

    FolderInfoDiaType m_diaType;
};

#endif // ZFOLDERINFODIA_H
