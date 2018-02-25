#ifndef PSTEPEDITOR_H
#define PSTEPEDITOR_H
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QToolButton>
#include <QGridLayout>
class PStepEditor : public QFrame
{
    Q_OBJECT
public:
    PStepEditor();
    ~PStepEditor();

    QString ZGetStepName();
    void ZSetStepName(QString stepName);

    QStringList ZGetLinkTemplates();
    void ZSetLinkTemplates(QStringList templates);

    QStringList ZGetLinkFiles();
    void ZSetLinkFiles(QStringList files);

    QStringList ZGetLinkRoles();
    void ZSetLinkRoles(QStringList roles);
private slots:
    void ZSlotCloseMe();
    void ZSlotAddLinkTemplate();
    void ZSlotDelLinkTemplate();
    void ZSlotAddLinkFile();
    void ZSlotDelLinkFile();
    void ZSlotAddLinkRole();
    void ZSlotDelLinkRole();
signals:
    void ZSignalCloseMe(PStepEditor *me);
    void ZSignalDataChanged();
private:
    //step name.
    QLabel *m_llStepName;
    QLineEdit *m_leStepName;
    QToolButton *m_tbClose;
    //link template.
    QLabel *m_llLinkTemplate;
    QListWidget *m_lwLinkTemplate;
    QToolButton *m_btnAddTemplate;
    QToolButton *m_btnDelTemplate;

    //link pdf files.
    QLabel *m_llLinkFiles;
    QListWidget *m_lwLinkFiles;
    QToolButton *m_btnAddFiles;
    QToolButton *m_btnDelFiles;

    //link roles.
    QLabel *m_lLinkRoles;
    QListWidget *m_lwLinkRoles;
    QToolButton *m_btnAddRoles;
    QToolButton *m_btnDelRoles;

    //layout.
    QGridLayout *m_gridLayout;
};

#endif // PSTEPEDITOR_H
