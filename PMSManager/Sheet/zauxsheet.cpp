#include "zauxsheet.h"

ZAuxSheet::ZAuxSheet(QWidget *parent) :
    QWidget(parent)
{
    this->m_labelWorkShop=new QLabel(tr("Work Shop"));
    this->m_lineEditWorkShop=new QLineEdit;
    this->m_lineEditWorkShop->setMaxLength(64);

    this->m_labelWorkShift=new QLabel(tr("Work Shift"));
    this->m_lineEditWorkShift=new QLineEdit;
    this->m_lineEditWorkShift->setMaxLength(64);

    this->m_labelOrderNo=new QLabel(tr("Order No."));
    this->m_lineEditOrderNo=new QLineEdit;
    this->m_lineEditOrderNo->setMaxLength(64);

    //task state.
    this->m_labelTaskState=new QLabel;
    this->m_labelTaskState->setObjectName("ZAuxSheetTaskStateLabel");
    //layout.
    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_labelWorkShop);
    this->m_hLayout->addWidget(this->m_lineEditWorkShop);
    this->m_hLayout->addWidget(this->m_labelWorkShift);
    this->m_hLayout->addWidget(this->m_lineEditWorkShift);
    this->m_hLayout->addWidget(this->m_labelOrderNo);
    this->m_hLayout->addWidget(this->m_lineEditOrderNo);
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_labelTaskState);
    this->setLayout(this->m_hLayout);

    //signals to notify data changed.
    connect(this->m_lineEditWorkShop,SIGNAL(textChanged(QString)),this,SIGNAL(ZSignalDataChanged()));
    connect(this->m_lineEditWorkShift,SIGNAL(textChanged(QString)),this,SIGNAL(ZSignalDataChanged()));
    connect(this->m_lineEditOrderNo,SIGNAL(textChanged(QString)),this,SIGNAL(ZSignalDataChanged()));
}
ZAuxSheet::~ZAuxSheet()
{
    delete this->m_labelWorkShop;
    delete this->m_lineEditWorkShop;
    delete this->m_labelWorkShift;
    delete this->m_lineEditWorkShift;
    delete this->m_labelOrderNo;
    delete this->m_lineEditOrderNo;
    delete this->m_labelTaskState;
    delete this->m_hLayout;
}
QString ZAuxSheet::ZGetWorkShop()
{
    return this->m_lineEditWorkShop->text();
}
void ZAuxSheet::ZSetWorkShop(QString workShop)
{
    this->m_lineEditWorkShop->setText(workShop);
}

QString ZAuxSheet::ZGetWorkShift()
{
    return this->m_lineEditWorkShift->text();
}

void ZAuxSheet::ZSetWorkShift(QString workShift)
{
    this->m_lineEditWorkShift->setText(workShift);
}

QString ZAuxSheet::ZGetOrderNo()
{
    return this->m_lineEditOrderNo->text();
}
void ZAuxSheet::ZSetOrderNo(QString orderNo)
{
    this->m_lineEditOrderNo->setText(orderNo);
}
qint32 ZAuxSheet::ZGetTaskState()
{
    return this->m_taskState;
}
void ZAuxSheet::ZSetTaskState(qint32 taskState)
{
    QString tCurrentTaskState;
    if(0==taskState)
    {
        tCurrentTaskState=QString("Not Saved");
    }
    else if(1==taskState)
    {
        tCurrentTaskState=QString("Not Submit");
    }else if(2==taskState)
    {
        tCurrentTaskState=QString("Waiting Check");
    }else if(3==taskState)
    {
       tCurrentTaskState=QString("Check Pass");
    }else if(4==taskState)
    {
        tCurrentTaskState=QString("Check Failed");
    }
    this->m_labelTaskState->setText(tCurrentTaskState);
    this->m_taskState=taskState;
}
//task creator.
QString ZAuxSheet::ZGetTaskCreator()
{
    return this->m_taskCreator;
}
void ZAuxSheet::ZSetTaskCreator(QString taskCreator)
{
    this->m_taskCreator=taskCreator;
}
//task checker.
QString ZAuxSheet::ZGetTaskChecker()
{
    return this->m_taskChecker;
}
void ZAuxSheet::ZSetTaskChecker(QString taskChecker)
{
    this->m_taskChecker=taskChecker;
}
