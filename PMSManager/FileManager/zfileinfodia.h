#ifndef ZFILEINFODIA_H
#define ZFILEINFODIA_H

#include "BasePart/zbaseinfodia.h"
#include <QToolButton>
#include <QLineEdit>
class ZFileInfoDia : public ZBaseInfoDia
{
    Q_OBJECT
public:
    typedef enum{
        Type_AddFile=0,
        Type_DelFile=1,
        Type_GetFile=2,
        Type_DwnData=3,
    }FileInfoDiaType;

    ZFileInfoDia(FileInfoDiaType type,QWidget *parent=0);
    ~ZFileInfoDia();

    void ZSetFolderName(QString folderName);
    QString ZGetFolderName();

    void ZSetFileName(QString fileName);
    QString ZGetFileName();

    void ZParseAckNetFrmXmlData();

    void ZDwnData(QString fileName,QString folderName,qint32 totalBlock,qint32 blockSize,qint32 remainBytes);
protected:
    QSize sizeHint() const;
private slots:
    void ZSlotOkay();
    void ZSlotCancel();
private:
    QLabel *m_llFolderName;
    QLineEdit *m_leFolderName;

    QLabel *m_llFileName;
    QLineEdit *m_leFileName;

    QToolButton *m_btnOkay;
    QToolButton *m_btnCancel;

    QGridLayout *m_gridLayout;

    FileInfoDiaType m_diaType;
};

#endif // ZFILEINFODIA_H
