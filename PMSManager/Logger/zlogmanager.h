#ifndef ZLOGMANAGER_H
#define ZLOGMANAGER_H

#include <QFrame>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QCloseEvent>
class ZLogManager : public QFrame
{
    Q_OBJECT
public:
    ZLogManager(QWidget *parent=0);
    ~ZLogManager();
protected:
    void closeEvent(QCloseEvent *event);
public slots:
    void ZSlotAddLogMsg(QString logMsg);
private:
    QTextEdit *m_textEdit;
    QVBoxLayout *m_vLayout;
};

#endif // ZLOGMANAGER_H
