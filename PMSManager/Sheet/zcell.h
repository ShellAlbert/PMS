#ifndef ZCELL_H
#define ZCELL_H

#include <QTableWidgetItem>
#include <QFont>
#include <QColor>
//QTableWidgetItem contains cellWidget.
//item(i,j)    cellWidget(i,j).
class ZCell : public QObject,public QTableWidgetItem
{
    Q_OBJECT
public:
    explicit ZCell();

public:
    void ZSetFont(QFont tFont);
    QFont ZGetFont();

    void ZSetForegroundColor(QColor fgColor);
    QColor ZGetForegroundColor();

    void ZSetBackgroundColor(QColor bgColor);
    QColor ZGetBackgroundColor();

    void ZSetDataType(QString dataType);
    QString ZGetDataType();
    void ZSetMinMaxToleranceValue(qint32 minValue,qint32 maxValue,qint32 toleranceValue);
    qint32 ZGetMinValue();
    qint32 ZGetMaxValue();
    qint32 ZGetToleranceValue();

    void ZSetCellData(QString data);
    QString ZGetCellData();
    
    //indicate this cell contains QLabel widget and has a picture.
    typedef enum{
        CellWidget_No=0,//no cell widget.
        CellWidget_QLabel=1,
        CellWidget_QLineEdit=2,
        CellWidget_QCheckBox=3,
        CellWidget_QComboBox=4,
        CellWidget_QDateTimeEdit=5,
        CellWidget_QSpinBox=6,
    }CellWidgetType;
    void ZSetCellWidgetType(CellWidgetType type);
    CellWidgetType ZGetCellWidgetType();

    //border frame.
    void ZSetTopFrame(bool bFrame);
    bool ZTopFrameIsSet();

    void ZSetBottomFrame(bool bFrame);
    bool ZBottomFrameIsSet();

    void ZSetLeftFrame(bool bFrame);
    bool ZLeftFrameIsSet();

    void ZSetRightFrame(bool bFrame);
    bool ZRightFrameIsSet();

    void ZSetFrameColor(QColor frameColor);
    QColor ZGetFrameColor();

    void ZSetFrameWidth(qint32 width);
    qint32 ZGetFrameWidth();


    void ZSetTextAlignment(qint32 textAlignment);
    qint32 ZGetTextAlignment();


    void ZSetLockCell(bool bLock);
    bool ZGetLockCell();

    //sign
    void ZSetCheckedSign(bool bLock);
    bool ZGetCheckedSign();

    ///////////////////////////////////////////////
    void ZSetBindVarName(QString varName);
    QString ZGetBindVarName();

signals:

public slots:

private:
    QString m_dataType;
    //for numeric data type.
    qint32 m_minValue;
    qint32 m_maxValue;
    qint32 m_toleranceValue;

    //border frame.
    bool m_bTopFrame;
    bool m_bBottomFrame;
    bool m_bLeftFrame;
    bool m_bRightFrame;
    bool m_bIsCheckedSign;
    QColor m_frameColor;
    qint32 m_frameWidth;

    CellWidgetType m_cellWidgetType;
    /////////////////////////////
    QString m_bindVarName;
};

#endif // ZCELL_H
