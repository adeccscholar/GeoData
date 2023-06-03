USE Geodaten;

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

CREATE VIEW vw_Sachsen_Land AS
  SELECT DISTINCT Land_ID, Bezeichnung as Land
  FROM Sachsen_Schluessel
  WHERE Satzart = 'Land';


CREATE VIEW vw_Sachsen_Regionen AS
  SELECT DISTINCT Land_ID, Region_ID, SUBSTRING(Bezeichnung, 15, LEN(Bezeichnung) - 14) AS Region
  FROM Sachsen_Schluessel
  WHERE Satzart = 'Region';

  
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
  FROM vw_Sachsen_Gemeinden a LEFT JOIN vw_Sachsen_Kreise b ON (b.Land_ID = a.Land_ID AND b.Kreis_ID = a.Kreis_ID)
  WHERE a.Art = 'Stadt';
UNION
  SELECT SUBSTRING(Bezeichnung, 18, LEN(Bezeichnung) - 17) AS Gemeinde, NULL AS Kreis, "Kreisfreie Stadt" AS Art,
         Land_ID, Region_ID, Kreis_ID, 0 AS Gemeinde_ID 
  FROM Sachsen_Schluessel
  WHERE Satzart = 'Kreis'  AND Bezeichnung LIKE 'Kreisfreie Stadt%';


CREATE TABLE Sachsen_Kreise (
   Kreis                 VARCHAR(75) NULL,
   Abkuerzung            VARCHAR(10) NULL,
   Art                   VARCHAR(25) NULL,
   Kreisstadt            VARCHAR(75) NULL,
   Kfz_Kennzeichen       VARCHAR(150) NULL,
   Land_ID               INTEGER NULL,
   Region_ID             INTEGER NULL,
   Kreis_ID              INTEGER NULL,
   Breitengrad           FLOAT NULL,
   Laengengrad           FLOAT NULL,
   Verwaltung            VARCHAR(75) NULL,
   Verw_Adr_PLZ          VARCHAR(5) NULL,
   Verw_Adr_Ort          VARCHAR(75) NULL,
   Verw_Adr_Strasse      VARCHAR(75) NULL,
   Verw_Adr_Nummer       VARCHAR(20) NULL,
   Verw_Adr_Breitengrad  FLOAT NULL,
   Verw_Adr_Laengegrad   FLOAT NULL
   );

CREATE TABLE Sachsen_Staedte (
   Stadt                 VARCHAR(75) NULL,
   Kreis                 VARCHAR(75) NULL,
   Art                   VARCHAR(25) NULL,
   Land_ID               INTEGER NULL,
   Region_ID             INTEGER NULL,
   Kreis_ID              INTEGER NULL,
   Gemeinde_ID           INTEGER NULL,
   Breitengrad           FLOAT NULL,
   Laengengrad           FLOAT NULL,
   Verwaltung            VARCHAR(75) NULL,
   Verw_Adr_PLZ          VARCHAR(5) NULL,
   Verw_Adr_Ort          VARCHAR(75) NULL,
   Verw_Adr_Strasse      VARCHAR(75) NULL,
   Verw_Adr_Nummer       VARCHAR(20) NULL,
   Verw_Adr_Breitengrad  FLOAT NULL,
   Verw_Adr_Laengegrad   FLOAT NULL
   );

INSERT INTO Sachsen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Region_ID, Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verw_Adr_PLZ,Verw_Adr_Ort,Verw_Adr_Strasse,Verw_Adr_Nummer,Verw_Adr_Breitengrad,Verw_Adr_Laengegrad) VALUES ('Bautzen', 'BZ', 'Kreis', 'Bautzen', 'BZ, BIW, HY, KM', 14, 6, 25, 51.1835, 14.4344, 'Landratsamt Bautzen', '02625', 'Bautzen', 'Bahnhofstraße', '9', 51.1807, 14.4284);
INSERT INTO Sachsen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Region_ID, Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verw_Adr_PLZ,Verw_Adr_Ort,Verw_Adr_Strasse,Verw_Adr_Nummer,Verw_Adr_Breitengrad,Verw_Adr_Laengegrad) VALUES ('Chemnitz', 'C', 'kreisfreie Stadt', NULL, 'C', 14, 5, 11, 50.8321, 12.9253, 'Stadt Chemnitz', '09106', 'Chemnitz', 'Markt', '1', 50.8297, 12.9219);
INSERT INTO Sachsen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Region_ID, Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verw_Adr_PLZ,Verw_Adr_Ort,Verw_Adr_Strasse,Verw_Adr_Nummer,Verw_Adr_Breitengrad,Verw_Adr_Laengegrad) VALUES ('Dresden', 'DD', 'kreisfreie Stadt', NULL, 'DD', 14, 6, 12, 51.0493, 13.7384, 'Stadt Dresden', '01067', 'Dresden', 'Theaterplatz', '1', 51.0527, 13.7409);
INSERT INTO Sachsen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Region_ID, Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verw_Adr_PLZ,Verw_Adr_Ort,Verw_Adr_Strasse,Verw_Adr_Nummer,Verw_Adr_Breitengrad,Verw_Adr_Laengegrad) VALUES ('Görlitz', 'GR', 'Kreis', 'Görlitz', 'GR, LÖB, NOL, NY, WSW, ZI', 14, 6, 26, 51.1244, 14.9822, 'Landratsamt Görlitz', '02826', 'Görlitz', 'Bahnhofstraße', '24', 51.1543, 14.9953);
INSERT INTO Sachsen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Region_ID, Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verw_Adr_PLZ,Verw_Adr_Ort,Verw_Adr_Strasse,Verw_Adr_Nummer,Verw_Adr_Breitengrad,Verw_Adr_Laengegrad) VALUES ('Leipzig', 'L', 'kreisfreie Stadt', NULL, 'L', 14, 7, 13, 51.3396, 12.3731, 'Stadt Leipzig', '04109', 'Leipzig', 'Martin-Luther-Ring', '4-6', 51.3396, 12.3731);
INSERT INTO Sachsen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Region_ID, Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verw_Adr_PLZ,Verw_Adr_Ort,Verw_Adr_Strasse,Verw_Adr_Nummer,Verw_Adr_Breitengrad,Verw_Adr_Laengegrad) VALUES ('Leipzig', 'L', 'Kreis', 'Borna', 'L, BNA, GHA, GRM, MTL, WUR', 14, 7, 29, 51.2543, 12.5576, 'Landratsamt Leipzig', '04552', 'Borna', 'Brauhausstraße', '18', 51.1275, 12.4313);
INSERT INTO Sachsen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Region_ID, Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verw_Adr_PLZ,Verw_Adr_Ort,Verw_Adr_Strasse,Verw_Adr_Nummer,Verw_Adr_Breitengrad,Verw_Adr_Laengegrad) VALUES ('Meißen', 'MEI', 'Kreis', 'Meißen', 'MEI, RG, GRH, DL, DW, FLÖ, HC, KM, MW, RL, TL, TO, WR, ZI', 14, 6, 27, 51.1687, 13.4712, 'Landratsamt Meißen', '01662', 'Meißen', 'Hafenstraße', '40', 51.1614, 13.4686);
INSERT INTO Sachsen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Region_ID, Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verw_Adr_PLZ,Verw_Adr_Ort,Verw_Adr_Strasse,Verw_Adr_Nummer,Verw_Adr_Breitengrad,Verw_Adr_Laengegrad) VALUES ('Mittelsachsen', 'FG', 'Kreis', 'Freiberg', ' FG, BED, DL, FLÖ, HC, MW, RL', 14, 5, 22, 51.0326, 13.2718, 'Landratsamt Mittelsachsen', '09599', 'Freiberg', 'Frauensteiner Straße', '43', 50.9255, 13.3179);
INSERT INTO Sachsen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Region_ID, Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verw_Adr_PLZ,Verw_Adr_Ort,Verw_Adr_Strasse,Verw_Adr_Nummer,Verw_Adr_Breitengrad,Verw_Adr_Laengegrad) VALUES ('Nordsachsen', 'TDO', 'Kreis', 'Torgau', 'TDO, DZ, EB, OZ, TG', 14, 7, 30, 51.4427, 13.5687, 'Landratsamt Nordsachsen', '04860', 'Torgau', 'August-Bebel-Straße', '1', 51.5615, 13.0032);
INSERT INTO Sachsen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Region_ID, Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verw_Adr_PLZ,Verw_Adr_Ort,Verw_Adr_Strasse,Verw_Adr_Nummer,Verw_Adr_Breitengrad,Verw_Adr_Laengegrad) VALUES ('Sächsische Schweiz-Osterzgebirge', 'PIR', 'Kreis', 'Pirna', 'PIR, DW, FTL, SEB', 14, 6, 28, 50.9369, 13.9261, 'Landratsamt Pirna', '01796', 'Pirna', 'Schlosshof', '2', 50.9567, 13.9433);
INSERT INTO Sachsen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Region_ID, Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verw_Adr_PLZ,Verw_Adr_Ort,Verw_Adr_Strasse,Verw_Adr_Nummer,Verw_Adr_Breitengrad,Verw_Adr_Laengegrad) VALUES ('Vogtlandkreis', 'V', 'Kreis', 'Plauen', 'V', 14, 5, 23, 50.4912, 12.3689, 'Landratsamt Vogtlandkreis', '08523', 'Plauen', 'Postplatz', '5', 50.499, 12.1377);
INSERT INTO Sachsen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Region_ID, Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verw_Adr_PLZ,Verw_Adr_Ort,Verw_Adr_Strasse,Verw_Adr_Nummer,Verw_Adr_Breitengrad,Verw_Adr_Laengegrad) VALUES ('Zwickau', 'Z', 'Kreis', 'Zwickau', 'Z, GC, HOT, WDA', 14, 5, 24, 50.7334, 12.4473, 'Landratsamt Zwickau', '08056', 'Zwickau', 'Peter-Breuer-Straße', '12', 50.7334, 12.4473);

