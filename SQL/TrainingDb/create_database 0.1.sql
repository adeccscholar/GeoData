/*
Projekt: Training
Inhalt:  Anlegen der Datenbank
Autor:   Volker Hillmann (adecc Systemhaus GmbH)
Datum:   24.04.2016
Copyright © 2001 - 2016. Alle Rechte vorbehalten.
*/

CREATE TABLE AddressTypes (
   ID             INTEGER NOT NULL,
   Denotation     VARCHAR(50) NOT NULL,
   Abbreviation   VARCHAR(10),
   Description    TEXT,
   Notes          TEXT,
   UrgentValue    SMALLINT
  );

CREATE TABLE Address (
   ID             INTEGER NOT NULL,
   AddressType    INTEGER NOT NULL,
   Street         VARCHAR(50) NOT NULL,
   StreetNumber   VARCHAR(10),
   City           VARCHAR(50) NOT NULL,
   Zipcode        VARCHAR(10) NOT NULL,
   Country        INTEGER NOT NULL
  );

CREATE TABLE PhoneTypes (
   ID             INTEGER NOT NULL,
   Denotation     VARCHAR(50) NOT NULL,
   Abbreviation   VARCHAR(10),
   Description    TEXT,
   Notes          TEXT,
   UrgentValue    SMALLINT
  );

CREATE TABLE Phone (
   ID             INTEGER NOT NULL,
   PhoneType      INTEGER NOT NULL,
   AreaCode       VARCHAR(10) NOT NULL,
   CallNumber     VARCHAR(13) NOT NULL,
   Country        INTEGER NOT NULL
  );

CREATE TABLE BankingTypes (
   ID             INTEGER NOT NULL,
   Denotation     VARCHAR(50) NOT NULL,
   Abbreviation   VARCHAR(10),
   Description    TEXT,
   Notes          TEXT,
   UrgentValue    SMALLINT
  );

CREATE TABLE Banking (
   ID             INTEGER NOT NULL,
   BankingType    INTEGER NOT NULL,
   BankName       VARCHAR(50),
   IBAN           VARCHAR(33),
   BIC            VARCHAR(12),
   BankOwner      VARCHAR(27),
   Country        INTEGER
  );

CREATE TABLE InternetTypes (
   ID             INTEGER NOT NULL,
   Denotation     VARCHAR(50) NOT NULL,
   Abbreviation   VARCHAR(10),
   Description    TEXT,
   Prefix         VARCHAR(10),
   Notes          TEXT,
   UrgentValue    SMALLINT
  );

CREATE TABLE Internet (
   ID             INTEGER NOT NULL,
   InternetType   INTEGER NOT NULL,
   Adresse        VARCHAR(100) NOT NULL
  );

CREATE TABLE Countries (
   ID             INTEGER NOT NULL,
   Denotation     VARCHAR(50) NOT NULL,
   Abbreviation   VARCHAR(10),
   Description    TEXT,
   CountryDialing VARCHAR(10),
   ISO_Code       VARCHAR(5),
   Notes          TEXT,
   UrgentValue    SMALLINT
  );

CREATE TABLE FamilyTypes (
   ID             INTEGER NOT NULL,
   Denotation     VARCHAR(50) NOT NULL,
   Abbreviation   VARCHAR(10),
   Description    TEXT,
   Notes          TEXT,
   UrgentValue    SMALLINT
  );

CREATE TABLE FormOfAddress (
   ID             INTEGER NOT NULL,
   Denotation     VARCHAR(50) NOT NULL,
   Abbreviation   VARCHAR(10),
   Description    TEXT,
   TypeSpec       INTEGER NOT NULL,
   Salutation     VARCHAR(50),
   Valediction    VARCHAR(50),
   Notes          TEXT,
   UrgentValue    SMALLINT
  );

CREATE TABLE Person (
   ID             INTEGER NOT NULL,
   Name           VARCHAR(30) NOT NULL,
   Firstname      VARCHAR(30),
   FormOfAddress  INTEGER NOT NULL,
   Birthday       DATETIME,
   Notes          TEXT
  );

CREATE TABLE Departments (
   ID             INTEGER NOT NULL,
   Denotation     VARCHAR(50) NOT NULL,
   Abbreviation   VARCHAR(10),
   Description    TEXT,
   Notes          TEXT
  );

CREATE TABLE JobPositions (
   ID             INTEGER NOT NULL,
   Denotation     VARCHAR(50) NOT NULL,
   Abbreviation   VARCHAR(10),
   Description    TEXT,
   Notes          TEXT,
   UrgentValue    SMALLINT
  );

CREATE TABLE Employees (
   ID             INTEGER NOT NULL,
   PersonNumber   VARCHAR(15) NOT NULL,
   Salery         DECIMAL(10,2),
   StartOfJob     DATETIME,
   JobPosition    INTEGER,
   JobSpec        VARCHAR(100),
   Department     INTEGER NOT NULL,
   SocialNummer   VARCHAR(20),
   Active         SMALLINT
  );
GO
  
ALTER TABLE AddressTypes ADD CONSTRAINT pk_AddressTypes PRIMARY KEY (ID);
ALTER TABLE Address ADD CONSTRAINT pk_Address PRIMARY KEY (ID, AddressType);
ALTER TABLE PhoneTypes ADD CONSTRAINT pk_PhoneTypes PRIMARY KEY (ID);
ALTER TABLE Phone ADD CONSTRAINT pk_Phone PRIMARY KEY (ID, PhoneType);
ALTER TABLE BankingTypes ADD CONSTRAINT pk_BankingTypes PRIMARY KEY (ID);
ALTER TABLE Banking ADD CONSTRAINT pk_Banking PRIMARY KEY (ID, BankingType);
ALTER TABLE InternetTypes ADD CONSTRAINT pk_InternetTypes PRIMARY KEY (ID);
ALTER TABLE Internet ADD CONSTRAINT pk_Internet PRIMARY KEY (ID, InternetType);
ALTER TABLE Countries ADD CONSTRAINT pk_Countries PRIMARY KEY (ID);
ALTER TABLE FamilyTypes ADD CONSTRAINT pk_FamilyTypes PRIMARY KEY (ID);
ALTER TABLE FormOfAddress ADD CONSTRAINT pk_FormOfAddress PRIMARY KEY (ID);
ALTER TABLE Person ADD CONSTRAINT pk_Person PRIMARY KEY (ID);
ALTER TABLE Departments ADD CONSTRAINT pk_Departments PRIMARY KEY (ID);
ALTER TABLE JobPositions ADD CONSTRAINT pk_JobPositions PRIMARY KEY (ID);
ALTER TABLE Employees ADD CONSTRAINT pk_Employees PRIMARY KEY (ID);

GO

ALTER TABLE AddressTypes ADD CONSTRAINT uk_AddressTypes_Denotation UNIQUE (Denotation);
ALTER TABLE PhoneTypes ADD CONSTRAINT uk_PhoneTypes_Denotation UNIQUE (Denotation);
ALTER TABLE BankingTypes ADD CONSTRAINT uk_BankingTypes_Denotation UNIQUE (Denotation);
ALTER TABLE InternetTypes ADD CONSTRAINT uk_InternetTypes_Denotation UNIQUE (Denotation);
ALTER TABLE Countries ADD CONSTRAINT uk_Countries_Denotation UNIQUE (Denotation);
ALTER TABLE FamilyTypes ADD CONSTRAINT uk_FamilyTypes_Denotation UNIQUE (Denotation);
ALTER TABLE FormOfAddress ADD CONSTRAINT uk_FormOfAddress_Denotation UNIQUE (Denotation);
ALTER TABLE Departments ADD CONSTRAINT uk_Departments_Denotation UNIQUE (Denotation);
ALTER TABLE JobPositions ADD CONSTRAINT uk_JobPositions_Denotation UNIQUE (Denotation);

GO

ALTER TABLE Address ADD CONSTRAINT fk_Address_Person FOREIGN KEY (ID) REFERENCES Person (ID);
ALTER TABLE Address ADD CONSTRAINT fk_Address_AddressTypes FOREIGN KEY (AddressType) REFERENCES AddressTypes (ID);
ALTER TABLE Address ADD CONSTRAINT fk_Address_Countries FOREIGN KEY (Country) REFERENCES Countries (ID);
ALTER TABLE Phone ADD CONSTRAINT fk_Phone_Person FOREIGN KEY (ID) REFERENCES Person (ID);
ALTER TABLE Phone ADD CONSTRAINT fk_Phone_PhoneTypes FOREIGN KEY (PhoneType) REFERENCES PhoneTypes (ID);
ALTER TABLE Phone ADD CONSTRAINT fk_Phone_Countries FOREIGN KEY (Country) REFERENCES Countries (ID);
ALTER TABLE Banking ADD CONSTRAINT fk_Banking_Person FOREIGN KEY (ID) REFERENCES Person (ID);
ALTER TABLE Banking ADD CONSTRAINT fk_Banking_BankingTypes FOREIGN KEY (BankingType) REFERENCES BankingTypes (ID);
ALTER TABLE Banking ADD CONSTRAINT fk_Banking_Countries FOREIGN KEY (Country) REFERENCES Countries (ID);
ALTER TABLE Internet ADD CONSTRAINT fk_Internet_Person FOREIGN KEY (ID) REFERENCES Person (ID);
ALTER TABLE Internet ADD CONSTRAINT fk_Internet_InternetTypes FOREIGN KEY (InternetType) REFERENCES InternetTypes (ID);
ALTER TABLE FormOfAddress ADD CONSTRAINT fk_FormOfAddress_FamilyTypes FOREIGN KEY (TypeSpec) REFERENCES FamilyTypes (ID);
ALTER TABLE Person ADD CONSTRAINT fk_Person_FormOfAddress FOREIGN KEY (FormOfAddress) REFERENCES FormOfAddress (ID);
ALTER TABLE Employees ADD CONSTRAINT fk_Employees_Person FOREIGN KEY (ID) REFERENCES Person (ID);
ALTER TABLE Employees ADD CONSTRAINT fk_Employees_JobPositions FOREIGN KEY (JobPosition) REFERENCES JobPositions (ID);
ALTER TABLE Employees ADD CONSTRAINT fk_Employees_Departments FOREIGN KEY (Department) REFERENCES Departments (ID);

GO
