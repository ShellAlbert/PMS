#ifndef ZGRPINFODIA_H
#define ZGRPINFODIA_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QTextEdit>
#include <QToolButton>
#include <QListWidget>
#include <QStackedWidget>
#include <QSplitter>
#include "NetProtocol/pnetframe.h"
#include "BasePart/zbaseinfodia.h"
class ZUserManagerPerm:public QFrame
{
public:
    ZUserManagerPerm();
    ~ZUserManagerPerm();

    void ZSetPermBits(qint32 permBits);
    qint32 ZGetPermBits();
private:
    QCheckBox *m_cbNewGrp;
    QCheckBox *m_cbMdyGrp;
    QCheckBox *m_cbDelGrp;

    QCheckBox *m_cbNewUser;
    QCheckBox *m_cbMdyUser;
    QCheckBox *m_cbDelUser;

    QCheckBox *m_cbImport;
    QCheckBox *m_cbExport;

    QGridLayout *m_gridLayout;
};
class ZTemplateEditorPerm:public QFrame
{
public:
    ZTemplateEditorPerm();
    ~ZTemplateEditorPerm();

    void ZSetPermBits(qint32 permBits);
    qint32 ZGetPermBits();
private:
    QCheckBox *m_cbNewTem;
    QCheckBox *m_cbMdyTem;
    QCheckBox *m_cbDelTem;

    QCheckBox *m_cbNewVarSrc;
    QCheckBox *m_cbMdyVarSrc;
    QCheckBox *m_cbDelVarSrc;

    QCheckBox *m_cbImport;
    QCheckBox *m_cbExport;

    QGridLayout *m_gridLayout;
};
class ZFileManagerPerm:public QFrame
{
public:
    ZFileManagerPerm();
    ~ZFileManagerPerm();

    void ZSetPermBits(qint32 permBits);
    qint32 ZGetPermBits();
private:
    QCheckBox *m_cbNewFolder;
    QCheckBox *m_cbDelFolder;

    QCheckBox *m_cbUploadFile;
    QCheckBox *m_cbDownloadFile;
    QCheckBox *m_cbDelFile;

    QGridLayout *m_gridLayout;
};
class ZProcessEditorPerm:public QFrame
{
public:
    ZProcessEditorPerm();
    ~ZProcessEditorPerm();

    void ZSetPermBits(qint32 permBits);
    qint32 ZGetPermBits();
private:
    QCheckBox *m_cbNewProcess;
    QCheckBox *m_cbMdyProcess;
    QCheckBox *m_cbDelProcess;

    QGridLayout *m_gridLayout;
};
class ZTaskManagerPerm:public QFrame
{
public:
    ZTaskManagerPerm();
    ~ZTaskManagerPerm();

    void ZSetPermBits(qint32 permBits);
    qint32 ZGetPermBits();
private:
    QCheckBox *m_cbNewTask;
    QCheckBox *m_cbMdyTask;
    QCheckBox *m_cbDelTask;

    QGridLayout *m_gridLayout;
};
class ZFormDesignerPerm:public QFrame
{
public:
    ZFormDesignerPerm();
    ~ZFormDesignerPerm();

    void ZSetPermBits(qint32 permBits);
    qint32 ZGetPermBits();
private:
    QCheckBox *m_cbNewForm;
    QCheckBox *m_cbMdyForm;
    QCheckBox *m_cbDelForm;

    QGridLayout *m_gridLayout;
};
class ZGrpInfoDia : public ZBaseInfoDia
{
    Q_OBJECT
public:
    typedef enum{
        Type_NewGrp=0,
        Type_MdyGrp=1,
        Type_DelGrp=2,
    }GrpInfoDiaType;
    ZGrpInfoDia(GrpInfoDiaType type,QWidget *parent=0);
    ~ZGrpInfoDia();

    QString ZGetParentName();
    void ZSetParentName(QString name);

    QString ZGetGrpName();
    void ZSetGrpName(QString name);

    QString ZGetPermBits();
    void ZSetPermBits(QString permBits);

    QString ZGetGrpMemo();
    void ZSetGrpMemo(QString memo);

    void ZParseAckNetFrmXmlData();
private slots:
    void ZSlotOkay();
    void ZSlotCancel();
    void ZSlotShowParts(qint32 index);
protected:
    QSize sizeHint() const;
private:

    QLabel *m_lblParentName;
    QLineEdit *m_letParentName;

    QLabel *m_lblGrpName;
    QLineEdit *m_letGrpName;

    QListWidget *m_listWidget;
    QStackedWidget *m_stackedWidget;
    QSplitter *m_spliter;

    QLabel *m_lblGrpMemo;
    QTextEdit *m_tetGrpMemo;

    QToolButton *m_btnOKay;
    QToolButton *m_btnCancel;

    QGridLayout *m_gridLayout;

    GrpInfoDiaType m_diaType;


private:
    ZUserManagerPerm *m_userManagerPerm;
    ZTemplateEditorPerm *m_templateEditorPerm;
    ZFileManagerPerm *m_fileManagerPerm;
    ZProcessEditorPerm *m_processEditorPerm;
    ZTaskManagerPerm *m_taskManagerPerm;
    ZFormDesignerPerm *m_formDesignerPerm;

};

#endif // ZGRPINFODIA_H
