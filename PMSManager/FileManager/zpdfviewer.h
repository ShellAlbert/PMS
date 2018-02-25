#ifndef ZPDFVIEWER_H
#define ZPDFVIEWER_H

#include <QWidget>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QScrollArea>
#include <QLabel>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QScrollBar>
#include <QToolButton>

#define USE_PDF     1

#ifdef USE_PDF
#include <FileManager/poppler/poppler-qt5.h>
#endif
class ZPdfViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ZPdfViewer(QWidget *parent = 0);
    ~ZPdfViewer();
signals:

public:
    //load hard disk's pdf file with absolute path.
    bool ZLoadPdfFile(QString fileName);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
private slots:
    void ZSlotFirstPage();
    void ZSlotPriorPage();
    void ZSlotNextPage();
    void ZSlotLastPage();
    void ZSlotScaleUp();
    void ZSlotScaleDown();
    void ZSlotScaleFit();
    void ZSlotLoadPdfPage(qint32 pageIndex);

    void ZSlotScrollBarValueChanged(int scrollBarValue);
private:
#ifdef USE_PDF
    Poppler::Document* m_document;
#endif
    //control buttons.
    //QComboBox.
    QComboBox *m_ComboBox;
    QToolButton *m_BtnFirstPage;
    QToolButton *m_BtnNextPage;
    QToolButton *m_BtnPriorPage;
    QToolButton *m_BtnLastPage;
    //scale.
    QToolButton *m_BtnScaleUp;
    QToolButton *m_BtnScaleDown;
    QToolButton *m_BtnScaleFit;
    QHBoxLayout *m_hlayoutTop;

    //vlayout main.
    QScrollArea *m_ScrollArea;
    QLabel *m_LabelImage;
    qint32 m_ImageFactor;
    QVBoxLayout *m_vlayoutMain;

    //pdf page releated.
    qint32 m_totalPages;
    qint32 m_currentPage;

    //left button was pressed.
    bool m_bLeftButtonPressed;
    QPoint m_OldPos;
    bool m_bCtrlButtonPressed;
};

#endif // ZPDFVIEWER_H
