/* ------------------------------------------------------------------------------------------------------------------
    Beispiel Skript für eine neue Geostruktur Datenbank
	   - OpenData Berlin, Brandenburg, Sachsen und Thüringen als Input
	   - Projekt um Normalisierung zu zeigen, Vergleiche zu unnormalisierten Daten

	Autor: Volker Hillmann
	Projekt: adecc Scholar (github https://github.com/adeccscholar/GeoData)
	GNU GENERAL PUBLIC LICENSE
 ------------------------------------------------------------------------------------------------------------------ */

USE [TestNeu]

-- Aufräumen, löschen der bisherigen Tabellen und Daten, Regeln und Verknüpfungen

IF EXISTS (
    SELECT 1
    FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS
    WHERE CONSTRAINT_NAME = 'ck_Geo_Structure_Rules' AND TABLE_NAME = 'Geographical_Structure' )
BEGIN
ALTER TABLE Geographical_Structure DROP CONSTRAINT ck_Geo_Structure_Rules;
END

IF OBJECT_ID('Check_Geographic_Units_Rules', 'FN') IS NOT NULL
BEGIN
DROP FUNCTION Check_Geographic_Units_Rules;
END

IF OBJECT_ID('view_Berlin', 'V') IS NOT NULL
BEGIN
DROP VIEW view_Berlin;
END

IF OBJECT_ID('view_Geo_Structure', 'V') IS NOT NULL
BEGIN
DROP VIEW view_Geo_Structure;
END

IF OBJECT_ID('tree_Geo_Structure', 'V') IS NOT NULL
BEGIN
DROP VIEW tree_Geo_Structure;
END

IF OBJECT_ID('Parcel_Street_Mapping', 'U') IS NOT NULL
BEGIN
DROP TABLE Parcel_Street_Mapping;
END

IF OBJECT_ID('Parcel_of_Land', 'U') IS NOT NULL
BEGIN
DROP TABLE Parcel_of_Land;
END

IF OBJECT_ID('Street_Unit_Mapping', 'U') IS NOT NULL
BEGIN
DROP TABLE Street_Unit_Mapping;
END

IF OBJECT_ID('Streets', 'U') IS NOT NULL
BEGIN
DROP TABLE Streets;
END

IF OBJECT_ID('Geographical_Structure', 'U') IS NOT NULL
BEGIN
DROP TABLE Geographical_Structure;
END

IF OBJECT_ID('Geographic_Units_Nuts_Rules', 'U') IS NOT NULL
BEGIN
DROP TABLE Geographic_Units_Nuts_Rules;
END

IF OBJECT_ID('Geographic_Units_Rules', 'U') IS NOT NULL
BEGIN
DROP TABLE Geographic_Units_Rules;
END

IF OBJECT_ID('Geographic_Units_Range', 'U') IS NOT NULL
BEGIN
DROP TABLE Geographic_Units_Range;
END

IF OBJECT_ID('NUTS_Range', 'U') IS NOT NULL
BEGIN
DROP TABLE NUTS_Range;
END

GO

/* Erstellen der Tabellen, Sichten, Contraints, Funktionen */

/* ------------------------------------------------------------------------------------------------------------------
    Tabelle mit Werten für die Statistik - Informationen (NUTS Ebenen)
 ------------------------------------------------------------------------------------------------------------------ */


CREATE TABLE NUTS_Range (
  ID               INTEGER NOT NULL,
  Designation      VARCHAR(25) NOT NULL,
  Description      VARCHAR(MAX)
  );

ALTER TABLE NUTS_Range ADD CONSTRAINT pk_NUTS_Range PRIMARY KEY (ID);
ALTER TABLE NUTS_Range ADD CONSTRAINT uk_NUTS_Range UNIQUE (Designation);

/* ------------------------------------------------------------------------------------------------------------------
    Tabelle mit möglichen Werten / Kategorien für die geografischen Einheiten
	Boolscher Wert, wenn es sich um eine Stadt / Ort für Anschrift mit PLZ handelt
	Boolscher Wert der angibt, ob zu dieser Kategorie Straßen zugeordnet werden können
 --------------------------------------------------------------------------------------------------------------------
    englisches Feld, um zu zeigen, dass Sprachen über eigene Tabellen gelöst werden sollten
 --------------------------------------------------------------------------------------------------------------------
	temporär NUTS_ID, um Problem zu zeigen - Mehrere Werte, zu starr, von Struktur unabhängige Statistik
 ------------------------------------------------------------------------------------------------------------------ */

CREATE TABLE Geographic_Units_Range (
  ID               INTEGER NOT NULL,
  Designation      VARCHAR(50) NOT NULL,
  Designation_engl VARCHAR(50) NULL,
  Is_City          SMALLINT NOT NULL,
  Has_Streets      SMALLINT NOT NULL,
  NUTS_ID          INTEGER,
  Description      VARCHAR(MAX)
  );

ALTER TABLE Geographic_Units_Range ADD CONSTRAINT pk_Geo_Units_Range PRIMARY KEY (ID);
ALTER TABLE Geographic_Units_Range ADD CONSTRAINT uk_Geo_Units_Range_Desc UNIQUE (designation);
ALTER TABLE Geographic_Units_Range ADD CONSTRAINT ck_Geo_Units_Range_Is_City CHECK (Is_City = 1 OR Is_City = 0);
ALTER TABLE Geographic_Units_Range ADD CONSTRAINT ck_Geo_Units_Range_Has_Streets CHECK (Has_Streets = 1 OR Has_Streets = 0);
ALTER TABLE Geographic_Units_Range ADD CONSTRAINT fk_Geo_Units_Range_NUTS FOREIGN KEY (NUTS_ID) REFERENCES NUTS_Range (ID);

/* ------------------------------------------------------------------------------------------------------------------
    Tabelle mit Regeln, wie Struktureinheiten und Statisktikdaten verbunden werden können
	Achtung: parallel mit Fehler in Geographic_Units_Range, Notwendigkeit Beziehungen zu erkennen und separate Tabellen zu machen
 ------------------------------------------------------------------------------------------------------------------ */

CREATE TABLE Geographic_Units_Nuts_Rules (
   Unit_Category INTEGER NOT NULL,
   NUTS_ID       INTEGER NOT NULL
   );

ALTER TABLE Geographic_Units_Nuts_Rules ADD CONSTRAINT pk_Unit_NUTS_Rules PRIMARY KEY (Unit_Category, NUTS_ID);
ALTER TABLE Geographic_Units_Nuts_Rules ADD CONSTRAINT fk_Unit_NUTS_Rules_Units FOREIGN KEY (Unit_Category) REFERENCES Geographic_Units_Range (ID);
ALTER TABLE Geographic_Units_Nuts_Rules ADD CONSTRAINT fk_Unit_NUTS_Rules_NUTS FOREIGN KEY (NUTS_ID) REFERENCES NUTS_Range (ID);

/* ------------------------------------------------------------------------------------------------------------------
    Tabelle mit Regeln, wie Struktureinheiten verknüpft werden können, festlegen von Regeln

	Achtung: parallel mit Fehler in Geographic_Units_Range, Notwendigkeit Beziehungen zu erkennen und separate Tabellen zu machen
 ------------------------------------------------------------------------------------------------------------------ */

CREATE TABLE Geographic_Units_Rules (
  Category         INTEGER NOT NULL,
  Parent_Category  INTEGER NOT NULL
  );

ALTER TABLE Geographic_Units_Rules ADD CONSTRAINT pk_Geo_Units_Rules PRIMARY KEY (Category, Parent_Category);
ALTER TABLE Geographic_Units_Rules ADD CONSTRAINT fk_Geo_Units_Rules_Category FOREIGN KEY (Category) REFERENCES Geographic_Units_Range (ID);  
ALTER TABLE Geographic_Units_Rules ADD CONSTRAINT fk_Geo_Units_Rules_Parent FOREIGN KEY (Parent_Category) REFERENCES Geographic_Units_Range (ID);  

/* ------------------------------------------------------------------------------------------------------------------
    Haupttabelle mit rekursiver geografischer Struktur
	Category mit Wertebereich
	Description ist Name der Einheit
	Achtung: hier mit Check- Bedingung über Function und Rules - Tabelle
	möglich auch Category für Parent mit aufzunehmen
 ------------------------------------------------------------------------------------------------------------------ */

CREATE TABLE Geographical_Structure (
  ID          INTEGER NOT NULL,
  Category    INTEGER NOT NULL,
  Parent_ID   INTEGER,
  Description VARCHAR(50)
  );

GO

CREATE FUNCTION Check_Geographic_Units_Rules (@id AS INTEGER, @Category AS INTEGER) RETURNS SMALLINT
BEGIN
   DECLARE @retval1 AS SMALLINT;
   SELECT @retval1 = count(*) 
   FROM Geographic_Units_Rules r 
   WHERE r.Parent_Category = (SELECT s.Category
                              FROM Geographical_Structure s 
                              WHERE s.ID = @id)
		   AND r.Category = @Category;
   RETURN @retval1;

   DECLARE @retval2 AS SMALLINT;
   SELECT @retval2 = count(*) 
   FROM Geographical_Structure s
   WHERE s.Parent_ID = @id
         AND NOT EXISTS (SELECT *
                         FROM Geographic_Units_Rules r 
                         WHERE r.Category = s.Category AND r.Parent_Category = @Category);
   DECLARE @retval SMALLINT;
   IF @retval1 > 0 AND @retval2 = 0
      SET @retval = 1;
   ELSE
      SET @retval = 0;
   
   RETURN @retval;
END;

GO

ALTER TABLE Geographical_Structure ADD CONSTRAINT pk_Geo_Structure PRIMARY KEY (ID);
ALTER TABLE Geographical_Structure ADD CONSTRAINT fk_Geo_Structure_Category FOREIGN KEY (Category) REFERENCES Geographic_Units_Range (ID);
ALTER TABLE Geographical_Structure ADD CONSTRAINT fk_Geo_Structure_Parent FOREIGN KEY (Parent_ID) REFERENCES Geographical_Structure (ID);
ALTER TABLE Geographical_Structure ADD CONSTRAINT ck_Geo_Structure_Rules CHECK (Parent_ID IS NULL OR dbo.Check_Geographic_Units_Rules(Parent_ID, Category) > 0);

GO

/* --------------------------------------------------------------------------------------------
   Definition einer Baumstruktur mit Hilfe einer rekursiven CTE
   CTE = Common Table Expressions, eingeführt in SQL 1999 Standard
   Oracle, Microsoft SQL Server, PostgreSQL, MySQL und SQLite unterstützen CTEs gemäß dem SQL-Standard
---------------------------------------------------------------------------------------------- */

CREATE VIEW tree_Geo_Structure AS
WITH FStruct AS (
  SELECT ID, Parent_ID, ID AS Super_ID, 0 AS Level
  FROM Geographical_Structure
  WHERE Parent_ID IS NULL

  UNION ALL

  SELECT s.ID, s.Parent_ID, c.Super_ID, c.Level + 1
  FROM Geographical_Structure s
  INNER JOIN FStruct c ON s.Parent_ID = c.ID
)
SELECT ID, Parent_ID, Super_ID, Level
FROM FStruct;

GO


CREATE VIEW view_Geo_Structure AS
SELECT s1.ID, s1.Description, s1.Category,
       STUFF((SELECT ', ' + s2.Description
              FROM Geographical_Structure s2
              WHERE s2.Parent_ID = s1.ID
			  ORDER BY s2.Description
              FOR XML PATH('')), 1, 2, '') AS Subordinates
FROM Geographical_Structure s1;

GO

/* ------------------------------------------------------------------------------------------------------------------
   Spezielle Sicht um zu zeigen, dass eine Veknüpfung von Daten so möglich ist, die alte Struktur herzustellen
 ------------------------------------------------------------------------------------------------------------------*/

CREATE VIEW view_Berlin AS
SELECT gs.ID, 
       p.Description AS Land,
	   NULL AS Region,
	   NULL AS Kreis,
       g.Description AS Bundesland,
       c.Description AS Stadt,
       s.Description AS Stadtbezirk,
       gs.Description AS Ortsteil
FROM Geographical_Structure gs
JOIN Geographical_Structure s ON gs.Parent_ID = s.ID AND s.Category = 8
JOIN Geographical_Structure c ON s.Parent_ID = c.ID AND c.Category = 5
JOIN Geographical_Structure g ON c.Parent_ID = g.ID AND g.Category = 2
JOIN Geographical_Structure p ON g.Parent_ID = p.ID AND p.Category = 1
WHERE gs.Category = 9;


GO


/* ------------------------------------------------------------------------------------------------------------------
   Tabelle für den Strassen 
 ------------------------------------------------------------------------------------------------------------------*/

CREATE TABLE Streets (
   ID          INTEGER NOT NULL,
   Street      VARCHAR(100) NOT NULL,
   Street_Date DATE
   );

ALTER TABLE Streets ADD CONSTRAINT pk_Streets PRIMARY KEY (ID);

/* ------------------------------------------------------------------------------------------------------------------
   Tabelle für die Zuordnung der Strassen zur geografischen Einheiten

 ------------------------------------------------------------------------------------------------------------------*/

CREATE TABLE Street_Unit_Mapping (
   Street_ID   INTEGER NOT NULL,
   Unit_ID     INTEGER NOT NULL
   );

ALTER TABLE Street_Unit_Mapping ADD CONSTRAINT pk_Streets_Units_Mapping PRIMARY KEY (Street_ID, Unit_ID);
ALTER TABLE Street_Unit_Mapping ADD CONSTRAINT fk_Streets_Units_Mapping_Streets FOREIGN KEY (Street_ID) REFERENCES Streets (ID);
ALTER TABLE Street_Unit_Mapping ADD CONSTRAINT fk_Streets_Units_Mapping_Units FOREIGN KEY (Unit_ID) REFERENCES Geographical_Structure (ID);

/* ------------------------------------------------------------------------------------------------------------------
   Tabelle, um Daten für Grundstücke zu speichern
   Um Verwechslung mit ähnlichen Entities Address zu vermeiden, wird "Parcel of Land" verwendet
   Viele Daten sind Bestandteil der Beziehungen des Grundstücks zur Strasse, bzw. anderen geografischen Einheiten
--------------------------------------------------------------------------------------------------------------------*/

CREATE TABLE Parcel_of_Land (
   ID          INTEGER NOT NULL,
   Parcel_Date DATE
   );

ALTER TABLE Parcel_of_Land ADD CONSTRAINT pk_Parcel PRIMARY KEY (ID);

/* ------------------------------------------------------------------------------------------------------------------
   Tabelle, um Grundstücke einer Straße zuzuordnen
   Hausnummer, Ergänzung und PLZ sind Bestandteil der Beziehung
-------------------------------------------------------------------------------------------------------------------*/
CREATE TABLE Parcel_Street_Mapping (
   Parcel_ID         INTEGER NOT NULL,
   Street_ID         INTEGER NOT NULL,
   ZIP_code          VARCHAR(10) NOT NULL,
   HouseNumber       INTEGER,
   HouseNumberSuffix VARCHAR(5)
   );

ALTER TABLE Parcel_Street_Mapping ADD CONSTRAINT pk_Street_Parcel_Mapping PRIMARY KEY (Parcel_ID, Street_ID);
ALTER TABLE Parcel_Street_Mapping ADD CONSTRAINT uk_Street_Parcel_Mapping_Number UNIQUE (Street_ID, HouseNumber, HouseNumberSuffix);
ALTER TABLE Parcel_Street_Mapping ADD CONSTRAINT fk_Street_Parcel_Mapping_Parcel FOREIGN KEY (Parcel_ID) REFERENCES Parcel_of_Land (ID);
ALTER TABLE Parcel_Street_Mapping ADD CONSTRAINT fk_Street_Parcel_Mapping_Street FOREIGN KEY (Street_ID) REFERENCES Streets (ID);

INSERT INTO NUTS_Range (ID, Designation, Description) VALUES
   (1, 'Land_Kz',     'NUTS Ebene 1, innerhalb Deutschlands bezogen auf die Bundesländer'),
   (2, 'Region_Kz',   'NUTS Ebene 2, Region innerhalb eines Landes, wird nicht von jedem Bundesland verwendet'),
   (3, 'Kreis_Kz',    'NUTS Ebene 3, die Kreise und kreisfreie Städte repräsentiert.'),
   (4, 'Gemeinde_Kz', 'NUTS Ebene 4, wird für Gemeinden und Städte auf niedrigerer Ebene verwendet.'),
   (5, 'Bezirk_Kz',   'Keine NUTS Nomenkladur. Identifikation für Stadtbezirke, speziell für Stadtstaatem wie Berlin, Hamburg und Bremen.'),
   (6, 'Ortsteil_Kz', 'Keine NUTS Nomenkladur. Identifikation für Ortsteile, speziell für Stadtstaaten. wie Berlin, Hamburg und Bremen.'),
   (7, 'Strasse_Kz',  'Keine NUTS Nomenkladur. Identifikation für Strassen innerhalb einer Stadt, Gemeinde, ...');
GO

INSERT INTO Geographic_Units_Range (ID, Designation, Designation_engl, Is_City, Has_Streets, NUTS_ID, Description) VALUES
   ( 1, 'Land',             'Country',          0, 0, NULL, 'Staat / Land'), 
   ( 2, 'Bundesland',       'Federal State',    0, 0, 1,    'Bundesland'),
   ( 3, 'Regionalregion',   'Regional Area',    0, 0, 2,    'Regionalregion'),
   ( 4, 'Kreis',            'District',         0, 0, 3,    'Kreis, Landkreis'),
   ( 5, 'kreisfreie Stadt', 'Independent city', 1, 1, 3,    'kreisfreie Stadt'),
   ( 6, 'Gemeinde',         'Municipality',     0, 0, 4,    'Gemeinde'),
   ( 7, 'Stadt',            'City',             1, 1, 4,    'Stadt'),
   ( 8, 'Stadtteil',        'City District',    0, 1, 5,    'Stadtteil innerhalb einer Stadt'),
   ( 9, 'Ortsteil',         'Neighborhood',     0, 1, 6,    'Ortsteil innerhalb einer Stadt, Stadtteil'),
   (10, 'Ort',              'Village',          1, 1, NULL, 'Ort / Ortsteil innerhalb einer Gemeinde');
GO

INSERT INTO Geographic_Units_Rules (Category, Parent_Category) VALUES
   (2, 1), (3, 2), (4, 2), (5, 2), (4, 3), (5, 3),
   (6, 4), (7, 4), (8, 5), (7, 6), (10, 6), (8, 7), (9, 8);
GO

INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (1, 1, NULL, 'Deutschland');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (2, 2, 1,    'Berlin');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (3, 5, 2,    'Berlin');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (4, 8, 3,    'Spandau');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (5, 9, 4,    'Gatow');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (6, 9, 4,    'Spandau');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (7, 9, 4,    'Wilhelmstadt');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (8, 9, 4,    'Kladow');
/*
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES 
   (1, 1, NULL, 'Deutschland'),
   (2, 2, 1, 'Berlin'),
   (3, 7, 2, 'Berlin'),
   (4, 8, 3, 'Spandau'),
   (5, 9, 4, 'Gatow'),
   (6, 9, 4, 'Spandau'),
   (7, 9, 4, 'Wilhelmstadt'),
   (8, 9, 4, 'Kladow');
*/
GO