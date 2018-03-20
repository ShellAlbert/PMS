/********************************************************************************
** Form generated from reading UI file 'previewdialogbase.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREVIEWDIALOGBASE_H
#define UI_PREVIEWDIALOGBASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreviewWidgetBase
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *actionBar;
    QHBoxLayout *horizontalLayout;
    QToolButton *firstPage;
    QToolButton *prevPage;
    QLineEdit *pageNumber;
    QLabel *pageCount;
    QToolButton *nextPage;
    QToolButton *lastPage;
    QFrame *line;
    QToolButton *zoomIn;
    QComboBox *zoomCombo;
    QToolButton *zoomOut;
    QSpacerItem *spacerItem;
    QLabel *labelPaperSize;
    QComboBox *paperSizeCombo;
    QLabel *labelOrientation;
    QComboBox *paperOrientationCombo;
    QSpacerItem *spacerItem1;
    QPushButton *tableBreakingButton;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *pageList;
    QScrollArea *previewArea;

    void setupUi(QWidget *PreviewWidgetBase)
    {
        if (PreviewWidgetBase->objectName().isEmpty())
            PreviewWidgetBase->setObjectName(QStringLiteral("PreviewWidgetBase"));
        PreviewWidgetBase->resize(1292, 629);
        verticalLayout = new QVBoxLayout(PreviewWidgetBase);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        actionBar = new QWidget(PreviewWidgetBase);
        actionBar->setObjectName(QStringLiteral("actionBar"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(actionBar->sizePolicy().hasHeightForWidth());
        actionBar->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(actionBar);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        firstPage = new QToolButton(actionBar);
        firstPage->setObjectName(QStringLiteral("firstPage"));
        firstPage->setToolTipDuration(2);
        QIcon icon;
        icon.addFile(QStringLiteral(":/FormDesigner/images/FormDesigner/2leftarrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        firstPage->setIcon(icon);
        firstPage->setIconSize(QSize(22, 22));
        firstPage->setAutoRaise(true);

        horizontalLayout->addWidget(firstPage);

        prevPage = new QToolButton(actionBar);
        prevPage->setObjectName(QStringLiteral("prevPage"));
        prevPage->setToolTipDuration(2);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/FormDesigner/images/FormDesigner/1leftarrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        prevPage->setIcon(icon1);
        prevPage->setIconSize(QSize(22, 22));
        prevPage->setAutoRaise(true);

        horizontalLayout->addWidget(prevPage);

        pageNumber = new QLineEdit(actionBar);
        pageNumber->setObjectName(QStringLiteral("pageNumber"));
        pageNumber->setMaxLength(10);
        pageNumber->setAlignment(Qt::AlignHCenter);

        horizontalLayout->addWidget(pageNumber);

        pageCount = new QLabel(actionBar);
        pageCount->setObjectName(QStringLiteral("pageCount"));

        horizontalLayout->addWidget(pageCount);

        nextPage = new QToolButton(actionBar);
        nextPage->setObjectName(QStringLiteral("nextPage"));
        nextPage->setToolTipDuration(2);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/FormDesigner/images/FormDesigner/1rightarrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        nextPage->setIcon(icon2);
        nextPage->setIconSize(QSize(22, 22));
        nextPage->setAutoRaise(true);

        horizontalLayout->addWidget(nextPage);

        lastPage = new QToolButton(actionBar);
        lastPage->setObjectName(QStringLiteral("lastPage"));
        lastPage->setToolTipDuration(2);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/FormDesigner/images/FormDesigner/2rightarrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        lastPage->setIcon(icon3);
        lastPage->setIconSize(QSize(22, 22));
        lastPage->setAutoRaise(true);

        horizontalLayout->addWidget(lastPage);

        line = new QFrame(actionBar);
        line->setObjectName(QStringLiteral("line"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        zoomIn = new QToolButton(actionBar);
        zoomIn->setObjectName(QStringLiteral("zoomIn"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/FormDesigner/images/FormDesigner/zoom+.png"), QSize(), QIcon::Normal, QIcon::Off);
        zoomIn->setIcon(icon4);
        zoomIn->setIconSize(QSize(22, 22));
        zoomIn->setAutoRaise(true);

        horizontalLayout->addWidget(zoomIn);

        zoomCombo = new QComboBox(actionBar);
        zoomCombo->setObjectName(QStringLiteral("zoomCombo"));

        horizontalLayout->addWidget(zoomCombo);

        zoomOut = new QToolButton(actionBar);
        zoomOut->setObjectName(QStringLiteral("zoomOut"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/FormDesigner/images/FormDesigner/zoom-.png"), QSize(), QIcon::Normal, QIcon::Off);
        zoomOut->setIcon(icon5);
        zoomOut->setIconSize(QSize(22, 22));
        zoomOut->setAutoRaise(true);

        horizontalLayout->addWidget(zoomOut);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacerItem);

        labelPaperSize = new QLabel(actionBar);
        labelPaperSize->setObjectName(QStringLiteral("labelPaperSize"));

        horizontalLayout->addWidget(labelPaperSize);

        paperSizeCombo = new QComboBox(actionBar);
        paperSizeCombo->setObjectName(QStringLiteral("paperSizeCombo"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(paperSizeCombo->sizePolicy().hasHeightForWidth());
        paperSizeCombo->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(paperSizeCombo);

        labelOrientation = new QLabel(actionBar);
        labelOrientation->setObjectName(QStringLiteral("labelOrientation"));

        horizontalLayout->addWidget(labelOrientation);

        paperOrientationCombo = new QComboBox(actionBar);
        paperOrientationCombo->setObjectName(QStringLiteral("paperOrientationCombo"));
        sizePolicy2.setHeightForWidth(paperOrientationCombo->sizePolicy().hasHeightForWidth());
        paperOrientationCombo->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(paperOrientationCombo);

        spacerItem1 = new QSpacerItem(101, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacerItem1);

        tableBreakingButton = new QPushButton(actionBar);
        tableBreakingButton->setObjectName(QStringLiteral("tableBreakingButton"));

        horizontalLayout->addWidget(tableBreakingButton);


        verticalLayout->addWidget(actionBar);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pageList = new QListWidget(PreviewWidgetBase);
        pageList->setObjectName(QStringLiteral("pageList"));

        horizontalLayout_2->addWidget(pageList);

        previewArea = new QScrollArea(PreviewWidgetBase);
        previewArea->setObjectName(QStringLiteral("previewArea"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(previewArea->sizePolicy().hasHeightForWidth());
        previewArea->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(previewArea);


        verticalLayout->addLayout(horizontalLayout_2);

#ifndef QT_NO_SHORTCUT
        labelPaperSize->setBuddy(paperSizeCombo);
        labelOrientation->setBuddy(paperOrientationCombo);
#endif // QT_NO_SHORTCUT

        retranslateUi(PreviewWidgetBase);

        QMetaObject::connectSlotsByName(PreviewWidgetBase);
    } // setupUi

    void retranslateUi(QWidget *PreviewWidgetBase)
    {
        PreviewWidgetBase->setWindowTitle(QApplication::translate("PreviewWidgetBase", "Print Preview", nullptr));
#ifndef QT_NO_TOOLTIP
        firstPage->setToolTip(QApplication::translate("PreviewWidgetBase", "\347\254\254\344\270\200\351\241\265", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        firstPage->setWhatsThis(QApplication::translate("PreviewWidgetBase", "Goes to the first page", nullptr));
#endif // QT_NO_WHATSTHIS
        firstPage->setText(QApplication::translate("PreviewWidgetBase", "\347\254\254\344\270\200\351\241\265", nullptr));
#ifndef QT_NO_TOOLTIP
        prevPage->setToolTip(QApplication::translate("PreviewWidgetBase", "\345\211\215\344\270\200\351\241\265", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        prevPage->setWhatsThis(QApplication::translate("PreviewWidgetBase", "Goes to the previous page", nullptr));
#endif // QT_NO_WHATSTHIS
        prevPage->setText(QApplication::translate("PreviewWidgetBase", "\345\211\215\344\270\200\351\241\265", nullptr));
        pageNumber->setText(QApplication::translate("PreviewWidgetBase", "1", nullptr));
        pageCount->setText(QApplication::translate("PreviewWidgetBase", "/ 10", nullptr));
#ifndef QT_NO_TOOLTIP
        nextPage->setToolTip(QApplication::translate("PreviewWidgetBase", "\344\270\213\344\270\200\351\241\265", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        nextPage->setWhatsThis(QApplication::translate("PreviewWidgetBase", "Goes to the next page", nullptr));
#endif // QT_NO_WHATSTHIS
        nextPage->setText(QApplication::translate("PreviewWidgetBase", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        lastPage->setToolTip(QApplication::translate("PreviewWidgetBase", "\346\234\200\345\220\216\344\270\200\351\241\265", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        lastPage->setWhatsThis(QApplication::translate("PreviewWidgetBase", "Goes to the last page", nullptr));
#endif // QT_NO_WHATSTHIS
        lastPage->setText(QApplication::translate("PreviewWidgetBase", "\346\234\200\345\220\216\344\270\200\351\241\265", nullptr));
        zoomIn->setText(QApplication::translate("PreviewWidgetBase", "...", nullptr));
        zoomOut->setText(QApplication::translate("PreviewWidgetBase", "...", nullptr));
        labelPaperSize->setText(QApplication::translate("PreviewWidgetBase", "\347\272\270\345\274\240\345\244\247\345\260\217:", nullptr));
        labelOrientation->setText(QApplication::translate("PreviewWidgetBase", "\347\272\270\345\274\240\346\226\271\345\220\221:", nullptr));
        tableBreakingButton->setText(QApplication::translate("PreviewWidgetBase", "\350\256\276\347\275\256...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PreviewWidgetBase: public Ui_PreviewWidgetBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREVIEWDIALOGBASE_H
