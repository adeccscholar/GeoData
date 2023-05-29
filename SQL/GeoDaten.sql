/*
MS SQL
25.05.2023 17:06:33,439: inserting data for Brandenburg started ...
import data, done in 2:15.678 sec sec
25.05.2023 17:08:49,118: import Brandenburg finished

25.05.2023 23:37:02,020: inserting data for Brandenburg started ...
25.05.2023 23:39:23,440: inserting data for Brandenburg, done in 2:21.420 sec
25.05.2023 23:39:23,441: inserting data for Brandenburg finished.

MySQL
25.05.2023 17:11:24,494: inserting data for Brandenburg started ...
import data, done in 36:9.945 sec sec
25.05.2023 17:47:34,438: import Brandenburg finished

25.05.2023 21:06:45,811: inserting data for Brandenburg started ...
25.05.2023 21:43:35,442: inserting data for Brandenburg, done in 36:49.631 sec
25.05.2023 21:43:35,443: inserting data for Brandenburg finished.
*/
USE Geodaten;



DROP VIEW Brandenburg_District_Township;
DROP Table Brandenburg;
DROP Table Berlin;
DROP Table Deutschland;

CREATE TABLE Deutschland(
	ID               integer NULL,
	Land             varchar(75) NULL,
	Hauptstadt       varchar(75) NULL,
	Status           varchar(75) NULL,
	Abkuerzung       varchar(10) NULL,
	Breitengrad      float NULL,
	Laengengrad      float NULL
   );
   
CREATE TABLE Verwaltungen (
    Schluessel       varchar(75) NULL,      
    Kategorie        varchar(75) NULL,   
    Bezug            varchar(75) NULL,           
    Bezeichnung      varchar(75) NULL,
    Strasse          varchar(75) NULL,     	
    Strasse_Nummer   varchar(20) NULL,     	
    PLZ              varchar( 5) NULL,    	
    Stadt            varchar(75) NULL,       	
	Breitengrad      float NULL,
	Laengengrad      float NULL
   );
   



INSERT INTO Deutschland (ID, Land, Hauptstadt, Abkuerzung, Status, Breitengrad, Laengengrad) VALUES (1, 'Schleswig-Holstein', 'Kiel', 'SH', 'Bundesland', 54.322708, 10.135555);
INSERT INTO Deutschland (ID, Land, Hauptstadt, Abkuerzung, Status, Breitengrad, Laengengrad) VALUES (2, 'Hamburg', 'Hamburg', 'HH', 'Stadtstaat', 53.551086, 9.993682);
INSERT INTO Deutschland (ID, Land, Hauptstadt, Abkuerzung, Status, Breitengrad, Laengengrad) VALUES (3, 'Niedersachsen', 'Hannover', 'NI', 'Bundesland', 52.375891, 9.732010);
INSERT INTO Deutschland (ID, Land, Hauptstadt, Abkuerzung, Status, Breitengrad, Laengengrad) VALUES (4, 'Bremen', 'Bremen', 'HB', 'Stadtstaat', 53.075820, 8.807165);
INSERT INTO Deutschland (ID, Land, Hauptstadt, Abkuerzung, Status, Breitengrad, Laengengrad) VALUES (5, 'Nordrhein-Westfalen', 'Düsseldorf', 'NW', 'Bundesland', 51.227741, 6.773456);
INSERT INTO Deutschland (ID, Land, Hauptstadt, Abkuerzung, Status, Breitengrad, Laengengrad) VALUES (6, 'Hessen', 'Wiesbaden', 'HE', 'Bundesland', 50.082583, 8.245351);
INSERT INTO Deutschland (ID, Land, Hauptstadt, Abkuerzung, Status, Breitengrad, Laengengrad) VALUES (7, 'Rheinland-Pfalz', 'Mainz', 'RP', 'Bundesland', 50.002966, 8.247253);
INSERT INTO Deutschland (ID, Land, Hauptstadt, Abkuerzung, Status, Breitengrad, Laengengrad) VALUES (8, 'Baden-Württemberg', 'Stuttgart', 'BW', 'Bundesland', 48.775845, 9.182932);
INSERT INTO Deutschland (ID, Land, Hauptstadt, Abkuerzung, Status, Breitengrad, Laengengrad) VALUES (9, 'Bayern', 'München', 'BY', 'Freistaat', 48.135125, 11.581981);
INSERT INTO Deutschland (ID, Land, Hauptstadt, Abkuerzung, Status, Breitengrad, Laengengrad) VALUES (10, 'Saarland', 'Saarbrücken', 'SL', 'Bundesland', 49.240157, 6.996932);
INSERT INTO Deutschland (ID, Land, Hauptstadt, Abkuerzung, Status, Breitengrad, Laengengrad) VALUES (11, 'Berlin', 'Berlin', 'BE', 'Stadtstaat', 52.520008, 13.404954);
INSERT INTO Deutschland (ID, Land, Hauptstadt, Abkuerzung, Status, Breitengrad, Laengengrad) VALUES (12, 'Brandenburg', 'Potsdam', 'BB', 'Bundesland', 52.400930, 13.059139);
INSERT INTO Deutschland (ID, Land, Hauptstadt, Abkuerzung, Status, Breitengrad, Laengengrad) VALUES (13, 'Mecklenburg-Vorpommern', 'Schwerin', 'MV', 'Bundesland', 53.629150, 11.417079);
INSERT INTO Deutschland (ID, Land, Hauptstadt, Abkuerzung, Status, Breitengrad, Laengengrad) VALUES (14, 'Sachsen', 'Dresden', 'SN', 'Freistaat', 51.050408, 13.737262);
INSERT INTO Deutschland (ID, Land, Hauptstadt, Abkuerzung, Status, Breitengrad, Laengengrad) VALUES (15, 'Sachsen-Anhalt', 'Magdeburg', 'ST', 'Bundesland', 52.120533, 11.627624);
INSERT INTO Deutschland (ID, Land, Hauptstadt, Abkuerzung, Status, Breitengrad, Laengengrad) VALUES (16, 'Thüringen', 'Erfurt', 'TH', 'Freistaat', 50.978709, 11.032829);


/* SQL Server */
UPDATE Bbg_Stadt
SET Land_ID = Bbg_Kreis.Land_ID, Kreis_ID = Bbg_Kreis.Kreis_ID
FROM Brandenburg_Staedte Bbg_Stadt join Brandenburg_Kreise Bbg_Kreis ON Bbg_Kreis.Abkuerzung = Bbg_Stadt.Abkuerzung_Kreis;


update a
set a.gemeinde_id = b.gemeinde_id
from brandenburg_staedte a left join 
   ( Select distinct land_id, kreis_id, gemeinde_id, Ortsteil_ID, Kreis, Gemeinde, Ort
     from brandenburg) b
	     on b.land_id = a.land_id and b.kreis_id  = a.kreis_id and a.stadt = b.gemeinde


/* MySQL
SET SQL_SAFE_UPDATES = 0;

UPDATE Brandenburg_Staedte a
JOIN Brandenburg_Kreise b ON b.Abkuerzung = a.Abkuerzung_Kreis
SET a.Land_ID = b.Land_ID, a.Kreis_ID = b.Kreis_ID
WHERE a.Land_ID IS NULL;

UPDATE brandenburg_staedte a
JOIN (
  SELECT DISTINCT land_id, kreis_id, gemeinde_id, Ortsteil_ID, Kreis, Gemeinde, Ort
  FROM brandenburg
) b ON b.land_id = a.land_id AND b.kreis_id = a.kreis_id AND a.stadt = b.gemeinde
SET a.gemeinde_id = b.gemeinde_id
WHERE a.gemeinde_id IS NULL;

COMMIT;
*/


