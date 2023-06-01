Use Geodaten;


DROP TABLE Thueringen_Staedte;
DROP TABLE Thueringen_Kreise;

DROP VIEW vw_Thueringen;

DROP TABLE Thueringen;
DROP TABLE Thueringen_Schluessel;
GO



CREATE TABLE Thueringen_Schluessel (
   Satzart          varchar(20) NULL,
   Land_ID          integer NULL,
   Region_ID        integer NULL,
   Kreis_ID         integer NULL,
   Gemeinde_ID      integer NULL,
   Bezeichnung      varchar(75)
);

CREATE TABLE Thueringen (
   Land_ID          integer NULL,
   Region_ID        integer NULL,
   Kreis_ID         integer NULL,
   Gemeinde_ID      integer NULL,
   Strasse_ID       integer NULL,
   Strasse          varchar(75) NULL,
   HNR              integer NULL,	
   ADZ              varchar(5) NULL,
   PLZ              varchar(5) NULL,
   Laengengrad      float NULL,
   Breitengrad      float NULL
);

GO

CREATE VIEW vw_Thueringen AS
SELECT a.Land_ID, a.Region_ID, a.Kreis_ID, a.Gemeinde_ID, a.Strasse_ID,  
       b.Bezeichnung AS Land, c.Bezeichnung AS Kreis, d.Bezeichnung AS Gemeinde,
       a.Strasse, a.HNR, a.ADZ, a.PLZ, 
       a.Laengengrad, a.Breitengrad
FROM Thueringen a left join Thueringen_Schluessel b on (b.land_id = a.land_id and b.Satzart = 'Land')
                  left join Thueringen_Schluessel c on (c.land_id = a.land_id and c.Kreis_ID = a.Kreis_ID AND c.Satzart = 'Kreis')
				  left join Thueringen_Schluessel d on (d.land_id = a.land_id and d.Kreis_ID = a.Kreis_ID AND d.Gemeinde_ID = a.Gemeinde_ID AND d.Satzart = 'Gemeinde');

GO











CREATE TABLE Thueringen_Kreise (
   Kreis                   varchar(75) NULL,
   Abkuerzung              varchar(10) NULL,
   Art                     varchar(25) NULL,
   Kreisstadt              varchar(75) NULL,
   Kfz_Kennzeichen         varchar(100) NULL,
   Land_ID                 integer NULL,
   Kreis_ID                integer NULL,
   Breitengrad             float NULL,
   Laengengrad             float NULL,
   Verwaltung              varchar(75) NULL,
   Verwaltung_PLZ          varchar(5) NULL,
   Verwaltung_Ort          varchar(75) NULL,
   Verwaltung_Strasse      varchar(75) NULL,
   Verwaltung_Nummer       varchar(20) NULL,
   Verwaltung_Breitengrad  float NULL,
   Verwaltung_Laengegrad   float NULL
);

CREATE TABLE Thueringen_Staedte (
   Stadt                   varchar(75) NULL,
   Kreis                   varchar(75) NULL,
   Breitengrad             float NULL,
   Laengengrad             float NULL,
   Land_ID                 integer NULL,
   Kreis_ID                integer NULL,
   Gemeinde_ID             integer NULL
);





INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Erfurt', 'EF', 'kreisfreie Stadt', NULL, 'EF', 16, 51, 50.9847, 11.0299, 'Rathaus', '99084', 'Erfurt', 'Fischmarkt', '1', 50.9767, 11.0299);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Gera', 'G', 'kreisfreie Stadt', NULL, 'G', 16, 52, 50.8815, 12.0826, 'Rathaus', '07545', 'Gera', 'Markt', '1', 50.8774, 12.0769);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Jena', 'J', 'kreisfreie Stadt', NULL, 'J', 16, 53, 50.927, 11.5893, 'Rathaus', '07743', 'Jena', 'Am Anger', '15', 50.9271, 11.5892);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Suhl', 'SHL', 'kreisfreie Stadt', NULL, 'SHL', 16, 54, 50.6057, 10.6926, 'Rathaus', '98527', 'Suhl', 'Friedrich-König-Straße', '42', 50.6098, 10.6941);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Weimar', 'WE', 'kreisfreie Stadt', NULL, 'WE', 16, 55, 50.9807, 11.3297, 'Rathaus', '99423', 'Weimar', 'Markt', '1', 50.9795, 11.3235);

INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Altenburger Land', 'ABG', 'Kreis', 'Altenburg', 'ABG, SLN', 16, 77, 50.9837, 12.3691, 'Landratsamt', '04600', 'Altenburg', 'Lindenaustraße', '2', 50.9848, 12.4434);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Eichsfeld', 'EIC', 'Kreis', 'Heilbad Heiligenstadt', 'EIC, HIG, WBS', 16, 61, 51.4091, 10.0546, 'Landratsamt', '37308', 'Heiligenstadt', 'Kalteneberer Straße', '1', 51.3723, 10.1519);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Gotha', 'GTH', 'Kreis', 'Gotha', 'GTH', 16, 67, 50.9509, 10.7064, 'Landratsamt', '99867', 'Gotha', 'Hospitalstraße', '1', 50.9395, 10.7002);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Greiz', 'GRZ', 'Kreis', 'Greiz', 'GRZ, ZR', 16, 76, 50.8044, 12.1374, 'Landratsamt', '07973', 'Greiz', 'Carolinenstraße', '9', 50.6519, 12.1947);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Hildburghausen', 'HBN', 'Kreis', 'Hildburghausen', 'HBN', 16, 69, 50.4073, 10.7339, 'Landratsamt', '98646', 'Hildburghausen', 'Schleusinger Straße', '1', 50.427, 10.7249);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Ilm-Kreis', 'IK', 'Kreis', 'Arnstadt', 'IK, ARN, IL', 16, 70, 50.8662, 10.9487, 'Landratsamt', '99310', 'Arnstadt', 'Am Markt', '1', 50.8329, 10.9406);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Kyffhäuserkreis', 'KYF', 'Kreis', 'Sondershausen', 'KYF, ART, SDH', 16, 65, 51.4285, 11.1037, 'Landratsamt', '99706', 'Sondershausen', 'Karl-Marx-Straße', '26', 51.3567, 11.1001);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Nordhausen', 'NDH', 'Kreis', 'Nordhausen', 'NDH', 16, 62, 51.5039, 10.7819, 'Landratsamt', '99734', 'Nordhausen', 'Friedrich-Ebert-Straße', '42', 51.5018, 10.7975);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Saale-Holzland-Kreis', 'SHK', 'Kreis', 'Eisenberg', 'SHK, EIS, SRO', 16, 74, 50.9447, 11.6744, 'Landratsamt', '07607', 'Eisenberg', 'Carl-August-Jäger-Straße', '2', 50.9812, 11.9421);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Saale-Orla-Kreis', 'SOK', 'Kreis', 'Schleiz', 'SOK, LBS, PN, SCZ', 16, 75, 50.6008, 11.6944, 'Landratsamt', '07907', 'Schleiz', 'Wiesenstraße', '18', 50.6156, 11.8137);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Saalfeld-Rudolstadt', 'SLF', 'Kreis', 'Saalfeld', 'SLF, RU', 16, 73, 50.6321, 11.3724, 'Landratsamt', '07318', 'Saalfeld', 'Goethestraße', '1', 50.6381, 11.3422);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Schmalkalden-Meiningen', 'SM', 'Kreis', 'Meiningen', 'SM, MGN', 16, 66, 50.5705, 10.5576, 'Landratsamt', '98617', 'Meiningen', 'Bernhardstraße', '80', 50.5734, 10.4566);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Sömmerda', 'SÖM', 'Kreis', 'Sömmerda', 'SÖM', 16, 68, 51.1289, 11.1585, 'Landratsamt', '99610', 'Sömmerda', 'Friedrich-Schiller-Straße', '33', 51.1592, 11.1017);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Sonneberg', 'SON', 'Kreis', 'Sonneberg', 'SON, NH', 16, 72, 50.3575, 11.0929, 'Landratsamt', '96515', 'Sonneberg', 'Güterstraße', '33', 50.359, 11.1686);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Unstrut-Hainich-Kreis', 'UH', 'Kreis', 'Mühlhausen', 'UH, LSZ, MHL', 16, 64, 51.2318, 10.4808, 'Landratsamt', '99974', 'Mühlhausen', 'Schwanenteichpromenade', '9', 51.2064, 10.4499);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Wartburgkreis', 'WAK', 'Kreis', 'Bad Salzungen', 'WAK, EA, SLZ', 16, 63, 50.7924, 10.3874, 'Landratsamt', '36433', 'Bad Salzungen', 'Langenfelder Straße', '29', 50.8146, 10.4872);
INSERT INTO Thueringen_Kreise (Kreis,Abkuerzung,Art,Kreisstadt,Kfz_Kennzeichen,Land_ID,Kreis_ID,Breitengrad,Laengengrad,Verwaltung,Verwaltung_PLZ,Verwaltung_Ort,Verwaltung_Strasse,Verwaltung_Nummer,Verwaltung_Breitengrad,Verwaltung_Laengegrad) VALUES ('Weimarer Land', 'AP', 'Kreis', 'Apolda', 'AP, APD', 16, 71, 50.9704, 11.3467, 'Landratsamt', '99510', 'Apolda', 'Bahnhofstraße', '4', 51.0267, 11.5126);


INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Altenburg', 'Altenburger Land', 50.9853, 12.4366, 16, 77, 1);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Amt Creuzburg', 'Wartburgkreis', 50.9367, 10.2469, 16, 63, 104);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('An der Schmücke', 'Kyffhäuserkreis', 50.5611, 10.825, 16, 65, 88);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Apolda', 'Weimarer Land', 51.0251, 11.5124, 16, 71, 1);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Arnstadt', 'Ilm-Kreis', 50.8419, 10.9892, 16, 70, 4);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Stadt Artern', 'Kyffhäuserkreis', 51.3648, 11.2756, 16, 65, 86);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Auma-Weidatal', 'Greiz', 50.7415, 11.9609, 16, 76, 92);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Bad Berka', 'Weimarer Land', 50.8924, 11.2882, 16, 71, 3);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Bad Blankenburg', 'Saalfeld-Rudolstadt', 50.6982, 11.2181, 16, 73, 5);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Bad Frankenhausen/Kyffhäuser', 'Kyffhäuserkreis', 51.3519, 11.0957, 16, 65, 3);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Bad Köstritz', 'Greiz', 50.9572, 12.0237, 16, 76, 3);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Bad Langensalza', 'Unstrut-Hainich-Kreis', 51.1054, 10.6472, 16, 64, 3);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Bad Liebenstein', 'Wartburgkreis', 50.8441, 10.3266, 16, 63, 99);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Bad Lobenstein', 'Saale-Orla-Kreis', 50.4837, 11.5949, 16, 75, 62);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Bad Salzungen', 'Wartburgkreis', 50.8095, 10.2246, 16, 63, 3);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Bad Sulza', 'Weimarer Land', 51.0595, 11.6488, 16, 71, 4);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Bad Tennstedt', 'Unstrut-Hainich-Kreis', 51.0992, 10.6396, 16, 64, 4);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Berga/Elster', 'Greiz', 50.6522, 11.7019, 16, 76, 4);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Blankenhain', 'Weimarer Land', 50.8589, 11.4203, 16, 71, 8);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Stadt Bleicherode', 'Nordhausen', 51.4577, 10.7699, 16, 62, 66);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Brotterode-Trusetal', 'Schmalkalden-Meiningen', 50.8014, 10.3537, 16, 66, 74);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Bürgel', 'Saale-Holzland-Kreis', 50.9054, 11.7594, 16, 74, 9);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Clingen', 'Kyffhäuserkreis', 51.3172, 11.1616, 16, 65, 12);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Dingelstädt', 'Eichsfeld', 51.2699, 10.3535, 16, 61, 118);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Dornburg-Camburg', 'Saale-Holzland-Kreis', 50.9301, 11.6835, 16, 74, 11);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Ebeleben', 'Kyffhäuserkreis', 51.2382, 10.638, 16, 65, 14);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Eisenach', 'Wartburgkreis', 50.9771, 10.3183, 16, 63, 105);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Eisenberg', 'Saale-Holzland-Kreis', 50.9722, 11.9902, 16, 74, 18);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Eisfeld', 'Hildburghausen', 50.4137, 10.9627, 16, 69, 12);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Ellrich', 'Nordhausen', 51.6285, 10.8354, 16, 62, 5);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Erfurt', NULL, 50.9847, 11.0299, 16, 51, 0);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Friedrichroda', 'Gotha', 50.8603, 10.5169, 16, 67, 19);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Gebesee', 'Sömmerda', 51.1102, 11.1735, 16, 68, 14);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Gefell', 'Saale-Orla-Kreis', 50.5435, 11.6215, 16, 75, 131);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Geisa', 'Wartburgkreis', 50.7232, 9.9726, 16, 63, 32);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Gera', NULL, 50.8773, 12.0841, 16, 52, 0);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Gößnitz', 'Altenburger Land', 50.9398, 12.5116, 16, 77, 12);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Gotha', 'Gotha', 50.9513, 10.6997, 16, 67, 29);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Gräfenthal', 'Saalfeld-Rudolstadt', 50.5746, 11.2743, 16, 73, 28);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Greiz', 'Greiz', 50.6566, 12.1997, 16, 76, 22);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Greußen', 'Kyffhäuserkreis', 51.2401, 10.9401, 16, 65, 89);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Großbreitenbach', 'Ilm-Kreis', 50.6594, 11.0311, 16, 70, 58);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Heilbad Heiligenstadt', 'Eichsfeld', 51.3836, 10.1293, 16, 61, 45);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Heldburg', 'Hildburghausen', 50.3798, 10.7112, 16, 69, 63);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Heringen/Helme', 'Nordhausen', 50.9526, 10.1602, 16, 62, 64);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Hermsdorf', 'Saale-Holzland-Kreis', 50.9515, 11.9812, 16, 74, 41);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Hildburghausen', 'Hildburghausen', 50.4271, 10.7333, 16, 69, 24);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Hirschberg', 'Saale-Orla-Kreis', 50.6702, 11.1147, 16, 75, 46);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Hohenleuben', 'Greiz', 50.7613, 12.0745, 16, 76, 29);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Ilmenau', 'Ilm-Kreis', 50.6812, 10.9087, 16, 70, 29);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Jena', NULL, 50.9281, 11.5862, 16, 53, 0);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Kahla', 'Saale-Holzland-Kreis', 50.7913, 11.5884, 16, 74, 44);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Kaltennordheim', 'Schmalkalden-Meiningen', 50.6319, 10.3175, 16, 66, 95);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Kölleda', 'Sömmerda', 51.1441, 11.2121, 16, 68, 34);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Königsee', 'Saalfeld-Rudolstadt', 50.6311, 11.1304, 16, 73, 112);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Kranichfeld', 'Weimarer Land', 50.8468, 11.2328, 16, 71, 46);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Lauscha', 'Sonneberg', 50.4488, 11.1704, 16, 72, 11);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Lehesten', 'Saalfeld-Rudolstadt', 50.4584, 11.3625, 16, 73, 46);

INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Leinefelde-Worbis', 'Eichsfeld', 51.3788, 10.3547, 16, 61, 115);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Leutenberg', 'Saalfeld-Rudolstadt', 50.6333, 11.4941, 16, 73, 106);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Lucka', 'Altenburger Land', 51.0529, 12.4196, 16, 77, 28);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Magdala', 'Weimarer Land', 50.9101, 11.4281, 16, 71, 53);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Meiningen', 'Schmalkalden-Meiningen', 50.5721, 10.4197, 16, 66, 42);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Meuselwitz', 'Altenburger Land', 51.0602, 12.2737, 16, 77, 32);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Mühlhausen/Thüringen', 'Unstrut-Hainich-Kreis', 51.2112, 10.4417, 16, 64, 46);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Münchenbernsdorf', 'Greiz', 50.8368, 11.9677, 16, 76, 49);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Neuhaus am Rennweg', 'Sonneberg', 50.4894, 11.1183, 16, 72, 13);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Neumark', 'Weimarer Land', 50.9066, 10.8983, 16, 71, 61);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Neustadt an der Orla', 'Saale-Orla-Kreis', 50.7476, 11.8027, 16, 75, 73);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Nordhausen', 'Nordhausen', 51.5031, 10.7901, 16, 62, 41);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Nottertal-Heilinger Höhen', 'Unstrut-Hainich-Kreis', 50.9067, 11.3787, 16, 64, 77);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Oberhof', 'Schmalkalden-Meiningen', 50.7066, 10.7344, 16, 66, 47);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Ohrdruf', 'Gotha', 50.8559, 10.7164, 16, 67, 53);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Orlamünde', 'Saale-Holzland-Kreis', 50.8889, 11.5914, 16, 74, 65);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Plaue', 'Ilm-Kreis', 50.8372, 11.1757, 16, 70, 43);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Pößneck', 'Saale-Orla-Kreis', 50.6963, 11.5955, 16, 75, 85);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Ranis', 'Saale-Orla-Kreis', 50.6631, 11.6189, 16, 75, 88);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Rastenberg', 'Sömmerda', 51.0758, 11.2821, 16, 68, 42);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Römhild', 'Hildburghausen', 50.3945, 10.7176, 16, 69, 62);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Ronneburg', 'Greiz', 50.8664, 12.1838, 16, 76, 61);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Roßleben-Wiehe', 'Kyffhäuserkreis', 51.2314, 11.4317, 16, 65, 87);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Rudolstadt', 'Saalfeld-Rudolstadt', 50.7184, 11.3307, 16, 73, 76);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Ruhla', 'Wartburgkreis', 50.8939, 10.3997, 16, 63, 66);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Saalburg-Ebersdorf', 'Saale-Orla-Kreis', 50.5455, 11.6612, 16, 75, 135);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Saalfeld/Saale', 'Saalfeld-Rudolstadt', 50.6397, 11.3493, 16, 73, 77);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Schalkau', 'Sonneberg', 50.4059, 11.1774, 16, 72, 15);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Schkölen', 'Saale-Holzland-Kreis', 51.0077, 11.7467, 16, 74, 116);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Schleiz', 'Saale-Orla-Kreis', 50.5901, 11.8212, 16, 75, 98);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Schleusingen', 'Hildburghausen', 50.5512, 10.8024, 16, 69, 43);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Schmalkalden, Kurort', 'Schmalkalden-Meiningen', 50.7123, 10.4659, 16, 66, 63);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Schmölln', 'Altenburger Land', 50.8893, 12.3542, 16, 77, 43);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Schwarzatal', 'Saalfeld-Rudolstadt', 50.6674, 11.0773, 16, 73, 113);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Sömmerda', 'Sömmerda', 51.1697, 11.0993, 16, 68, 51);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Sondershausen', 'Kyffhäuserkreis', 51.3659, 10.8782, 16, 65, 67);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Sonneberg', 'Sonneberg', 50.3572, 11.1696, 16, 72, 18);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Stadtilm', 'Ilm-Kreis', 50.8002, 11.0556, 16, 70, 48);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Stadtroda', 'Saale-Holzland-Kreis', 50.8965, 11.7434, 16, 74, 94);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Steinach', 'Sonneberg', 50.4734, 11.1369, 16, 72, 19);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Steinbach-Hallenberg, Kurort', 'Schmalkalden-Meiningen', 50.7033, 10.5714, 16, 66, 69);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Suhl', NULL, 50.6143, 10.6892, 16, 54, 0);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Tambach-Dietharz/Thür. Wald', 'Gotha', 50.8279, 10.6013, 16, 67, 65);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Tanna', 'Saale-Orla-Kreis', 50.4173, 11.7335, 16, 75, 132);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Themar', 'Hildburghausen', 50.4818, 10.6414, 16, 69, 51);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Treffurt', 'Wartburgkreis', 51.0476, 10.2422, 16, 63, 76);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Triptis', 'Saale-Orla-Kreis', 50.8237, 11.9361, 16, 75, 116);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Ummerstadt', 'Hildburghausen', 50.2917, 10.4882, 16, 69, 52);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Vacha', 'Wartburgkreis', 50.8201, 10.0983, 16, 63, 82);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Waltershausen', 'Gotha', 50.8812, 10.4941, 16, 67, 72);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Wasungen', 'Schmalkalden-Meiningen', 50.7232, 10.6987, 16, 66, 86);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Weida', 'Greiz', 50.7782, 12.0676, 16, 76, 79);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Weimar', NULL, 50.9825, 11.3297, 16, 55, 0);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Weißensee', 'Sömmerda', 51.1239, 11.1417, 16, 68, 58);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Werra-Suhl-Tal', 'Wartburgkreis', 50.7711, 10.4236, 16, 63, 103);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Wurzbach', 'Saale-Orla-Kreis', 50.4896, 11.6357, 16, 75, 133);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Zella-Mehlis', 'Schmalkalden-Meiningen', 50.6497, 10.7027, 16, 66, 92);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Zeulenroda-Triebes', 'Greiz', 50.6631, 11.9664, 16, 76, 87);
INSERT INTO Thueringen_Staedte (Stadt, Kreis, Breitengrad, Laengengrad, Land_ID, Kreis_ID, Gemeinde_ID) VALUES ('Ziegenrück', 'Saale-Orla-Kreis', 50.6482, 11.7176, 16, 75, 127);


