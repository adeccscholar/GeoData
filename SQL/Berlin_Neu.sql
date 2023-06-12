Use GeoDaten;

DROP TABLE [mod_neu].Berlin_Adresse_Ortsteil_Beziehung;
DROP TABLE [mod_neu].Berlin_Adresse_Strasse_Beziehung;
DROP TABLE [mod_neu].Berlin_Ortsteile_Bezirk_Beziehung;
DROP TABLE [mod_neu].Berlin_Strassen_Beziehung;
DROP TABLE [mod_neu].Berlin;
DROP TABLE [mod_neu].Berlin_Strassen;
DROP TABLE [mod_neu].Berlin_Ortsteile;
DROP TABLE [mod_neu].Berlin_Bezirke;
DROP SCHEMA mod_neu;
GO

CREATE SCHEMA mod_neu AUTHORIZATION dbo;
GO

CREATE TABLE [mod_neu].Berlin_Bezirke (
   ID INTEGER Identity(1,1) NOT NULL,
   Bezirk varchar(50) NOT NULL,
   Gueltig_ab DATE NOT NULL,
   Land_Kz INTEGER NOT NULL,
   Bezirk_Kz INTEGER NOT NULL
   );


CREATE TABLE [mod_neu].Berlin_Ortsteile (
   ID INTEGER Identity(1,1) NOT NULL,
   Ortsteil varchar(50) NOT NULL,
   Gueltig_ab DATE NOT NULL,
   Land_Kz INTEGER NOT NULL,
   Bezirk_Kz INTEGER NOT NULL,
   Ortsteil_Kz INTEGER NOT NULL
   );


CREATE TABLE [mod_neu].Berlin_Strassen (
   ID INTEGER Identity(1,1) NOT NULL,
   Strasse VARCHAR(75) NOT NULL,
   Strasse_Kz INTEGER NOT NULL
);


CREATE TABLE [mod_neu].Berlin (
   ID INTEGER Identity(1,1) NOT NULL,
   Latitude float NOT NULL,
   Longitude float NOT NULL
   );


CREATE TABLE [mod_neu].Berlin_Adresse_Strasse_Beziehung (
   -- ID INTEGER Identity(1,1) NOT NULL,
   Adresse_ID INTEGER NOT NULL,
   Strasse_ID INTEGER NOT NULL,
   Nummer INTEGER NULL,
   ADZ VARCHAR(5) NULL,
   PLZ VARCHAR(5) NOT NULL
   );


CREATE TABLE [mod_neu].Berlin_Adresse_Ortsteil_Beziehung (
   ID INTEGER NOT NULL,
   Ortsteil_ID INTEGER NOT NULL
   );


CREATE TABLE [mod_neu].Berlin_Ortsteile_Bezirk_Beziehung (
   Ortsteil_ID INTEGER NOT NULL,
   Bezirk_ID INTEGER NOT NULL
   );


CREATE TABLE [mod_neu].Berlin_Strassen_Beziehung (
   Strasse_ID INTEGER NOT NULL,
   Ortsteil_ID INTEGER NOT NULL
   );

GO

/* ---- Contraints für  [mod_neu].Berlin_Bezirke ----- */

ALTER TABLE [mod_neu].Berlin_Bezirke ADD CONSTRAINT pk_Bln_Bezirke PRIMARY KEY (ID);
ALTER TABLE [mod_neu].Berlin_Bezirke ADD CONSTRAINT uk_Bln_Bezirke_Bezirk UNIQUE (Bezirk); 
ALTER TABLE [mod_neu].Berlin_Bezirke ADD CONSTRAINT uk_Bln_Bezirke_Land_Bezirk_Kz UNIQUE (Land_Kz, Bezirk_Kz);

ALTER TABLE [mod_neu].Berlin_Bezirke ADD CONSTRAINT ck_Bln_Bezirke_Land_Kz CHECK (Land_Kz > 0 AND Land_Kz < 100);
ALTER TABLE [mod_neu].Berlin_Bezirke ADD CONSTRAINT ck_Bln_Bezirke_Bezirk_Kz CHECK (Bezirk_Kz > 0 AND Bezirk_Kz < 100);


/* ---- Contraints für  [mod_neu].Berlin_Ortsteile ----- */

ALTER TABLE [mod_neu].Berlin_Ortsteile ADD CONSTRAINT pk_Bln_Ortsteile PRIMARY KEY (ID);
ALTER TABLE [mod_neu].Berlin_Ortsteile ADD CONSTRAINT uk_Bln_Ortsteile_Ortsteil UNIQUE (Ortsteil);
ALTER TABLE [mod_neu].Berlin_Ortsteile ADD CONSTRAINT uk_Bln_Ortsteile_Kz UNIQUE (Land_Kz, Bezirk_Kz, Ortsteil_Kz);

ALTER TABLE [mod_neu].Berlin_Ortsteile ADD CONSTRAINT ck_Bln_Ortsteile_Land_Kz CHECK (Land_Kz > 0 AND Land_Kz < 100);
ALTER TABLE [mod_neu].Berlin_Ortsteile ADD CONSTRAINT ck_Bln_Ortsteile_Bezirk_Kz CHECK (Bezirk_Kz > 0 AND Bezirk_Kz < 100);
ALTER TABLE [mod_neu].Berlin_Ortsteile ADD CONSTRAINT ck_Bln_Ortsteile_Ortsteil_Kz CHECK (Ortsteil_Kz > 0 AND Ortsteil_Kz < 100);


/* ---- Contraints für  [mod_neu].Berlin_Strassen ----- */

ALTER TABLE [mod_neu].Berlin_Strassen ADD CONSTRAINT pk_Bln_Strassen PRIMARY KEY (ID);
ALTER TABLE [mod_neu].Berlin_Strassen ADD CONSTRAINT ck_Bln_Strassen_Kz CHECK (Strasse_Kz > 0 AND Strasse_Kz < 100000);


/* ---- Contraints für  [mod_neu].Berlin ----- */

ALTER TABLE [mod_neu].Berlin ADD CONSTRAINT pk_mod_Berlin PRIMARY KEY (ID);
ALTER TABLE [mod_neu].Berlin ADD CONSTRAINT ck_mod_Berlin_Lat CHECK (Latitude >= -90 AND Latitude <= 90); 
ALTER TABLE [mod_neu].Berlin ADD CONSTRAINT ck_mod_Berlin_Long CHECK (Longitude >= -180 AND Longitude <= 180);



GO


INSERT INTO [mod_neu].Berlin_Bezirke(Bezirk, Gueltig_ab, Land_Kz, Bezirk_Kz)
SELECT DISTINCT Bezirk, '01.01.2001', Land_ID, Bezirk_ID
FROM dbo.Berlin;

INSERT INTO [mod_neu].Berlin_Ortsteile (Ortsteil, Gueltig_ab, Land_Kz, Bezirk_Kz, Ortsteil_Kz)
SELECT DISTINCT Ortsteil, '01.01.2001', Land_ID, Bezirk_ID, Ortsteil_ID - 100 * Bezirk_ID
FROM dbo.Berlin;

INSERT INTO [mod_neu].Berlin_Strassen (Strasse, Strasse_Kz)
SELECT DISTINCT Strasse, Strasse_ID
FROM dbo.Berlin

GO

INSERT INTO [mod_neu].Berlin_Ortsteile_Bezirk_Beziehung (Ortsteil_ID, Bezirk_ID)
SELECT DISTINCT a.ID AS Ortsteil_ID, b.ID AS Bezirk_ID
FROM [mod_neu].Berlin_Ortsteile a JOIN [mod_neu].Berlin_Bezirke b ON (b.Land_Kz = a.Land_Kz AND b.Bezirk_Kz = a.Bezirk_Kz)

INSERT INTO [mod_neu].Berlin_Strassen_Beziehung (Strasse_ID, Ortsteil_ID)
SELECT DISTINCT s.ID AS Strasse_ID, o.ID AS Ortsteil_ID
FROM Berlin a JOIN [mod_neu].Berlin_Strassen s ON (s.Strasse_Kz = a.Strasse_ID)
              JOIN [mod_neu].Berlin_Ortsteile o ON (o.Bezirk_Kz = a.Bezirk_ID AND o.Ortsteil_Kz = a.Ortsteil_ID - 100 * a.Bezirk_ID);
GO


CREATE PROCEDURE Migrate_Berlin
AS
BEGIN
   DECLARE @PLZ VARCHAR(5);
   DECLARE @Nummer INTEGER;
   DECLARE @ADZ VARCHAR(5);
   DECLARE @Latitude FLOAT;
   DECLARE @Longitude FLOAT;
   DECLARE @Strasse_ID INTEGER;
   DECLARE @Adresse_ID INTEGER;


   DECLARE migCursor CURSOR FOR
      SELECT a.PLZ, a.HNR AS Nummer, a.ADZ, a.Latitude, a.Longitude, s.ID AS Strasse_ID
      FROM dbo.Berlin a JOIN [mod_neu].Berlin_Strassen s ON (s.Strasse_Kz = a.Strasse_ID)

   OPEN migCursor;
   FETCH NEXT FROM migCursor INTO @PLZ, @Nummer, @ADZ, @Latitude, @Longitude, @Strasse_ID;

   WHILE @@FETCH_STATUS = 0
   BEGIN
      CREATE TABLE #AdID ( ID INT );
BEGIN TRANSACTION;
	  INSERT INTO [mod_neu].Berlin (Latitude, Longitude) 
	  OUTPUT inserted.ID INTO #AdID (ID)
	  VALUES (@Latitude, @Longitude);

	  SELECT @Adresse_ID = ID
	  FROM #AdID;

	  INSERT INTO [mod_neu].Berlin_Adresse_Strasse_Beziehung (Adresse_ID, Strasse_ID, Nummer, ADZ, PLZ)
	  VALUES (@Adresse_ID, @Strasse_ID, @Nummer, @ADZ, @PLZ);
COMMIT;
	  DROP TABLE #AdID;

	  FETCH NEXT FROM migCursor INTO @PLZ, @Nummer, @ADZ, @Latitude, @Longitude, @Strasse_ID;
   END;
   
   CLOSE migCursor;
   DEALLOCATE migCursor;
END;

EXECUTE Migrate_Berlin;

GO

DROP PROCEDURE Migrate_Berlin;
GO

DECLARE @Message VARCHAR(100) = 'Hello, world!';

PRINT @Message;

/*
CREATE TABLE [mod_neu].Berlin (
   ID INTEGER Identity(1,1) NOT NULL,
   Latitude float NOT NULL,
   Longitude float NOT NULL
   );


CREATE TABLE [mod_neu].Berlin_Adresse_Strasse_Beziehung (
   ID INTEGER Identity(1,1) NOT NULL,
   Adresse_ID INTEGER NOT NULL,
   Strasse_ID INTEGER NOT NULL,
   Nummer INTEGER NULL,
   ADZ VARCHAR(5) NULL,
   PLZ VARCHAR(5) NOT NULL
   );


CREATE TABLE [mod_neu].Berlin_Adresse_Ortsteil_Beziehung (
   ID INTEGER NOT NULL,
   Ortsteil_ID INTEGER NOT NULL
   );
*/


/* ---- Contraints für  [mod_neu].Berlin_Strasse_Beziehung  ----- */

ALTER TABLE [mod_neu].Berlin_Adresse_Strasse_Beziehung ADD CONSTRAINT pk_mod_Bln_Adr_Strasse_Bez PRIMARY KEY (Adresse_ID);
ALTER TABLE [mod_neu].Berlin_Adresse_Strasse_Beziehung ADD CONSTRAINT uk_mod_Bln_Adr_Strasse_Bez_Strasse UNIQUE (Strasse_ID, Nummer, ADZ);
ALTER TABLE [mod_neu].Berlin_Adresse_Strasse_Beziehung ADD CONSTRAINT fk_mod_Bln_Adr_Strasse_Bez_Bln FOREIGN KEY (Adresse_ID) REFERENCES [mod_neu].Berlin (ID);
ALTER TABLE [mod_neu].Berlin_Adresse_Strasse_Beziehung ADD CONSTRAINT fk_mod_Bln_Adr_Strasse_Bez_Str FOREIGN KEY (Strasse_ID) REFERENCES [mod_neu].Berlin_Strassen (ID);


/* ---- Contraints für  [mod_neu].Berlin_Adresse_Ortsteil_Beziehung ----- */

ALTER TABLE [mod_neu].Berlin_Adresse_Ortsteil_Beziehung ADD CONSTRAINT pk_mod_Bln_Adr_Ortsteil_Bez PRIMARY KEY (ID, Ortsteil_ID);
ALTER TABLE [mod_neu].Berlin_Adresse_Ortsteil_Beziehung ADD CONSTRAINT fk_mod_Bln_Adr_Ortsteil_Bez_Bln FOREIGN KEY (ID) REFERENCES [mod_neu].Berlin (ID); 
ALTER TABLE [mod_neu].Berlin_Adresse_Ortsteil_Beziehung ADD CONSTRAINT pk_mod_Bln_Adr_Ortsteil_Bez_Ort FOREIGN KEY (Ortsteil_ID) REFERENCES [mod_neu].Berlin_Ortsteile (ID);


/* ---- Contraints für  [mod_neu].Berlin_Ortsteile_Bezirk_Beziehung ----- */

ALTER TABLE [mod_neu].Berlin_Ortsteile_Bezirk_Beziehung ADD CONSTRAINT pk_mod_Berlin_Ortsteile_Beziehung PRIMARY KEY (Ortsteil_ID);
ALTER TABLE [mod_neu].Berlin_Ortsteile_Bezirk_Beziehung ADD CONSTRAINT fk_mod_Berlin_Ortsteile_Ortsteil FOREIGN KEY (Ortsteil_ID) REFERENCES [mod_neu].Berlin_Ortsteile (ID);
ALTER TABLE [mod_neu].Berlin_Ortsteile_Bezirk_Beziehung ADD CONSTRAINT fk_mod_Berlin_Ortsteile_Bezirk FOREIGN KEY (Bezirk_ID) REFERENCES [mod_neu].Berlin_Bezirke (ID);


/* ---- Contraints für  [mod_neu].Berlin_Strassen_Beziehung ----- */

ALTER TABLE [mod_neu].Berlin_Strassen_Beziehung ADD CONSTRAINT pk_mod_Berlin_Strassen_Beziehung PRIMARY KEY (Strasse_ID, Ortsteil_ID);
ALTER TABLE [mod_neu].Berlin_Strassen_Beziehung ADD CONSTRAINT fk_mod_Berlin_Strassen_Strasse FOREIGN KEY (Strasse_ID) REFERENCES [mod_neu].Berlin_Strassen (ID);
ALTER TABLE [mod_neu].Berlin_Strassen_Beziehung ADD CONSTRAINT fk_mod_Berlin_Strassen_Ortsteil FOREIGN KEY (Ortsteil_ID) REFERENCES [mod_neu].Berlin_Ortsteile (ID);
