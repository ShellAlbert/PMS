#ifndef PFILEMANAGER_H
#define PFILEMANAGER_H

#include <QFrame>
#include <QToolButton>
#include <QTreeWidget>
#include <QTextEdit>
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "pgblpara.h"
#include <QLabel>
#include <QScrollArea>
class ZFileList:public QFrame
{
    Q_OBJECT
public:
    ZFileList(QWidget *parent=0);
    ~ZFileList();
public:
    QTreeWidget *m_treeWidget;
    QVBoxLayout *m_vLayout;
};
class ZImageViewer:public QFrame
{
    Q_OBJECT
public:
    ZImageViewer(QWidget *parent=0);
    ~ZImageViewer();
    void ZLoadPixmap(QPixmap pixmap);
private slots:
    void ZSlotZoomIn();
    void ZSlotZoomOut();
    void ZSlotZoomFit();
    void ZSlotRotate();
private:
    QToolButton *m_tbZoomIn;
    QToolButton *m_tbZoomOut;
    QToolButton *m_tbZoomFit;
    QToolButton *m_tbRotate;
    QHBoxLayout *m_hLayout;
    QPixmap m_pixmap;
    QLabel *m_llImg;
    QScrollArea *m_scrollArea;
    QVBoxLayout *m_vLayout;
    qint32 m_rotateIndex;
    qint32 m_imgWidth;
    qint32 m_imgHeight;
};
class PFileManager : public QFrame,public ZAckNetFrmWidget
{
    Q_OBJECT
public:
    PFileManager();
    ~PFileManager();

    void ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode);
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void ZSignalCloseEvent(QString widget);
    void ZSignalLogMsg(QString logMsg);
private slots:
    void ZSlotNewFolder();
    void ZSlotDelFolder();
    void ZSlotUploadFile();
    void ZSlotUploadPic();
    void ZSlotOpenFile();
    void ZSlotDelFile();
    void ZSlotExpandAll();
    void ZSlotHelp();
    void ZSlotCloseTabWidget(qint32 index);
private:
    void ZAddLogMsg(QString logMsg);
private:
    //left.
    QToolButton *m_tbNewFolder;
    QToolButton *m_tbDelFolder;
    QToolButton *m_tbUploadFile;
    QToolButton *m_tbUploadPic;

    QToolButton *m_tbOpenFile;
    QToolButton *m_tbDelFile;

    QToolButton *m_tbExpandAll;
    QToolButton *m_tbHelp;
    QVBoxLayout *m_vLayoutTb;
    //right.
    QTabWidget *m_tab;
    ZFileList *m_fileList;
    //main.
    QHBoxLayout *m_hLayoutMain;
};

#endif // PFILEMANAGER_H
