#ifndef ZLISTFORMINFODIA_H
#define ZLISTFORMINFODIA_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QTextEdit>
#include <QToolButton>
#include "NetProtocol/pnetframe.h"
#include "BasePart/zbaseinfodia.h"
class ZListFormInfoDia : public ZBaseInfoDia
{
public:
    ZListFormInfoDia(QWidget *parent=0);
    ~ZListFormInfoDia();
    void ZExecuteListOp();
    void ZParseAckNetFrmXmlData();

private:
    QLabel *m_llMsg;
    QToolButton *m_tbOkay;
    QVBoxLayout *m_vLayout;
};
#endif // ZLISTFORMINFODIA_H
