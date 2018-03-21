/*
SQLyog v10.2 
MySQL - 5.5.56 : Database - pms
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`pms` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE `pms`;

/*Table structure for table `加固外壳检查单_data` */

DROP TABLE IF EXISTS `加固外壳检查单_data`;

CREATE TABLE `加固外壳检查单_data` (
  `TaskName` varchar(45) NOT NULL,
  `width` int(11) DEFAULT NULL,
  `height` int(11) DEFAULT NULL,
  `sno` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`TaskName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `加固外壳检查单_data` */

insert  into `加固外壳检查单_data`(`TaskName`,`width`,`height`,`sno`) values ('admin-加固外壳检查表-20180227215248',13,33,'370682198709012312');

/*Table structure for table `月末绩效检查单_data` */

DROP TABLE IF EXISTS `月末绩效检查单_data`;

CREATE TABLE `月末绩效检查单_data` (
  `TaskName` varchar(45) NOT NULL,
  `username` varchar(45) DEFAULT NULL,
  `group` varchar(45) DEFAULT NULL,
  `alldays` int(11) DEFAULT NULL,
  `restdays` int(11) DEFAULT NULL,
  `xishu` int(11) DEFAULT NULL,
  `wanchenglv` int(11) DEFAULT NULL,
  `leader` varchar(45) DEFAULT NULL,
  `filldate` datetime DEFAULT NULL,
  `t1` int(11) DEFAULT NULL,
  `t2` int(11) DEFAULT NULL,
  `t3` int(11) DEFAULT NULL,
  `t4` int(11) DEFAULT NULL,
  PRIMARY KEY (`TaskName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `月末绩效检查单_data` */

insert  into `月末绩效检查单_data`(`TaskName`,`username`,`group`,`alldays`,`restdays`,`xishu`,`wanchenglv`,`leader`,`filldate`,`t1`,`t2`,`t3`,`t4`) values ('admin-月末绩效检查单-20180310114126','zhangshaoyan','101',103,4,1,1,'任大炮','2018-03-17 00:00:00',1,2,3,4),('zhangshaoyan-月末绩效检查单-20180320095537','张绍言','3年2班',103,23,23,22,'研究院','2018-03-20 00:00:00',45,30,55,40);

/*Table structure for table `backupinfo` */

DROP TABLE IF EXISTS `backupinfo`;

CREATE TABLE `backupinfo` (
  `BackupName` varchar(64) NOT NULL,
  `FileSize` int(11) DEFAULT NULL,
  `Creator` varchar(64) DEFAULT NULL,
  `CreateTime` datetime DEFAULT NULL,
  PRIMARY KEY (`BackupName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `backupinfo` */

insert  into `backupinfo`(`BackupName`,`FileSize`,`Creator`,`CreateTime`) values ('20180310132631',15796,'admin','2018-03-10 13:26:31'),('20180320160207',20979,'admin','2018-03-20 16:02:07');

/*Table structure for table `fileinfo` */

DROP TABLE IF EXISTS `fileinfo`;

CREATE TABLE `fileinfo` (
  `FileName` varchar(64) NOT NULL,
  `FolderName` varchar(64) DEFAULT NULL,
  `FileType` varchar(8) DEFAULT NULL,
  `FileSize` int(11) DEFAULT NULL,
  `Creator` varchar(64) DEFAULT NULL,
  `CreateTime` datetime DEFAULT NULL,
  PRIMARY KEY (`FileName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `fileinfo` */

insert  into `fileinfo`(`FileName`,`FolderName`,`FileType`,`FileSize`,`Creator`,`CreateTime`) values ('BlockDiagramOfLaserSpyDeviceV0.1.pdf','GongYiFile','pdf',376094,'admin','2018-02-27 21:02:58'),('RF射频同轴连接器MCX-KHD.png','国标GB2003','png',142008,'admin','2018-02-27 17:17:56'),('微信图片_20170822110036.jpg','工艺文件集合','jpg',50760,'admin','2018-02-27 17:17:50');

/*Table structure for table `folderinfo` */

DROP TABLE IF EXISTS `folderinfo`;

CREATE TABLE `folderinfo` (
  `FolderName` varchar(64) NOT NULL,
  `Creator` varchar(64) DEFAULT NULL,
  `CreateTime` datetime DEFAULT NULL,
  PRIMARY KEY (`FolderName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `folderinfo` */

insert  into `folderinfo`(`FolderName`,`Creator`,`CreateTime`) values ('GongYiFile','admin','2018-02-27 21:02:46'),('国标GB2003','admin','2018-02-27 17:17:16'),('工艺文件集合','admin','2018-02-27 17:17:08');

/*Table structure for table `forminfo` */

DROP TABLE IF EXISTS `forminfo`;

CREATE TABLE `forminfo` (
  `FormName` varchar(64) NOT NULL,
  `FileSize` int(11) DEFAULT NULL,
  `Creator` varchar(64) DEFAULT NULL,
  `CreateTime` datetime DEFAULT NULL,
  PRIMARY KEY (`FormName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `forminfo` */

insert  into `forminfo`(`FormName`,`FileSize`,`Creator`,`CreateTime`) values ('form2',0,'admin','2018-03-11 10:34:29'),('form3',0,'admin','2018-03-11 10:34:34'),('form4',0,'admin','2018-03-11 10:34:39'),('form5',0,'admin','2018-03-11 10:34:44'),('检查单1',390,'admin','2018-03-11 10:32:07');

/*Table structure for table `processinfo` */

DROP TABLE IF EXISTS `processinfo`;

CREATE TABLE `processinfo` (
  `ProcessName` varchar(64) NOT NULL,
  `StepNum` int(11) DEFAULT NULL,
  `Creator` varchar(64) DEFAULT NULL,
  `CreateTime` datetime DEFAULT NULL,
  PRIMARY KEY (`ProcessName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `processinfo` */

insert  into `processinfo`(`ProcessName`,`StepNum`,`Creator`,`CreateTime`) values ('hanjie',2,'admin','2018-02-27 20:59:58'),('外壳加工',2,'admin','2018-02-27 21:01:11'),('管道焊接',2,'admin','2018-02-27 21:00:38'),('阻抗测试',0,'admin','2018-02-27 21:01:24');

/*Table structure for table `roleinfo` */

DROP TABLE IF EXISTS `roleinfo`;

CREATE TABLE `roleinfo` (
  `RoleName` varchar(64) NOT NULL,
  `PermBits` varchar(64) NOT NULL,
  `RoleMemo` varchar(512) DEFAULT NULL,
  `Creator` varchar(64) NOT NULL,
  `CreateTime` datetime NOT NULL,
  PRIMARY KEY (`RoleName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `roleinfo` */

insert  into `roleinfo`(`RoleName`,`PermBits`,`RoleMemo`,`Creator`,`CreateTime`) values ('1admin','255,255,255,255,255,255','PMS Initial Created','admin','2018-02-26 20:32:11'),('admin','255,255,255,255,255,255','nothing','admin','2018-02-26 20:32:11'),('班长组','255,255,31,7,7,7','生产线上的班长组，拥有高一级权限','admin','2018-03-11 10:52:38'),('生产员工组','0,0,0,0,6,7','','admin','2018-03-06 15:31:29');

/*Table structure for table `stepinfo` */

DROP TABLE IF EXISTS `stepinfo`;

CREATE TABLE `stepinfo` (
  `No` int(11) NOT NULL AUTO_INCREMENT,
  `StepName` varchar(64) DEFAULT NULL,
  `ProcessName` varchar(64) DEFAULT NULL,
  `LinkTemplates` varchar(256) DEFAULT NULL,
  `LinkFiles` varchar(256) DEFAULT NULL,
  `LinkRoles` varchar(256) DEFAULT NULL,
  PRIMARY KEY (`No`)
) ENGINE=InnoDB AUTO_INCREMENT=41 DEFAULT CHARSET=utf8;

/*Data for the table `stepinfo` */

insert  into `stepinfo`(`No`,`StepName`,`ProcessName`,`LinkTemplates`,`LinkFiles`,`LinkRoles`) values (6,'初步尺寸测量','管道焊接','template1',NULL,NULL),(7,'初步尺寸测量','管道焊接',NULL,'GongYiFile/BlockDiagramOfLaserSpyDeviceV0.1.pdf',NULL),(8,'初步尺寸测量','管道焊接',NULL,NULL,'admin'),(9,'初步尺寸测量','管道焊接',NULL,NULL,'管理员'),(10,'焊锡预估','管道焊接','template1',NULL,NULL),(11,'焊锡预估','管道焊接',NULL,'GongYiFile/BlockDiagramOfLaserSpyDeviceV0.1.pdf',NULL),(12,'焊锡预估','管道焊接',NULL,'国标GB2003/RF射频同轴连接器MCX-KHD.png',NULL),(13,'焊锡预估','管道焊接',NULL,NULL,'管理员'),(21,'step-1','外壳加工','加固外壳检查表',NULL,NULL),(22,'step-1','外壳加工',NULL,'国标GB2003/RF射频同轴连接器MCX-KHD.png',NULL),(23,'step-1','外壳加工',NULL,'工艺文件集合/微信图片_20170822110036.jpg',NULL),(24,'step-1','外壳加工',NULL,NULL,'管理员'),(25,'step-1','外壳加工',NULL,NULL,'admin'),(26,'step-2','外壳加工','加固外壳检查表',NULL,NULL),(27,'step-2','外壳加工',NULL,'GongYiFile/BlockDiagramOfLaserSpyDeviceV0.1.pdf',NULL),(28,'step-2','外壳加工',NULL,NULL,'管理员'),(29,'step-2','外壳加工',NULL,NULL,'admin'),(30,'step-1','hanjie','加固外壳检查表',NULL,NULL),(31,'step-1','hanjie','月末绩效检查单',NULL,NULL),(32,'step-1','hanjie',NULL,'GongYiFile/BlockDiagramOfLaserSpyDeviceV0.1.pdf',NULL),(33,'step-1','hanjie',NULL,'国标GB2003/RF射频同轴连接器MCX-KHD.png',NULL),(34,'step-1','hanjie',NULL,'工艺文件集合/微信图片_20170822110036.jpg',NULL),(35,'step-1','hanjie',NULL,NULL,'班长组'),(36,'step-1','hanjie',NULL,NULL,'生产员工组'),(37,'step-2','hanjie','月末绩效检查单',NULL,NULL),(38,'step-2','hanjie',NULL,'工艺文件集合/微信图片_20170822110036.jpg',NULL),(39,'step-2','hanjie',NULL,NULL,'班长组'),(40,'step-2','hanjie',NULL,NULL,'生产员工组');

/*Table structure for table `taskinfo` */

DROP TABLE IF EXISTS `taskinfo`;

CREATE TABLE `taskinfo` (
  `TaskName` varchar(64) NOT NULL,
  `RefProcess` varchar(64) DEFAULT NULL,
  `RefStep` varchar(64) DEFAULT NULL,
  `RefTemplate` varchar(64) DEFAULT NULL,
  `TaskState` int(11) DEFAULT NULL,
  `Creator` varchar(64) DEFAULT NULL,
  `CreateTime` datetime DEFAULT NULL,
  `Checker` varchar(64) DEFAULT NULL,
  `CheckTime` datetime DEFAULT NULL,
  PRIMARY KEY (`TaskName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `taskinfo` */

insert  into `taskinfo`(`TaskName`,`RefProcess`,`RefStep`,`RefTemplate`,`TaskState`,`Creator`,`CreateTime`,`Checker`,`CheckTime`) values ('admin-template1-20180228150635','管道焊接','焊锡预估','template1',1,'admin','2018-02-28 15:06:37','admin','0000-00-00 00:00:00'),('admin-加固外壳检查表-20180227215248','外壳加工','step-1','加固外壳检查表',4,'admin','2018-02-27 21:52:49','admin','2018-02-28 15:04:52'),('admin-月末绩效检查单-20180310114126','hanjie','step-1','月末绩效检查单',2,'admin','2018-03-10 11:41:33','admin','0000-00-00 00:00:00'),('zhangshaoyan-月末绩效检查单-20180320095537','hanjie','step-2','月末绩效检查单',3,'zhangshaoyan','2018-03-20 09:55:43','admin','2018-03-20 12:26:25');

/*Table structure for table `templateinfo` */

DROP TABLE IF EXISTS `templateinfo`;

CREATE TABLE `templateinfo` (
  `TemplateName` varchar(64) NOT NULL,
  `VarSourceName` varchar(64) NOT NULL,
  `FileSize` int(11) DEFAULT NULL,
  `Creator` varchar(64) DEFAULT NULL,
  `CreateTime` datetime DEFAULT NULL,
  PRIMARY KEY (`TemplateName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `templateinfo` */

insert  into `templateinfo`(`TemplateName`,`VarSourceName`,`FileSize`,`Creator`,`CreateTime`) values ('加固外壳检查表','加固外壳检查单',368,'admin','2018-02-27 21:46:08'),('月末绩效检查单','月末绩效检查单',582,'admin','2018-03-06 15:34:47');

/*Table structure for table `userinfo` */

DROP TABLE IF EXISTS `userinfo`;

CREATE TABLE `userinfo` (
  `UserName` varchar(64) NOT NULL,
  `RealName` varchar(256) DEFAULT NULL,
  `RoleName` varchar(64) NOT NULL,
  `Sex` varchar(16) DEFAULT NULL,
  `LockBit` int(1) DEFAULT NULL,
  `Password` varchar(64) NOT NULL,
  `Mobile` varchar(64) DEFAULT NULL,
  `Creator` varchar(64) DEFAULT NULL,
  `CreateTime` datetime DEFAULT NULL,
  `LastLoginTime` datetime DEFAULT NULL,
  PRIMARY KEY (`UserName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `userinfo` */

insert  into `userinfo`(`UserName`,`RealName`,`RoleName`,`Sex`,`LockBit`,`Password`,`Mobile`,`Creator`,`CreateTime`,`LastLoginTime`) values ('admin','administrator','admin','male',0,'MTIzNDU2','13522296239','admin','2018-02-26 20:38:07',NULL),('ganjue','感觉','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:40','2018-03-18 18:43:40'),('guoshouyi','郭守义','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 16:46:31','2018-03-18 16:46:31'),('kele','可乐','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:40','2018-03-18 18:43:40'),('keshi','乐视','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:40','2018-03-18 18:43:40'),('lianyunchuan','连云川','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:39','2018-03-18 18:43:39'),('lijianli','李建立','生产员工组','male',NULL,'bGlqaWFubGk=','13945102345','admin','2018-03-06 15:31:57','2018-03-06 15:31:57'),('likeqiang','李克强','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 16:46:31','2018-03-18 16:46:31'),('liuchuanfeng','刘传峰','班长组','male',NULL,'bGl1Y2h1YW5mZW5n','13296871123','admin','2018-03-06 15:30:54','2018-03-06 15:30:54'),('liulina','刘丽娜','生产员工组','female',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 16:46:30','2018-03-18 16:46:30'),('luoxiaozuo','落小左','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 16:46:31','2018-03-18 16:46:31'),('mingle','明乐','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:40','2018-03-18 18:43:40'),('ningkang','宁康','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 16:46:31','2018-03-18 16:46:31'),('panxiaohui','潘晓慧','生产员工组','female',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 16:46:31','2018-03-18 16:46:31'),('qiaozhi','侨志','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:39','2018-03-18 18:43:39'),('songchangji','宋昌几','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:41','2018-03-18 18:43:41'),('songchangkun','宋昌坤','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:41','2018-03-18 18:43:41'),('songling','宋零','生产员工组','female',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 16:46:30','2018-03-18 16:46:30'),('songmingyi','宋明义','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:41','2018-03-18 18:43:41'),('tiandeyu','田德雨','生产员工组','male',NULL,'dGlhbmRleXU=','13966092345','admin','2018-03-06 15:32:53','2018-03-06 15:32:53'),('tiantian','甜甜','生产员工组','female',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:40','2018-03-18 18:43:40'),('tianwangmiao','天王苗','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:40','2018-03-18 18:43:40'),('tianwujian','田无间','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:40','2018-03-18 18:43:40'),('tianxin','田心','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:40','2018-03-18 18:43:40'),('wangkun','王昆','生产员工组','female',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 16:46:30','2018-03-18 16:46:30'),('wanglifeng','王立风','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:39','2018-03-18 18:43:39'),('wanglizhu','王立柱','班长组','male',NULL,'MTIzNDU2','15811402356','admin','2018-03-18 18:42:37','2018-03-18 18:42:37'),('wangxiaoshi','王小时','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:39','2018-03-18 18:43:39'),('xufuqiang','徐富强','生产员工组','male',NULL,'eHVmdXFpYW5n','15966032566','admin','2018-03-06 15:32:24','2018-03-06 15:32:24'),('xuxiake','徐霞客','生产员工组','female',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 16:46:30','2018-03-18 16:46:30'),('yangjinshuo','杨金硕','生产员工组','female',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 16:46:30','2018-03-18 16:46:30'),('zhangle','张乐','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:39','2018-03-18 18:43:39'),('zhangshaoyan','张绍言','班长组','male',NULL,'MTIzNDU2','13522296239','admin','2018-03-06 15:29:53','2018-03-06 15:29:53'),('zhangyantai','张烟台','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:39','2018-03-18 18:43:39'),('zhenni','珍妮','生产员工组','male',NULL,'MTIzNDU2','15966032566','admin','2018-03-18 18:43:40','2018-03-18 18:43:40');

/*Table structure for table `varsourceinfo` */

DROP TABLE IF EXISTS `varsourceinfo`;

CREATE TABLE `varsourceinfo` (
  `VarSourceName` varchar(64) NOT NULL,
  `RefCount` int(11) DEFAULT NULL,
  `Creator` varchar(64) DEFAULT NULL,
  `CreateTime` datetime DEFAULT NULL,
  PRIMARY KEY (`VarSourceName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `varsourceinfo` */

insert  into `varsourceinfo`(`VarSourceName`,`RefCount`,`Creator`,`CreateTime`) values ('加固外壳检查单',1,'admin','2018-02-27 21:49:27'),('月末绩效检查单',1,'admin','2018-03-06 15:37:49');

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
