#ifndef ZUSERINFODIA_H
#define ZUSERINFODIA_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QToolButton>
#include <QGridLayout>
#include <QTreeWidget>
#include "NetProtocol/pnetframe.h"
#include "BasePart/zbaseinfodia.h"
class ZUserInfoDia : public ZBaseInfoDia
{
    Q_OBJECT
public:
    typedef enum{
        Type_NewUser=0,
        Type_MdyUser=1,
        Type_DelUser=2,
        Type_DelUserList=3,
    }UserInfoDiaType;

    ZUserInfoDia(UserInfoDiaType type,QWidget *parent=0);
    ~ZUserInfoDia();

    QString ZGetUserName();
    void ZSetUserName(QString userName);

    QString ZGetRealName();
    void ZSetRealName(QString realName);

    QString ZGetRoleName();
    void ZSetRoleName(QString roleName);

    qint32 ZGetSex();
    void ZSetSex(qint32 sex);

    QString ZGetPassword();
    void ZSetPassword(QString passwd);

    QString ZGetMobile();
    void ZSetMobile(QString mobile);

    void ZSetDelUserList(QString userName,QString roleName);
    qint32 ZGetDelUserListCount();

    void ZParseAckNetFrmXmlData();
private slots:
    void ZSlotOkay();
    void ZSlotCancel();
private:
    QLabel *m_lblUserName;
    QLineEdit *m_letUserName;

    QLabel *m_lblRealName;
    QLineEdit *m_letRealName;

    QLabel *m_lblGrps;
    QComboBox *m_cbbGrps;

    QLabel *m_lblSex;
    QRadioButton *m_rbMale;
    QRadioButton *m_rbFemale;
    QButtonGroup *m_brpSex;

    QLabel *m_lblPass;
    QLineEdit *m_letPass;

    QLabel *m_lblMobile;
    QLineEdit *m_letMobile;

    QTreeWidget *m_treeUserList;

    QToolButton *m_btnOkay;
    QToolButton *m_btnCancel;

    QGridLayout *m_gridLayout;

    UserInfoDiaType m_diaType;
};

#endif // ZUSERINFODIA_H
