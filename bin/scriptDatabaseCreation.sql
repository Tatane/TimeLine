CREATE TABLE "Category" (
	`Id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`Name`	TEXT NOT NULL
);
CREATE TABLE "Fact" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`startTime`	DateTime NOT NULL,
	`endTime`	DateTime NOT NULL,
	`title`	varchar(100),
	`description`	varchar(1000)
, categoryId INTEGER);


