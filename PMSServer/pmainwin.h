#ifndef PMAINWIN_H
#define PMAINWIN_H

#include <QWidget>
#include <QLabel>
#include <QTreeWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QSplitter>
class PMainWin : public QWidget
{
    Q_OBJECT

public:
    PMainWin(QWidget *parent = 0);
    ~PMainWin();
public slots:
    void ZSlotShowLogMsg(QString logMsg);
    void ZSlotHeartBeat(QString addr,QString userName);
    void ZSlotUserLogin(QString addr,QString userName);
    void ZSlotUserLogout(QString addr,QString userName);
private:
    QLabel *m_llBanner;
    QTreeWidget *m_treeWidget;
    QTextEdit *m_textEdit;
    QSplitter *m_split;
    QVBoxLayout *m_vLayout;
};

#endif // PMAINWIN_H
