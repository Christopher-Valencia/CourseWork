CREATE DATABASE CI420;

USE CI420;

CREATE TABLE STUDENT (
DOLPHIN_ID int(9),
FIRST_NAME varchar(16),
LAST_NAME varchar(32),
PRIMARY KEY (DOLPHIN_ID)
) ENGINE=INNODB;

CREATE TABLE PROJECT (
PROJECT_ID int(4),
PROJECT_NAME varchar(32),
PROJECT_DESCRIPTION varchar(255),
PRIMARY KEY (PROJECT_ID)
) ENGINE=INNODB;

CREATE TABLE GROUP_MEMBER (
DOLPHIN_ID int(9),
PROJECT_ID int(4),
PRIMARY KEY (DOLPHIN_ID, PROJECT_ID),
FOREIGN KEY (DOLPHIN_ID) REFERENCES STUDENT(DOLPHIN_ID),
FOREIGN KEY (PROJECT_ID) REFERENCES PROJECT(PROJECT_ID)
) ENGINE=INNODB;