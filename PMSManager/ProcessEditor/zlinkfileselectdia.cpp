#include "zlinkfileselectdia.h"
#include <FileManager/zlistfolderfileinfodia.h>
#include <QMessageBox>
ZLinkFileSelectDia::ZLinkFileSelectDia(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("请选择需要关联的文件"));

    this->m_tree=new QTreeWidget;
    this->m_tree->setColumnCount(5);
    QStringList headerList;
    headerList<<tr("文件名");
    headerList<<tr("文件类型");
    headerList<<tr("文件大小");
    headerList<<tr("创建者");
    headerList<<tr("创建时间");
    this->m_tree->setHeaderLabels(headerList);

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Okay"));

    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_tbOkay);
    this->m_hLayout->addWidget(this->m_tbCancel);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_tree);
    this->m_vLayout->addLayout(this->m_hLayout);
    this->setLayout(this->m_vLayout);

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(accept()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));

    ZListFolderFileInfoDia *dia=new ZListFolderFileInfoDia(this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZExecuteListOp();
    dia->ZShowWaitingDialog();
}
ZLinkFileSelectDia::~ZLinkFileSelectDia()
{
    delete this->m_tree;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_hLayout;
    delete this->m_vLayout;
}
QSize ZLinkFileSelectDia::sizeHint() const
{
    return QSize(500,250);
}
void ZLinkFileSelectDia::ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode)
{
    if(item=="folder")
    {
        if(cmd=="list")
        {
            QString folderName=paraList.at(0);
            QString creator=paraList.at(1);
            QString createTime=paraList.at(2);
            if(ackNetRetCode<0)
            {
                //failed to list folder.
            }else{
                QTreeWidgetItem *folderItem=new QTreeWidgetItem(0);//type=0 is folder.type=1 is file.
                folderItem->setIcon(0,QIcon(":/FileManager/images/FileManager/Folder.png"));
                folderItem->setText(0,folderName);
                folderItem->setText(3,creator);
                folderItem->setText(4,createTime);
                this->m_tree->addTopLevelItem(folderItem);
                this->m_tree->setCurrentItem(folderItem);
            }
        }//list.
    }else if(item=="file")
    {
        if(cmd=="list")
        {
            QString fileName=paraList.at(0);
            QString folderName=paraList.at(1);
            QString fileType=paraList.at(2);
            qint32 fileSize=paraList.at(3).toInt();
            QString creator=paraList.at(4);
            QString createTime=paraList.at(5);
            if(ackNetRetCode<0)
            {
                //failed to list file.
            }else{
                for(qint32 i=0;i<this->m_tree->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *folderItem=this->m_tree->topLevelItem(i);
                    if(folderItem->text(0)==folderName)
                    {
                        QTreeWidgetItem *fileItem=new QTreeWidgetItem(1);//type=0 is folder.type=1 is file.
                        fileItem->setCheckState(0,Qt::Unchecked);
                        fileItem->setIcon(0,QIcon(":/FileManager/images/FileManager/PdfFile.png"));
                        fileItem->setText(0,fileName);
                        fileItem->setText(1,fileType);
                        fileItem->setText(2,QString("%1K").arg(fileSize/1024));
                        fileItem->setText(3,creator);
                        fileItem->setText(4,createTime);
                        folderItem->addChild(fileItem);
                        break;
                    }
                }
            }
        }
    }
}
QStringList ZLinkFileSelectDia::ZGetSelectedFileList()
{
    QStringList selectList;
    for(qint32 i=0;i<this->m_tree->topLevelItemCount();i++)
    {
        QTreeWidgetItem *folderItem=this->m_tree->topLevelItem(i);
        for(qint32 j=0;j<folderItem->childCount();j++)
        {
            QTreeWidgetItem *fileItem=folderItem->child(j);
            if(fileItem->checkState(0)==Qt::Checked)
            {
                selectList.append(folderItem->text(0)+"/"+fileItem->text(0));
            }
        }
    }
    return selectList;
}
