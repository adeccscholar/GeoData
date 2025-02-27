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

IF OBJECT_ID('view_Geo_Structure_Leaves_with_Path', 'V') IS NOT NULL
BEGIN
DROP VIEW view_Geo_Structure_Leaves_with_Path;
END

IF OBJECT_ID('view_Geo_Structure_Predecessors', 'V') IS NOT NULL
BEGIN
DROP VIEW view_Geo_Structure_Predecessors;
END

IF OBJECT_ID('view_Geo_Structure_Subordinates', 'V') IS NOT NULL
BEGIN
DROP VIEW view_Geo_Structure_Subordinates;
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
	NUTS (Nomenclature des unités territoriales statistiques) 
	hierarchisches System, das von Eurostat verwendet wird, um statistische Regionen in der EU zu definieren
	Achtung, unterhalb von NUTS gibt es eine LAU Ebene (Local Administrative Units) 
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
ALTER TABLE Geographic_Units_Range ADD CONSTRAINT uk_Geo_Units_Range_Desc UNIQUE (Designation);
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

/* ------------------------------------------------------------------------------------------------------------------
   Funktion, ob zu überprüfen, ob mit der ParentID für die kategorie die Regeln erfüllt sind
   wird später als Check- Bedingung verwendet, um Regeln der Struktur zu ermöglichen
   Parameter ID : Parent ID in der Struktur
             Category : Kategorie des Knoten, der gepüft wird
 -------------------------------------------------------------------------------------------------------------------*/
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

/* ------------------------------------------------------------------------------------------------------------------
   Sicht um Knoten mit ihren irekten Nachfolgern auszugeben, verwendet Geographical_Structure und STUFF
   ! Entfernen der XML Strukturdaten, da STUFF eine XML- Struktur zurückgibt
 ------------------------------------------------------------------------------------------------------------------*/

CREATE VIEW view_Geo_Structure AS
SELECT s1.ID, s1.Description, s1.Category,
    STUFF( (SELECT ', ' + s2.Description
            FROM Geographical_Structure s2
            WHERE s2.Parent_ID = s1.ID
            ORDER BY s2.Description
         FOR XML PATH(''), TYPE).value('.', 'VARCHAR(MAX)'), 1, 2, '') AS Subordinates
FROM Geographical_Structure s1;

GO

/* ------------------------------------------------------------------------------------------------------------------
   Sicht um alle Nachfolger eines Knoten mit ID, Category udn Describtion (alle mit Prefex Sub) abzuzeigen
 ------------------------------------------------------------------------------------------------------------------*/
CREATE VIEW view_Geo_Structure_Subordinates AS
   SELECT s1.ID, s2.ID AS SubID, s2.Category AS SubCategory, s2.Description AS SubDescription
   FROM Geographical_Structure s1 join Geographical_Structure s2 ON s2.Parent_ID = s1.ID;
GO

/* ------------------------------------------------------------------------------------------------------------------
   Sicht um alle Vorgänger eines Knoten mit ID als SubID zu finden, inklusive dem Knoten selber (Level = 0)
   Level ist Abstand vom gesuchten Knoten
 ------------------------------------------------------------------------------------------------------------------*/
CREATE VIEW view_Geo_Structure_Predecessors AS
WITH BackCTE AS (
       SELECT t.ID AS ID, t.ID AS BackID, t.Parent_ID, 0 AS Level
       FROM tree_Geo_Structure t

       UNION ALL
	  
       SELECT b.ID, t.ID AS BackID, t.Parent_ID, b.Level + 1
       FROM BackCTE b
       JOIN tree_Geo_Structure t ON t.ID = b.Parent_ID
       )
   SELECT ID AS ID, BackID, [Level]
   FROM BackCTE;

GO

/* ------------------------------------------------------------------------------------------------------------------
   Sicht um Endknoten (Leaves) einer Struktur mit der Super_ID zu finden mit dem vollständigen Path zum Element
   Description des Leaves, FullDescription ist Description mit vollständigen Path in Klammern
 ------------------------------------------------------------------------------------------------------------------*/
CREATE VIEW view_Geo_Structure_Leaves_with_Path AS
WITH PathCTE AS (
    SELECT a.ID, s.Category, a.Parent_ID, a.Super_ID, a.Level, s.Description,
          CAST('' AS VARCHAR(MAX)) AS [Path]
    FROM tree_Geo_Structure a JOIN Geographical_Structure s ON s.ID = a.ID
    WHERE a.Parent_ID IS NULL

    UNION ALL

    SELECT a.ID, s.Category, a.Parent_ID, a.Super_ID, a.Level, s.Description,
           CAST(IIF(p.[Path] = '', p.Description, p.[Path] + ', ' + p.Description) AS VARCHAR(MAX) ) AS [Path]
    FROM tree_Geo_Structure a JOIN Geographical_Structure s ON s.ID = a.ID
                              JOIN PathCTE p ON a.Parent_ID = p.ID
    )
  SELECT p.ID, p.Category, p.Super_ID, p.Description, p.Description + ' (' + p.[Path] + ')' AS FullDescription
  FROM PathCTE p  
  WHERE -- p.Super_ID = 1 AND  
        NOT EXISTS ( SELECT 1 
                     FROM tree_Geo_Structure b 
                     WHERE b.Parent_ID = p.ID
                   );

GO

/* ------------------------------------------------------------------------------------------------------------------
   Spezielle Sicht um zu zeigen, dass eine Veknüpfung von Daten so möglich ist, die alte Struktur herzustellen
 ------------------------------------------------------------------------------------------------------------------*/

CREATE VIEW view_Berlin AS
SELECT gs.ID, 
       p.Description AS Land,
	   NULL AS Region,
	   g.Description AS Bundesland,
       NULL AS Kreis,
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
   (4, 'Gemeinde_Kz', 'LAU Klassikation (wie NUTS Ebene 4), wird für Gemeinden und Städte auf niedrigerer Ebene verwendet.'),
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

-- Land Deutschland
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (   1,  1, NULL,   'Deutschland');
-- Bundesland Berlin
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (   2,  2,   1,    'Berlin');
-- Stadt Berlin
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (   3,  5,   2,    'Berlin');
-- Berliner Stadtbezirke
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (   4,  8,   3,    'Mitte');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (   5,  8,   3,    'Friedrichshain-Kreuzberg');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (   6,  8,   3,    'Pankow');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (   7,  8,   3,    'Charlottenburg-Wilmersdorf');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (   8,  8,   3,    'Spandau');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (   9,  8,   3,    'Steglitz-Zehlendorf');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  10,  8,   3,    'Tempelhof-Schöneberg');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  11,  8,   3,    'Neukölln');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  12,  8,   3,    'Treptow-Köpenick');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  13,  8,   3,    'Marzahn-Hellersdorf');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  14,  8,   3,    'Lichtenberg');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  15,  8,   3,    'Reinickendorf');
-- Berlin Mitte
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  16,  9,   4,    'Mitte');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  17,  9,   4,    'Moabit');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  18,  9,   4,    'Hansaviertel');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  19,  9,   4,    'Tiergarten');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  20,  9,   4,    'Wedding');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  21,  9,   4,    'Gesundbrunnen');
-- Berlin Friedrichshain-Kreuzberg
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  22,  9,   5,    'Friedrichshain');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  23,  9,   5,    'Kreuzberg');
-- Berlin Pankow
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  24,  9,   6,    'Prenzlauer Berg');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  25,  9,   6,    'Weißensee');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  26,  9,   6,    'Blankenburg');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  27,  9,   6,    'Heinersdorf');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  28,  9,   6,    'Karow');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  29,  9,   6,    'Stadtrandsiedlung Malchow');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  30,  9,   6,    'Pankow');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  31,  9,   6,    'Blankenfelde');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  32,  9,   6,    'Buch');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  33,  9,   6,    'Französisch Buchholz');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  34,  9,   6,    'Niederschönhausen');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  35,  9,   6,    'Rosenthal');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  36,  9,   6,    'Wilhelmsruh');
-- Berlin Charlottenburg-Wilmersdorf
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  37,  9,   7,    'Charlottenburg');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  38,  9,   7,    'Wilmersdorf');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  39,  9,   7,    'Schmargendorf');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  40,  9,   7,    'Grunewald');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  41,  9,   7,    'Westend');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  42,  9,   7,    'Charlottenburg-Nord');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  43,  9,   7,    'Halensee');
-- Berlin Spandau
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  44,  9,   8,    'Spandau');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  45,  9,   8,    'Haselhorst');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  46,  9,   8,    'Siemensstadt');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  47,  9,   8,    'Staaken');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  48,  9,   8,    'Gatow');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  49,  9,   8,    'Kladow');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  50,  9,   8,    'Hakenfelde');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  51,  9,   8,    'Falkenhagener Feld');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  52,  9,   8,    'Wilhelmstadt');
-- Berlin Steglitz-Zehlendorf
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  53,  9,   9,    'Steglitz');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  54,  9,   9,    'Lichterfelde');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  55,  9,   9,    'Lankwitz');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  56,  9,   9,    'Zehlendorf');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  57,  9,   9,    'Dahlem');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  58,  9,   9,    'Nikolassee');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  59,  9,   9,    'Wannsee');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  60,  9,   9,    'Schlachtensee');
-- Berlin Tempelhof-Schöneberg
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  61,  9,  10,    'Schöneberg');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  62,  9,  10,    'Friedenau');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  63,  9,  10,    'Tempelhof');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  64,  9,  10,    'Mariendorf');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  65,  9,  10,    'Marienfelde');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  66,  9,  10,    'Lichtenrade');
-- Berlin Neukölln
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  67,  9,  11,    'Neukölln');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  68,  9,  11,    'Britz');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  69,  9,  11,    'Buckow');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  70,  9,  11,    'Rudow');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  71,  9,  11,    'Gropiusstadt');
-- Berlin Treptow-Köpenick
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  72,  9,  12,    'Alt-Treptow');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  73,  9,  12,    'Plänterwald');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  74,  9,  12,    'Baumschulenweg');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  75,  9,  12,    'Johannisthal');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  76,  9,  12,    'Niederschöneweide');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  77,  9,  12,    'Altglienicke');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  78,  9,  12,    'Adlershof');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  79,  9,  12,    'Bohnsdorf');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  80,  9,  12,    'Oberschöneweide');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  81,  9,  12,    'Köpenick');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  82,  9,  12,    'Friedrichshagen');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  83,  9,  12,    'Rahnsdorf');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  84,  9,  12,    'Grünau');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  85,  9,  12,    'Müggelheim');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  86,  9,  12,    'Schmöckwitz');
-- Berlin Marzahn-Hellersdorf
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  87,  9,  13,    'Marzahn');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  88,  9,  13,    'Biesdorf');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  89,  9,  13,    'Kaulsdorf');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  90,  9,  13,    'Mahlsdorf');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  91,  9,  13,    'Hellersdorf');
-- Berlin Lichtenberg
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  92,  9,  14,    'Friedrichsfelde');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  93,  9,  14,    'Karlshorst');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  94,  9,  14,    'Lichtenberg');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  95,  9,  14,    'Falkenberg');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  96,  9,  14,    'Malchow');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  97,  9,  14,    'Wartenberg');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  98,  9,  14,    'Neu-Hohenschönhausen');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES (  99,  9,  14,    'Alt-Hohenschönhausen');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES ( 100,  9,  14,    'Fennpfuhl');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES ( 101,  9,  14,    'Rummelsburg');
-- Berlin Reinickendorf
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES ( 102,  9,  15,    'Reinickendorf');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES ( 103,  9,  15,    'Tegel');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES ( 104,  9,  15,    'Konradshöhe');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES ( 105,  9,  15,    'Heiligensee');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES ( 106,  9,  15,    'Frohnau');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES ( 107,  9,  15,    'Hermsdorf');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES ( 108,  9,  15,    'Waidmannslust');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES ( 109,  9,  15,    'Lübars');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES ( 110,  9,  15,    'Wittenau');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES ( 111,  9,  15,    'Märkisches Viertel');
INSERT INTO Geographical_Structure (ID, Category, Parent_ID, Description) VALUES ( 112,  9,  15,    'Borsigwalde');

GO