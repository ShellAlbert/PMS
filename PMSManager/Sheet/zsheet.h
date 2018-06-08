#ifndef ZSHEET_H
#define ZSHEET_H
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFont>
#include <QDebug>
#include <Sheet/zcelldelegate.h>
#include <Sheet/zcell.h>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#define TABLE_ROW_COUNT 100
#define TABLE_COL_COUNT 50
class ZSheet : public QTableWidget
{
    Q_OBJECT
public:
    typedef enum{
        SheetState_Saved=0,//the sheet was saved yet.
        SheetState_NotSave=1,//the sheet was new,not saved yet.
    }ZSheetState;

    ZSheet(QWidget *parent=0);
    ~ZSheet();

public:
    QString ZGetProcessName();
    void ZSetProcessName(QString processName);
    QString ZGetStepName();
    void ZSetStepName(QString stepName);

    QString ZGetTemplateName();
    void ZSetTemplateName(QString templateName);

    QString ZGetSheetName();
    void ZSetSheetName(QString sheetName);

    ZSheetState ZGetSheetState();
    void ZSetSheetState(ZSheetState sheetState);

    //cell delegate.
    ZCellDelegate* ZGetCellDelegate();

    //load template sheet xml.
    bool ZLoadTemplateSheetByName(QString templateName);

    //pic convet
    QString PixMapToString(const QPixmap&);
    QPixmap StringToPixMap(const QString&);
    //for print html.
    QString ZGetPrintHtml();

    ///////////////////////////////////
    QString ZGetDestMinMaxXmlData();
    void ZSetDestMinMaxXmlData(QString pairXml);

    ///////////////////////////////////////////////
    QString ZGetPreSetProductNo();
    void ZSetPreSetProductNo(QString productNo);

    QString ZGetXYAutoFillProductNo();
    void ZSetXYAutoFillProductNo(QString productNo);

private slots:
    void ZSlotItemEntered();
    void ZSlotHAlignLeft();
    void ZSlotHAlignCenter();
    void ZSlotHAlignRight();
    void ZSlotVAlignTop();
    void ZSlotVAlignCenter();
    void ZSlotVAlignBottom();
    void ZSlotMerge();
    void ZSlotSplit();
    void ZSlotFastRemoveWidget();
    void ZSlotRemoveWidget();
    void ZSlotMutexManager();
    void ZSlotMinMaxDataCompare();
    void ZSlotAutoFillProductNo();
    void ZSlotDeleteRows();
    void ZSlotDeleteCols();
    void ZSlotInsertRows();
    void ZSlotInsertCols();

    void ZSlotHighlightCell(QString destCell,QString minCell,QString maxCell);
signals:
    void ZSignalSheetChanged(QString templateName);
    void ZSignalBindVar();
    void ZSignalUnbindVar();

    void ZSigIncBindXWhenAddRow(qint32 nX);
    void ZSigIncBindYWhenAddCol(qint32 nY);

    void ZSigDecBindXWhenDelRow(qint32 nX);
    void ZSigDecBindYWhenDelCol(qint32 nY);
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    QString m_processName;
    QString m_stepName;
    QString m_templateName;
    QString m_sheetName;

    //sheet type.
    ZSheetState m_sheetState;

    //item delegate.
    ZCellDelegate *m_cellDelegate;

    //right menu.
    QMenu *m_popupMenu;

    QAction *m_actBindVar;
    QAction *m_actUnbindVar;

    QMenu *m_subMenuAlign;
    QAction *m_actionHAlignLeft;
    QAction *m_actionHAlignCenter;
    QAction *m_actionHAlignRight;

    QAction *m_actionVAlignTop;
    QAction *m_actionVAlignCenter;
    QAction *m_actionVAlignBottom;

    QAction *m_actionMerge;
    QAction *m_actionSplit;

    QAction *m_actFastRemoveWidget;
    QAction *m_actRemoveWidget;

    QAction *m_actMutexManagr;
    QAction *m_actMinMaxDataCompare;
    QAction *m_actAutoFillProductNo;

    QMenu *m_subMenuRowCol;
    QAction *m_actDeleteRows;
    QAction *m_actDeleteCols;
    QAction *m_actInsertRows;
    QAction *m_actInsertCols;

private:
    //for min/max data compare.
    QStringList m_destMinMaxPair;

private:
    QStringList m_xyAutoFillProductNoList;
    QStringList m_preSetProductNoList;
};


#endif // ZSHEET_H
