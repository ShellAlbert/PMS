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

/*Table structure for table `l型结构件检查清单_data` */

DROP TABLE IF EXISTS `l型结构件检查清单_data`;

CREATE TABLE `l型结构件检查清单_data` (
  `TaskName` varchar(45) NOT NULL,
  `number` varchar(45) DEFAULT NULL,
  `width` int(11) DEFAULT NULL,
  `height` int(11) DEFAULT NULL,
  `fillDate` datetime DEFAULT NULL,
  PRIMARY KEY (`TaskName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `l型结构件检查清单_data` */

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

insert  into `processinfo`(`ProcessName`,`StepNum`,`Creator`,`CreateTime`) values ('hanjie',0,'admin','2018-02-27 20:59:58'),('外壳加工',0,'admin','2018-02-27 21:01:11'),('管道焊接',2,'admin','2018-02-27 21:00:38'),('阻抗测试',0,'admin','2018-02-27 21:01:24');

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

insert  into `roleinfo`(`RoleName`,`PermBits`,`RoleMemo`,`Creator`,`CreateTime`) values ('admin','255,255,255,255,255,255','nothing','admin','2018-02-26 20:32:11'),('管理员','255,255,31,7,7,7','没有什么可以说的','admin','2018-02-27 15:56:29');

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
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8;

/*Data for the table `stepinfo` */

insert  into `stepinfo`(`No`,`StepName`,`ProcessName`,`LinkTemplates`,`LinkFiles`,`LinkRoles`) values (6,'初步尺寸测量','管道焊接','template1',NULL,NULL),(7,'初步尺寸测量','管道焊接',NULL,'GongYiFile/BlockDiagramOfLaserSpyDeviceV0.1.pdf',NULL),(8,'初步尺寸测量','管道焊接',NULL,NULL,'admin'),(9,'初步尺寸测量','管道焊接',NULL,NULL,'管理员'),(10,'焊锡预估','管道焊接','template1',NULL,NULL),(11,'焊锡预估','管道焊接',NULL,'GongYiFile/BlockDiagramOfLaserSpyDeviceV0.1.pdf',NULL),(12,'焊锡预估','管道焊接',NULL,'国标GB2003/RF射频同轴连接器MCX-KHD.png',NULL),(13,'焊锡预估','管道焊接',NULL,NULL,'管理员');

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

insert  into `templateinfo`(`TemplateName`,`VarSourceName`,`FileSize`,`Creator`,`CreateTime`) values ('template1','L型结构件检查清单',368,'admin','2018-02-27 17:01:53');

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

insert  into `userinfo`(`UserName`,`RealName`,`RoleName`,`Sex`,`LockBit`,`Password`,`Mobile`,`Creator`,`CreateTime`,`LastLoginTime`) values ('admin','administrator','admin','male',0,'MTIzNDU2','13522296239','admin','2018-02-26 20:38:07',NULL),('zhangshaoyan','张绍言','管理员','male',NULL,'MTIzNDU2','13522296239','admin','2018-02-27 15:59:08','2018-02-27 15:59:08');

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

insert  into `varsourceinfo`(`VarSourceName`,`RefCount`,`Creator`,`CreateTime`) values ('L型结构件检查清单',1,'admin','2018-02-27 16:46:59');

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
