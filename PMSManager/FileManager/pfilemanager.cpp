#include "pfilemanager.h"
#include <QDateTime>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "pgblpara.h"
#include "FileManager/zfolderinfodia.h"
#include "FileManager/zfileinfodia.h"
#include "FileManager/zlistfolderfileinfodia.h"
#include <FileManager/zpdfviewer.h>
ZFileList::ZFileList(QWidget *parent):QFrame(parent)
{
    this->m_treeWidget=new QTreeWidget;
    this->m_treeWidget->setIconSize(QSize(24,24));
    this->m_treeWidget->setColumnCount(5);
    QStringList headerList;
    headerList<<tr("文件名");
    headerList<<tr("文件类型");
    headerList<<tr("文件大小");
    headerList<<tr("创建者");
    headerList<<tr("创建时间");
    this->m_treeWidget->setHeaderLabels(headerList);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_treeWidget);
    this->setLayout(this->m_vLayout);
}
ZFileList::~ZFileList()
{
    delete this->m_treeWidget;
    delete this->m_vLayout;
}
ZImageViewer::ZImageViewer(QWidget *parent):QFrame(parent)
{
    this->m_tbZoomIn=new QToolButton;
    this->m_tbZoomIn->setText(tr("放大"));
    this->m_tbZoomIn->setIcon(QIcon(":/FileManager/images/FileManager/ZoomIn.png"));
    this->m_tbZoomIn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbZoomOut=new QToolButton;
    this->m_tbZoomOut->setText(tr("缩小"));
    this->m_tbZoomOut->setIcon(QIcon(":/FileManager/images/FileManager/ZoomOut.png"));
    this->m_tbZoomOut->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbZoomFit=new QToolButton;
    this->m_tbZoomFit->setText(tr("显示全部"));
    this->m_tbZoomFit->setIcon(QIcon(":/FileManager/images/FileManager/ZoomFit.png"));
    this->m_tbZoomFit->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbRotate=new QToolButton;
    this->m_tbRotate->setText(tr("旋转"));
    this->m_tbRotate->setIcon(QIcon(":/FileManager/images/FileManager/Rotate.png"));
    this->m_tbRotate->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_tbZoomFit);
    this->m_hLayout->addWidget(this->m_tbZoomIn);
    this->m_hLayout->addWidget(this->m_tbZoomOut);
    this->m_hLayout->addWidget(this->m_tbRotate);

    this->m_llImg=new QLabel;
    this->m_llImg->setAlignment(Qt::AlignCenter);
    this->m_scrollArea=new QScrollArea;
    this->m_scrollArea->setBackgroundRole(QPalette::Dark);
    this->m_scrollArea->setWidget(this->m_llImg);
    this->m_scrollArea->setFocusPolicy(Qt::NoFocus);
    this->m_scrollArea->setWidgetResizable(true);
    this->m_scrollArea->setVisible(true);
    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addLayout(this->m_hLayout);
    this->m_vLayout->addWidget(this->m_scrollArea);
    this->setLayout(this->m_vLayout);

    this->m_rotateIndex=0;

    connect(this->m_tbZoomFit,SIGNAL(clicked(bool)),this,SLOT(ZSlotZoomFit()));
    connect(this->m_tbZoomIn,SIGNAL(clicked(bool)),this,SLOT(ZSlotZoomIn()));
    connect(this->m_tbZoomOut,SIGNAL(clicked(bool)),this,SLOT(ZSlotZoomOut()));
    connect(this->m_tbRotate,SIGNAL(clicked(bool)),this,SLOT(ZSlotRotate()));
}
ZImageViewer::~ZImageViewer()
{
    delete this->m_tbRotate;
    delete this->m_tbZoomOut;
    delete this->m_tbZoomIn;
    delete this->m_tbZoomFit;
    delete this->m_hLayout;
    delete this->m_llImg;
    delete this->m_scrollArea;
    delete this->m_vLayout;
}
void ZImageViewer::ZLoadPixmap(QPixmap pixmap)
{
    this->m_pixmap=pixmap;
    this->m_llImg->setPixmap(pixmap);
    this->m_imgWidth=pixmap.width();
    this->m_imgHeight=pixmap.height();
}
void ZImageViewer::ZSlotZoomIn()
{
    this->m_imgWidth*=2;
    this->m_imgHeight*=2;
    QPixmap pixmap=this->m_pixmap.scaled(this->m_imgWidth,this->m_imgHeight,Qt::KeepAspectRatio);
    this->m_llImg->setPixmap(pixmap);
}
void ZImageViewer::ZSlotZoomOut()
{
    this->m_imgWidth/=2;
    this->m_imgHeight/=2;
    QPixmap pixmap=this->m_pixmap.scaled(this->m_imgWidth,this->m_imgHeight,Qt::KeepAspectRatio);
    this->m_llImg->setPixmap(pixmap);
}
void ZImageViewer::ZSlotZoomFit()
{
    this->m_imgHeight=this->m_pixmap.height();
    this->m_imgWidth=this->m_pixmap.width();
    this->m_llImg->setPixmap(this->m_pixmap);
}
void ZImageViewer::ZSlotRotate()
{
    QMatrix matrix;
    matrix.rotate(90*this->m_rotateIndex++);
    if(this->m_rotateIndex==4)
    {
        this->m_rotateIndex=0;
    }
    QPixmap pixmap=this->m_pixmap.transformed(matrix,Qt::SmoothTransformation);
    this->m_llImg->setPixmap(pixmap);
}
PFileManager::PFileManager()
{
    this->setWindowTitle(tr("文件管理器-File Manager"));
    this->setWindowIcon(QIcon(":/TaskBar/images/FileManager.png"));
//    this->setStyleSheet("QToolButton{background-color:#cce5f9;font:color #eaf7ff;padding: 6px 12px 6px 12p}"
//                        "QToolButton::hover{background-color:#eaf7ff;}"
//                        "");

    this->setStyleSheet("QToolButton{background-color:#cce5f9;border:none;font:color #eaf7ff;}"
                        "QToolButton::hover{background-color:#eaf7ff;}"
                        "");
    //left.
    this->m_vLayoutTb=new QVBoxLayout;
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_fileManagerPerm&PermBits_FileManager_NewFolder)
    {
        this->m_tbNewFolder=new QToolButton;
        this->m_tbNewFolder->setToolTip(tr("新建文件夹"));
        this->m_tbNewFolder->setText(tr("新建"));
        this->m_tbNewFolder->setIcon(QIcon(":/FileManager/images/FileManager/NewFolder.png"));
        this->m_tbNewFolder->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutTb->addWidget(this->m_tbNewFolder);
        connect(this->m_tbNewFolder,SIGNAL(clicked(bool)),this,SLOT(ZSlotNewFolder()));
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_fileManagerPerm&PermBits_FileManager_DelFolder)
    {
        this->m_tbDelFolder=new QToolButton;
        this->m_tbDelFolder->setToolTip(tr("删除文件夹"));
        this->m_tbDelFolder->setText(tr("删除"));
        this->m_tbDelFolder->setIcon(QIcon(":/FileManager/images/FileManager/DelFolder.png"));
        this->m_tbDelFolder->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutTb->addWidget(this->m_tbDelFolder);
        connect(this->m_tbDelFolder,SIGNAL(clicked(bool)),this,SLOT(ZSlotDelFolder()));
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_fileManagerPerm&PermBits_FileManager_UploadFile)
    {
        this->m_tbUploadFile=new QToolButton;
        this->m_tbUploadFile->setToolTip(tr("上传文件"));
        this->m_tbUploadFile->setText(tr("文件"));
        this->m_tbUploadFile->setIcon(QIcon(":/FileManager/images/FileManager/UpFile.png"));
        this->m_tbUploadFile->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutTb->addWidget(this->m_tbUploadFile);
        connect(this->m_tbUploadFile,SIGNAL(clicked(bool)),this,SLOT(ZSlotUploadFile()));

        this->m_tbUploadPic=new QToolButton;
        this->m_tbUploadPic->setToolTip(tr("上传图片"));
        this->m_tbUploadPic->setText(tr("图片"));
        this->m_tbUploadPic->setIcon(QIcon(":/FileManager/images/FileManager/UpPic.png"));
        this->m_tbUploadPic->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutTb->addWidget(this->m_tbUploadPic);
        connect(this->m_tbUploadPic,SIGNAL(clicked(bool)),this,SLOT(ZSlotUploadPic()));
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_fileManagerPerm&PermBits_FileManager_DownloadFile)
    {
        this->m_tbOpenFile=new QToolButton;
        this->m_tbOpenFile->setToolTip(tr("下载文件"));
        this->m_tbOpenFile->setText(tr("下载"));
        this->m_tbOpenFile->setIcon(QIcon(":/FileManager/images/FileManager/DwnFile.png"));
        this->m_tbOpenFile->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutTb->addWidget(this->m_tbOpenFile);
        connect(this->m_tbOpenFile,SIGNAL(clicked(bool)),this,SLOT(ZSlotOpenFile()));
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_fileManagerPerm&PermBits_FileManager_DelFile)
    {
        this->m_tbDelFile=new QToolButton;
        this->m_tbDelFile->setToolTip(tr("删除文件"));
        this->m_tbDelFile->setText(tr("删除"));
        this->m_tbDelFile->setIcon(QIcon(":/FileManager/images/FileManager/DelFile.png"));
        this->m_tbDelFile->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutTb->addWidget(this->m_tbDelFile);
        connect(this->m_tbDelFile,SIGNAL(clicked(bool)),this,SLOT(ZSlotDelFile()));
    }

    this->m_tbExpandAll=new QToolButton;
    this->m_tbExpandAll->setToolTip(tr("全部展开"));
    this->m_tbExpandAll->setText(tr("展开"));
    this->m_tbExpandAll->setIcon(QIcon(":/FileManager/images/FileManager/Expand.png"));
    this->m_tbExpandAll->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(this->m_tbExpandAll,SIGNAL(clicked(bool)),this,SLOT(ZSlotExpandAll()));
    this->m_vLayoutTb->addStretch(1);
    this->m_vLayoutTb->addWidget(this->m_tbExpandAll);

    //help.
    this->m_tbHelp=new QToolButton;
    this->m_tbHelp->setToolTip(tr("获取帮助文档"));
    this->m_tbHelp->setText(tr("帮助"));
    this->m_tbHelp->setIcon(QIcon(":/common/images/common/help.png"));
    this->m_tbHelp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(this->m_tbHelp,SIGNAL(clicked(bool)),this,SLOT(ZSlotHelp()));
    this->m_vLayoutTb->addWidget(this->m_tbHelp);

    //right.
    this->m_tab=new QTabWidget;
    this->m_tab->setTabsClosable(true);
    this->m_fileList=new ZFileList;
    this->m_tab->addTab(this->m_fileList,QIcon(":/FileManager/images/FileManager/FileList.png"),tr("文件列表"));
    connect(this->m_tab,SIGNAL(tabCloseRequested(int)),this,SLOT(ZSlotCloseTabWidget(qint32)));

    //main.
    this->m_hLayoutMain=new QHBoxLayout;
    this->m_hLayoutMain->addLayout(this->m_vLayoutTb);
    this->m_hLayoutMain->addWidget(this->m_tab);
    this->setLayout(this->m_hLayoutMain);

    ZListFolderFileInfoDia *dia=new ZListFolderFileInfoDia(this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZExecuteListOp();
    dia->ZShowWaitingDialog();
}
PFileManager::~PFileManager()
{
    //left.
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_fileManagerPerm&PermBits_FileManager_NewFolder)
    {
        delete this->m_tbNewFolder;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_fileManagerPerm&PermBits_FileManager_DelFolder)
    {
        delete this->m_tbDelFolder;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_fileManagerPerm&PermBits_FileManager_UploadFile)
    {
        delete this->m_tbUploadFile;
        delete this->m_tbUploadPic;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_fileManagerPerm&PermBits_FileManager_DownloadFile)
    {
        delete this->m_tbOpenFile;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_fileManagerPerm&PermBits_FileManager_DelFile)
    {
        delete this->m_tbDelFile;
    }
    delete this->m_tbExpandAll;
    delete this->m_tbHelp;
    delete this->m_vLayoutTb;
    //right.
    delete this->m_fileList;
    delete this->m_tab;
    //main.
    delete this->m_hLayoutMain;
}
void PFileManager::ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode)
{
    if(item=="folder")
    {
        if(cmd=="add")
        {
            QString folderName=paraList.at(0);
            QString errMsg=paraList.at(1);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("add folder [%1] failed:[%2].").arg(folderName).arg(errMsg));
            }else{
                QTreeWidgetItem *folderItem=new QTreeWidgetItem(0);//type=0 is folder.type=1 is file.
                folderItem->setIcon(0,QIcon(":/FileManager/images/FileManager/Folder.png"));
                folderItem->setText(0,folderName);
                this->m_fileList->m_treeWidget->addTopLevelItem(folderItem);
                this->m_fileList->m_treeWidget->setCurrentItem(folderItem);
                this->ZAddLogMsg(tr("add folder [%1] success.").arg(folderName));
            }
        }else if(cmd=="del")
        {
            QString folderName=paraList.at(0);
            QString errMsg=paraList.at(1);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("delete folder [%1] failed:[%2].").arg(folderName).arg(errMsg));
            }else{
                //delete folderItem from treeWidget.
                for(qint32 i=0;i<this->m_fileList->m_treeWidget->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *folderItem=this->m_fileList->m_treeWidget->topLevelItem(i);
                    if(folderItem->type()==0 && folderItem->text(0)==folderName)
                    {
                        this->m_fileList->m_treeWidget->takeTopLevelItem(i);
                        delete folderItem;
                        folderItem=NULL;
                    }
                }
                this->ZAddLogMsg(tr("delete folder [%1] success.").arg(folderName));
            }
        }else if(cmd=="list")
        {
            QString folderName=paraList.at(0);
            QString creator=paraList.at(1);
            QString createTime=paraList.at(2);
            QTreeWidgetItem *folderItem=new QTreeWidgetItem(0);//type=0 is folder.type=1 is file.
            folderItem->setIcon(0,QIcon(":/FileManager/images/FileManager/Folder.png"));
            folderItem->setText(0,folderName);
            folderItem->setText(3,creator);
            folderItem->setText(4,createTime);
            this->m_fileList->m_treeWidget->addTopLevelItem(folderItem);
            this->m_fileList->m_treeWidget->setCurrentItem(folderItem);
            this->ZAddLogMsg(tr("list folder [%1] success.").arg(folderName));
        }
    }else if(item=="file")
    {
        if(cmd=="add")
        {
            if(ackNetRetCode<0)
            {
                QString fileName=paraList.at(0);
                QString errMsg=paraList.at(1);
                this->ZAddLogMsg(tr("upload file [%1] failed:[%2].").arg(fileName).arg(errMsg));
            }else{
                QString fileName=paraList.at(0);
                QString folderName=paraList.at(1);
                QString fileType=paraList.at(2);
                QString fileSize=paraList.at(3);
                QString creator=paraList.at(4);
                for(qint32 i=0;i<this->m_fileList->m_treeWidget->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *folderItem=this->m_fileList->m_treeWidget->topLevelItem(i);
                    if(folderItem->text(0)==folderName)
                    {
                        QTreeWidgetItem *fileItem=new QTreeWidgetItem(1);//type=0 is folder.type=1 is file.
                        if(fileType=="pdf")
                        {
                            fileItem->setIcon(0,QIcon(":/FileManager/images/FileManager/PdfFile.png"));
                        }else if(fileType=="png"||fileType=="jpg")
                        {
                            fileItem->setIcon(0,QIcon(":/FileManager/images/FileManager/ImageFile.png"));
                        }
                        fileItem->setText(0,fileName);
                        fileItem->setText(1,fileType);
                        fileItem->setText(2,QString("%1 KB").arg(fileSize.toInt()/1024));
                        fileItem->setText(3,creator);
                        fileItem->setText(4,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                        folderItem->addChild(fileItem);
                        this->m_fileList->m_treeWidget->setCurrentItem(fileItem);
                        this->ZAddLogMsg(tr("upload file [%1] success.").arg(fileName));
                        break;
                    }
                }
            }
        }else if(cmd=="updata")
        {
            if(ackNetRetCode<0)
            {
                QString fileName=paraList.at(0);
                QString errMsg=paraList.at(1);
                this->ZAddLogMsg(tr("upload file [%1] failed:[%2].").arg(fileName).arg(errMsg));
            }else{
                QString fileName=paraList.at(0);
                this->ZAddLogMsg(tr("upload file [%1] success.").arg(fileName));
            }
        }else if(cmd=="del")
        {
            QString folderName=paraList.at(0);
            QString fileName=paraList.at(1);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("delete file [%1] failed.").arg(fileName));
            }else{
                for(qint32 i=0;i<this->m_fileList->m_treeWidget->topLevelItemCount();i++)
                {
                    bool bDeleteOk=false;
                    QTreeWidgetItem *folderItem=this->m_fileList->m_treeWidget->topLevelItem(i);
                    if(folderItem->text(0)==folderName)
                    {
                        for(qint32 j=0;j<folderItem->childCount();j++)
                        {
                            QTreeWidgetItem *fileItem=folderItem->child(j);
                            if(fileItem->text(0)==fileName)
                            {
                                folderItem->removeChild(fileItem);
                                delete fileItem;
                                fileItem=NULL;
                                bDeleteOk=true;
                                break;
                            }
                        }
                    }
                    if(bDeleteOk)
                    {
                        break;
                    }
                }
                this->ZAddLogMsg(tr("delete file [%1] success.").arg(fileName));
            }
        }else if(cmd=="get")
        {
            if(ackNetRetCode<0)
            {
                QString fileName=paraList.at(0);
                QString errMsg=paraList.at(1);
                this->ZAddLogMsg(tr("get file [%1] failed:%2.").arg(fileName).arg(errMsg));
            }else{
                QString fileName=paraList.at(0);
                QString folderName=paraList.at(1);
                QString fileType=paraList.at(2);
                qint32 totalBlock=paraList.at(3).toInt();
                qint32 blockSize=paraList.at(4).toInt();
                qint32 remainBytes=paraList.at(5).toInt();
                if(totalBlock<=0 && remainBytes<=0)
                {
                    QMessageBox::critical(this,tr("下载错误"),tr("下载文件错误!\n服务器返回文件信息错误!"));
                }else{
                    this->ZAddLogMsg(tr("get file [%1]-block[%2-%3] success.").arg(fileName).arg(totalBlock).arg(remainBytes));

                    ZFileInfoDia *dia=new ZFileInfoDia(ZFileInfoDia::Type_GetFile,this);
                    dia->ZSetAckNetFrmProcessWidget(this);
                    dia->ZSetFolderName(folderName);
                    dia->ZSetFileName(fileName);
                    dia->ZDwnData(fileName,folderName,totalBlock,blockSize,remainBytes);
                    dia->ZShowWaitingDialog();
                }
            }
        }else if(cmd=="dwndata")
        {
            QString fileName=paraList.at(0);
            QString folderName=paraList.at(1);
            qint32 totalBlock=paraList.at(2).toInt();
            qint32 currentBlock=paraList.at(3).toInt();
            QString data=paraList.at(4);
            //write file to local cache dir.
            QString filePath(QDir::currentPath()+"/cache/file/"+folderName);
            QDir dir;
            dir.mkpath(filePath);
            QFile file(filePath+"/"+fileName);
            if(file.open(QIODevice::WriteOnly|QIODevice::Append))
            {
                QByteArray fileDataArray=QByteArray::fromBase64(data.toUtf8());
                qDebug()<<"recv file data:"<<fileDataArray.size();
                file.write(fileDataArray);
                file.close();
            }
            if(totalBlock==currentBlock)
            {
                QString fileType=fileName.right(3).toLower();
                if(fileType=="pdf")
                {
                    ZPdfViewer *pdfView=new ZPdfViewer;
                    pdfView->ZLoadPdfFile(filePath+"/"+fileName);
                    this->m_tab->addTab(pdfView,QIcon(":/FileManager/images/FileManager/PdfFile.png"),fileName);
                    this->m_tab->setCurrentWidget(pdfView);
                }else if(fileType=="png" ||fileType=="jpg")
                {
                    ZImageViewer *imgView=new ZImageViewer;
                    imgView->ZLoadPixmap(QPixmap(filePath+"/"+fileName));
                    this->m_tab->addTab(imgView,QIcon(":/FileManager/images/FileManager/ImageFile.png"),fileName);
                    this->m_tab->setCurrentWidget(imgView);
                }
            }
        }else if(cmd=="list")
        {
            QString fileName=paraList.at(0);
            QString folderName=paraList.at(1);
            QString fileType=paraList.at(2);
            qint32 fileSize=paraList.at(3).toInt();
            QString creator=paraList.at(4);
            QString createTime=paraList.at(5);
            for(qint32 i=0;i<this->m_fileList->m_treeWidget->topLevelItemCount();i++)
            {
                QTreeWidgetItem *folderItem=this->m_fileList->m_treeWidget->topLevelItem(i);
                if(folderItem->text(0)==folderName)
                {
                    QTreeWidgetItem *fileItem=new QTreeWidgetItem(1);//type=0 is folder.type=1 is file.
                    if(fileType=="pdf")
                    {
                        fileItem->setIcon(0,QIcon(":/FileManager/images/FileManager/PdfFile.png"));
                    }else if(fileType=="png"||fileType=="jpg")
                    {
                        fileItem->setIcon(0,QIcon(":/FileManager/images/FileManager/ImageFile.png"));
                    }
                    fileItem->setText(0,fileName);
                    fileItem->setText(1,fileType);
                    fileItem->setText(2,QString("%1K").arg(fileSize/1024));
                    fileItem->setText(3,creator);
                    fileItem->setText(4,createTime);
                    folderItem->addChild(fileItem);
                    break;
                }
            }
            for(qint32 i=0;i<this->m_fileList->m_treeWidget->columnCount();i++)
            {
                this->m_fileList->m_treeWidget->resizeColumnToContents(i);
            }
        }
    }
}
void PFileManager::ZSlotNewFolder()
{
    if(this->m_tab->currentIndex()!=0)
    {
        return;
    }

    ZFolderInfoDia *dia=new ZFolderInfoDia(ZFolderInfoDia::Type_NewFolder,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PFileManager::ZSlotDelFolder()
{
    if(this->m_tab->currentIndex()!=0)
    {
        return;
    }
    QTreeWidgetItem *item=this->m_fileList->m_treeWidget->currentItem();
    if(!item)
    {
        return;
    }
    if(item->type()!=0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请选择需要删除的文件夹!\n当前选择项为非文件夹!"));
        return;
    }
    if(item->childCount()>0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("无法删除文件夹[%1]!\n该文件夹包含文件,数目:[%2]!").arg(item->text(0)).arg(item->childCount()));
        return;
    }
    if(QMessageBox::question(this,tr("操作确认"),tr("您确认要删除文件夹[%1]吗?").arg(item->text(0)),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        ZFolderInfoDia *dia=new ZFolderInfoDia(ZFolderInfoDia::Type_DelFolder,this);
        dia->ZSetAckNetFrmProcessWidget(this);
        dia->ZSetFolderName(item->text(0));
        if(dia->exec()==QDialog::Accepted)
        {
            dia->ZShowWaitingDialog();
        }
    }
}
void PFileManager::ZSlotUploadFile()
{
    if(this->m_tab->currentIndex()!=0)
    {
        return;
    }

    QTreeWidgetItem *folderItem=this->m_fileList->m_treeWidget->currentItem();
    if(folderItem==NULL)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请先选择要将文件上传到的文件夹!"));
        return;
    }
    if(folderItem->type()!=0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请先选择要将文件上传到的文件夹!\n当前选择项为非文件夹!"));
        return;
    }
    QString filePath=QFileDialog::getOpenFileName(this,tr("请选择需要上传的文件"),".",tr("Pdf(*.pdf)"));
    if(filePath.isEmpty())
    {
        return;
    }
    ZFileInfoDia *dia=new ZFileInfoDia(ZFileInfoDia::Type_AddFile,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetFolderName(folderItem->text(0));
    dia->ZSetFileName(filePath);
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PFileManager::ZSlotUploadPic()
{
    if(this->m_tab->currentIndex()!=0)
    {
        return;
    }

    QTreeWidgetItem *folderItem=this->m_fileList->m_treeWidget->currentItem();
    if(folderItem==NULL)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请先选择要将图片上传到的文件夹!"));
        return;
    }
    if(folderItem->type()!=0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请先选择要将图片上传到的文件夹!\n当前选择项为非文件夹!"));
        return;
    }
    QString filePath=QFileDialog::getOpenFileName(this,tr("请选择需要上传的文件"),".",tr("Images(*.png *.jpg)"));
    if(filePath.isEmpty())
    {
        return;
    }
    ZFileInfoDia *dia=new ZFileInfoDia(ZFileInfoDia::Type_AddFile,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetFolderName(folderItem->text(0));
    dia->ZSetFileName(filePath);
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PFileManager::ZSlotOpenFile()
{
    if(this->m_tab->currentIndex()!=0)
    {
        return;
    }

    QTreeWidgetItem *fileItem=this->m_fileList->m_treeWidget->currentItem();
    if(fileItem==NULL)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请选择要下载的文件!"));
        return;
    }
    if(fileItem->type()!=1)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请选择要下载的文件!\n当前选择项为非文件!"));
        return;
    }
    ZFileInfoDia *dia=new ZFileInfoDia(ZFileInfoDia::Type_GetFile,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetFolderName(fileItem->parent()->text(0));
    dia->ZSetFileName(fileItem->text(0));
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PFileManager::ZSlotDelFile()
{
    if(this->m_tab->currentIndex()!=0)
    {
        return;
    }

    QTreeWidgetItem *fileItem=this->m_fileList->m_treeWidget->currentItem();
    if(fileItem==NULL)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请选择要删除的文件!"));
        return;
    }
    if(fileItem->type()!=1)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请选择需要删除的文件!\n当前选择项为非文件!"));
        return;
    }
    if(QMessageBox::question(this,tr("操作确认"),tr("您确认要删除文件[%1]吗?").arg(fileItem->text(0)),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        ZFileInfoDia *dia=new ZFileInfoDia(ZFileInfoDia::Type_DelFile,this);
        dia->ZSetAckNetFrmProcessWidget(this);
        dia->ZSetFolderName(fileItem->parent()->text(0));
        dia->ZSetFileName(fileItem->text(0));
        if(dia->exec()==QDialog::Accepted)
        {
            dia->ZShowWaitingDialog();
        }
    }
}
void PFileManager::ZSlotExpandAll()
{
    if(this->m_tab->currentIndex()!=0)
    {
        return;
    }
    this->m_fileList->m_treeWidget->expandAll();
}
void PFileManager::ZSlotHelp()
{

}
void PFileManager::closeEvent(QCloseEvent *event)
{
    emit this->ZSignalCloseEvent("FileManager");
    QFrame::closeEvent(event);
}
void PFileManager::ZAddLogMsg(QString logMsg)
{
    emit this->ZSignalLogMsg(QString("<FileManager>:")+logMsg);
}
void PFileManager::ZSlotCloseTabWidget(qint32 index)
{
    //tab0 is never close.
    if(index==0)
    {
        return;
    }
    //delete it to remove it from tab widget.
    this->m_tab->removeTab(index);
    delete this->m_tab->widget(index);
}
