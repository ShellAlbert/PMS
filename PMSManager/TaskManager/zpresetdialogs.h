#ifndef ZPRESETDIALOGS_H
#define ZPRESETDIALOGS_H
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QToolButton>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>
#include <QCloseEvent>
#include <QDebug>
//生产线/机器号 输入预置对话框
class ZProductLinePresetDialog:public QDialog
{
    Q_OBJECT
public:
    ZProductLinePresetDialog(QString refTemplateName,QWidget *parent=0);
    ~ZProductLinePresetDialog();

    QStringList ZReadList();
    QStringList ZGetList();
protected:
    QSize sizeHint() const;
    void closeEvent(QCloseEvent *e);
private slots:
    void ZSlotAdd();
    void ZSlotDel();
    void ZSlotReset();
    void ZSlotImport();
    void ZSlotExport();
    void ZSlotClickFill();
private:
    QListWidget *m_list;
    QToolButton *m_tbAdd;
    QToolButton *m_tbDel;
    QToolButton *m_tbReset;
    QToolButton *m_tbImport;
    QToolButton *m_tbExport;
    QToolButton *m_tbClickFill;
    QVBoxLayout *m_vLayoutBtn;
    QHBoxLayout *m_hLayout;
private:
    QString m_refTemplateName;
};
class ZProductLinePresetDialogXYList:public QDialog
{
    Q_OBJECT
public:
    ZProductLinePresetDialogXYList(QString refTemplateName,QWidget *parent=0);
    ~ZProductLinePresetDialogXYList();

    void ZPutList(QStringList xyList);
    QStringList ZGetList();
private slots:
    void ZSlotAdd();
    void ZSlotDel();
private:
    QLabel *m_llNotes;
    QListWidget *m_lstXY;
    QToolButton *m_tbAdd;
    QToolButton *m_tbDel;
    QVBoxLayout *m_vLayoutBtn;
    QHBoxLayout *m_hLayout;
    QVBoxLayout *m_vLayoutMain;
};
////////////////////////////////
/// \brief The ZProductLinePresetDialog class
//班组输入预置对话框
class ZClassPresetDialog:public QDialog
{
    Q_OBJECT
public:
    ZClassPresetDialog(QWidget *parent=0);
    ~ZClassPresetDialog();

    QStringList ZReadList();
    QStringList ZGetList();
protected:
    QSize sizeHint() const;
    void closeEvent(QCloseEvent *e);
private slots:
    void ZSlotAdd();
    void ZSlotDel();
    void ZSlotReset();
    void ZSlotImport();
    void ZSlotExport();
private:
    QListWidget *m_list;
    QToolButton *m_tbAdd;
    QToolButton *m_tbDel;
    QToolButton *m_tbReset;
    QToolButton *m_tbImport;
    QToolButton *m_tbExport;
    QVBoxLayout *m_vLayoutBtn;
    QHBoxLayout *m_hLayout;
};
//订单号输入预置对话框
class ZOrderNoPresetDialog:public QDialog
{
    Q_OBJECT
public:
    ZOrderNoPresetDialog(QString templateName,QWidget *parent=0);
    ~ZOrderNoPresetDialog();

    QStringList ZReadList();
    QStringList ZGetList();

    QStringList ZReadXYList();
    QStringList ZGetXYList();
protected:
    QSize sizeHint() const;
    void closeEvent(QCloseEvent *e);
private slots:
    void ZSlotAdd();
    void ZSlotDel();
    void ZSlotReset();
    void ZSlotImport();
    void ZSlotExport();

    void ZSlotAddXY();
    void ZSlotDelXY();
    void ZSlotResetXY();
private:
    QGroupBox *m_grpPreVal;
    QListWidget *m_list;
    QToolButton *m_tbAdd;
    QToolButton *m_tbDel;
    QToolButton *m_tbReset;
    QToolButton *m_tbImport;
    QToolButton *m_tbExport;
    QVBoxLayout *m_vLayoutBtn;
    QHBoxLayout *m_hLayoutGrp;

    QGroupBox *m_grpFillXY;
    QListWidget *m_xyList;
    QToolButton *m_tbAddXY;
    QToolButton *m_tbDelXY;
    QToolButton *m_tbResetXY;
    QVBoxLayout *m_vLayoutBtnXY;
    QHBoxLayout *m_hLayoutGrpXY;

    QHBoxLayout *m_hLayout;
private:
    QString m_relatedTemplate;
};
///产品编号预置输入对话框
class ZProductNoPresetDialog:public QDialog
{
    Q_OBJECT
public:
    ZProductNoPresetDialog(QString templateName,QWidget *parent=0);
    ~ZProductNoPresetDialog();

    void ZSetPreVal_XY_List(const QStringList &preValList,const QStringList &xyList);
    void ZGetPreVal_XY_List(QStringList &preValList,QStringList &xyList);
protected:
    QSize sizeHint() const;
private slots:
    void ZSlotAdd();
    void ZSlotDel();
    void ZSlotReset();
    void ZSlotImport();
    void ZSlotExport();

    void ZSlotAddXY();
    void ZSlotDelXY();
    void ZSlotResetXY();
private:
    QGroupBox *m_grpPreVal;
    QListWidget *m_list;
    QToolButton *m_tbAdd;
    QToolButton *m_tbDel;
    QToolButton *m_tbReset;
    QToolButton *m_tbImport;
    QToolButton *m_tbExport;
    QVBoxLayout *m_vLayoutBtn;
    QHBoxLayout *m_hLayoutGrp;

    QGroupBox *m_grpFillXY;
    QListWidget *m_xyList;
    QToolButton *m_tbAddXY;
    QToolButton *m_tbDelXY;
    QToolButton *m_tbResetXY;
    QVBoxLayout *m_vLayoutBtnXY;
    QHBoxLayout *m_hLayoutGrpXY;

    QHBoxLayout *m_hLayout;
private:
    QString m_relatedTemplate;
};

#endif // ZPRESETDIALOGS_H
