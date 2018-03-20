/********************************************************************************
** Form generated from reading UI file 'tablebreakingdialogbase.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEBREAKINGDIALOGBASE_H
#define UI_TABLEBREAKINGDIALOGBASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TableBreakingSettingsDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QCheckBox *breakTables;
    QGroupBox *scalingBox;
    QGridLayout *gridLayout;
    QRadioButton *scaleFonts;
    QSpinBox *scalingFactor;
    QRadioButton *fit;
    QSpinBox *numHorizontalPages;
    QLabel *labelPagesH;
    QSpinBox *numVerticalPages;
    QLabel *labelPagesV;
    QGroupBox *pageOrderBox;
    QVBoxLayout *vboxLayout;
    QRadioButton *downThenRight;
    QRadioButton *rightThenDown;
    QGroupBox *tableSettingsGroupBox;
    QVBoxLayout *verticalLayout;
    QCheckBox *showHorizontalHeader;
    QCheckBox *showVerticalHeader;
    QCheckBox *showGrid;
    QSpacerItem *spacerItem;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TableBreakingSettingsDialog)
    {
        if (TableBreakingSettingsDialog->objectName().isEmpty())
            TableBreakingSettingsDialog->setObjectName(QStringLiteral("TableBreakingSettingsDialog"));
        TableBreakingSettingsDialog->resize(688, 533);
        verticalLayout_2 = new QVBoxLayout(TableBreakingSettingsDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        breakTables = new QCheckBox(TableBreakingSettingsDialog);
        breakTables->setObjectName(QStringLiteral("breakTables"));

        verticalLayout_2->addWidget(breakTables);

        scalingBox = new QGroupBox(TableBreakingSettingsDialog);
        scalingBox->setObjectName(QStringLiteral("scalingBox"));
        gridLayout = new QGridLayout(scalingBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        scaleFonts = new QRadioButton(scalingBox);
        scaleFonts->setObjectName(QStringLiteral("scaleFonts"));

        gridLayout->addWidget(scaleFonts, 0, 0, 1, 1);

        scalingFactor = new QSpinBox(scalingBox);
        scalingFactor->setObjectName(QStringLiteral("scalingFactor"));
        scalingFactor->setMaximum(10000);
        scalingFactor->setSingleStep(5);
        scalingFactor->setValue(100);

        gridLayout->addWidget(scalingFactor, 0, 3, 1, 1);

        fit = new QRadioButton(scalingBox);
        fit->setObjectName(QStringLiteral("fit"));

        gridLayout->addWidget(fit, 1, 0, 1, 1);

        numHorizontalPages = new QSpinBox(scalingBox);
        numHorizontalPages->setObjectName(QStringLiteral("numHorizontalPages"));
        numHorizontalPages->setMinimum(1);
        numHorizontalPages->setMaximum(10000);

        gridLayout->addWidget(numHorizontalPages, 1, 1, 1, 1);

        labelPagesH = new QLabel(scalingBox);
        labelPagesH->setObjectName(QStringLiteral("labelPagesH"));

        gridLayout->addWidget(labelPagesH, 1, 2, 1, 1);

        numVerticalPages = new QSpinBox(scalingBox);
        numVerticalPages->setObjectName(QStringLiteral("numVerticalPages"));
        numVerticalPages->setMinimum(1);
        numVerticalPages->setMaximum(10000);

        gridLayout->addWidget(numVerticalPages, 1, 3, 1, 1);

        labelPagesV = new QLabel(scalingBox);
        labelPagesV->setObjectName(QStringLiteral("labelPagesV"));

        gridLayout->addWidget(labelPagesV, 1, 4, 1, 1);


        verticalLayout_2->addWidget(scalingBox);

        pageOrderBox = new QGroupBox(TableBreakingSettingsDialog);
        pageOrderBox->setObjectName(QStringLiteral("pageOrderBox"));
        vboxLayout = new QVBoxLayout(pageOrderBox);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        downThenRight = new QRadioButton(pageOrderBox);
        downThenRight->setObjectName(QStringLiteral("downThenRight"));

        vboxLayout->addWidget(downThenRight);

        rightThenDown = new QRadioButton(pageOrderBox);
        rightThenDown->setObjectName(QStringLiteral("rightThenDown"));

        vboxLayout->addWidget(rightThenDown);


        verticalLayout_2->addWidget(pageOrderBox);

        tableSettingsGroupBox = new QGroupBox(TableBreakingSettingsDialog);
        tableSettingsGroupBox->setObjectName(QStringLiteral("tableSettingsGroupBox"));
        verticalLayout = new QVBoxLayout(tableSettingsGroupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        showHorizontalHeader = new QCheckBox(tableSettingsGroupBox);
        showHorizontalHeader->setObjectName(QStringLiteral("showHorizontalHeader"));

        verticalLayout->addWidget(showHorizontalHeader);

        showVerticalHeader = new QCheckBox(tableSettingsGroupBox);
        showVerticalHeader->setObjectName(QStringLiteral("showVerticalHeader"));

        verticalLayout->addWidget(showVerticalHeader);

        showGrid = new QCheckBox(tableSettingsGroupBox);
        showGrid->setObjectName(QStringLiteral("showGrid"));

        verticalLayout->addWidget(showGrid);


        verticalLayout_2->addWidget(tableSettingsGroupBox);

        spacerItem = new QSpacerItem(659, 81, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(spacerItem);

        buttonBox = new QDialogButtonBox(TableBreakingSettingsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(TableBreakingSettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TableBreakingSettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TableBreakingSettingsDialog, SLOT(reject()));
        QObject::connect(numVerticalPages, SIGNAL(valueChanged(QString)), fit, SLOT(click()));
        QObject::connect(scalingFactor, SIGNAL(valueChanged(QString)), scaleFonts, SLOT(click()));
        QObject::connect(numHorizontalPages, SIGNAL(valueChanged(int)), fit, SLOT(click()));

        QMetaObject::connectSlotsByName(TableBreakingSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *TableBreakingSettingsDialog)
    {
        TableBreakingSettingsDialog->setWindowTitle(QApplication::translate("TableBreakingSettingsDialog", "Table Breaking / Font Scaling", nullptr));
        breakTables->setText(QApplication::translate("TableBreakingSettingsDialog", "&Break tables over multiple pages in the horizontal direction", nullptr));
        scalingBox->setTitle(QApplication::translate("TableBreakingSettingsDialog", "Font scaling", nullptr));
        scaleFonts->setText(QApplication::translate("TableBreakingSettingsDialog", "Scale &fonts by", nullptr));
        scalingFactor->setSuffix(QApplication::translate("TableBreakingSettingsDialog", "%", nullptr));
        fit->setText(QApplication::translate("TableBreakingSettingsDialog", "&Scale to fit", nullptr));
        labelPagesH->setText(QApplication::translate("TableBreakingSettingsDialog", "page(s) wide", nullptr));
        labelPagesV->setText(QApplication::translate("TableBreakingSettingsDialog", "page(s) high", nullptr));
        pageOrderBox->setTitle(QApplication::translate("TableBreakingSettingsDialog", "Page order for table breaking", nullptr));
        downThenRight->setText(QApplication::translate("TableBreakingSettingsDialog", "Page &down, then to right", nullptr));
        rightThenDown->setText(QApplication::translate("TableBreakingSettingsDialog", "Page to &right, then down", nullptr));
        tableSettingsGroupBox->setTitle(QApplication::translate("TableBreakingSettingsDialog", "Table settings", nullptr));
        showHorizontalHeader->setText(QApplication::translate("TableBreakingSettingsDialog", "Show &horizontal header", nullptr));
        showVerticalHeader->setText(QApplication::translate("TableBreakingSettingsDialog", "Show &vertical header", nullptr));
        showGrid->setText(QApplication::translate("TableBreakingSettingsDialog", "Show &grid", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TableBreakingSettingsDialog: public Ui_TableBreakingSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEBREAKINGDIALOGBASE_H
