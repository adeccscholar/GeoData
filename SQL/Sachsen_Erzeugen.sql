Use Geodaten;

CREATE TABLE Sachsen_Schluessel (
   Satzart          VARCHAR(20) NULL,
   Land_ID          INTEGER NULL,
   Region_ID        INTEGER NULL,
   Kreis_ID         INTEGER NULL,
   Gemeinde_ID      INTEGER NULL,
   Ortsteil_ID      INTEGER NULL,
   Bezeichnung      VARCHAR(75)
   );


CREATE TABLE Sachsen (
   Strasse          VARCHAR(75) NULL,
   Nummer           INTEGER NULL,
   Zusatz           VARCHAR(20) NULL,
   PLZ              VARCHAR(5) NULL,
   Ort              VARCHAR(75) NULL,
   Ortsteil         VARCHAR(75) NULL,  
   Land_ID          INTEGER NULL,
   Region_ID        INTEGER NULL,
   Kreis_ID         INTEGER NULL,
   Gemeinde_ID      INTEGER NULL,
   Ortsteil_ID      INTEGER NULL,
   Strasse_ID       INTEGER NULL,
   Laengengrad      FLOAT NULL,
   Breitengrad      FLOAT NULL
   );


CREATE VIEW vw_Sachsen AS
  SELECT a.Strasse, a.Nummer, a.Zusatz, a.PLZ, a.Ort, a.Ortsteil,
                  a.Land_ID, a.Region_ID, a.Kreis_ID, a.Gemeinde_ID, a.Ortsteil_ID, a.Strasse_ID, 
				  a.Laengengrad, a.Breitengrad,
				  b.Bezeichnung AS Land, c.Bezeichnung AS Region, d.Bezeichnung AS Kreis, e.Bezeichnung AS Gemeinde,
				  f.Bezeichnung AS Ortsteil_X
  FROM Sachsen a LEFT JOIN Sachsen_Schluessel b ON (b.Land_ID = a.Land_ID AND b.Satzart = 'Land')
                 LEFT JOIN Sachsen_Schluessel c ON (c.Land_ID = a.Land_ID AND c.Region_ID = a.Region_ID AND c.Satzart = 'Region')
	             LEFT JOIN Sachsen_Schluessel d ON (d.Land_ID = a.Land_ID AND d.Region_ID = a.Region_ID AND d.Kreis_ID = a.Kreis_ID AND d.Satzart = 'Kreis')
                 LEFT JOIN Sachsen_Schluessel e ON (e.Land_ID = a.Land_ID AND e.Region_ID = a.Region_ID AND e.Kreis_ID = a.Kreis_ID AND e.Gemeinde_ID = a.Gemeinde_ID AND e.Satzart = 'Gemeinde')
		         LEFT JOIN Sachsen_Schluessel f ON (f.Land_ID = a.Land_ID AND f.Region_ID = a.Region_ID AND f.Kreis_ID = a.Kreis_ID AND f.Gemeinde_ID = a.Gemeinde_ID AND f.Ortsteil_ID = a.Ortsteil_ID AND f.Satzart = 'Ortsteil')


CREATE VIEW vw_Sachsen_Kreise AS
  SELECT Land_ID, Region_ID, Kreis_ID, SUBSTRING(Bezeichnung, 18, LEN(Bezeichnung) - 17) AS Kreis, 'kreisfrei' AS ART 
  FROM Sachsen_Schluessel
  WHERE Satzart = 'Kreis'  AND Bezeichnung LIKE 'Kreisfreie Stadt%'
UNION
  SELECT Land_ID, Region_ID, Kreis_ID, SUBSTRING(Bezeichnung, 11, LEN(Bezeichnung) - 10) AS Kreis, 'Landkreis' AS ART 
  FROM Sachsen_Schluessel
  WHERE Satzart = 'Kreis' AND Bezeichnung LIKE 'Landkreis%'
UNION
  SELECT Land_ID, Region_ID, Kreis_ID, Bezeichnung AS Kreis, 'Kreis' AS ART 
  FROM Sachsen_Schluessel
  WHERE Satzart = 'Kreis' AND NOT (Bezeichnung LIKE 'Landkreis%'OR Bezeichnung LIKE 'Kreisfreie Stadt%');


CREATE VIEW vw_Sachsen_Gemeinden AS
  SELECT Land_ID, Region_ID, Kreis_ID, Gemeinde_ID, SUBSTRING(Bezeichnung, 7, LEN(Bezeichnung) - 6) AS Gemeinde, 'Stadt' AS ART
  FROM Sachsen_Schluessel
  WHERE Satzart = 'Gemeinde' AND Bezeichnung LIKE 'Stadt %'
UNION
  SELECT Land_ID, Region_ID, Kreis_ID, Gemeinde_ID, Bezeichnung AS Gemeinde, 'Gemeinde' AS ART
  FROM Sachsen_Schluessel
  WHERE Satzart = 'Gemeinde' AND
        NOT Bezeichnung LIKE 'Stadt %';


CREATE VIEW vw_Sachsen_Staedte AS
  SELECT a.Gemeinde, b.Kreis, b.Art, a.Land_ID, a.Region_ID, a.Kreis_ID, a.Gemeinde_ID 
  FROM vw_Sachsen_Gemeinden a LEFT JOIN vw_Sachsen_Kreise b ON (b.Land_ID = a.Land_ID and b.Kreis_ID = a.Kreis_ID)
  WHERE a.Art = 'Stadt';
