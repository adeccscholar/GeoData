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
   
CREATE TABLE Brandenburg_Kreise (
    Land_ID          integer NULL,
    Kreis_ID         integer NULL,
    Kreis            varchar(75) NULL,  	
    Kreisstadt       varchar(75) NULL,
    Status           varchar(75) NULL,
    Abkuerzung       varchar(10) NULL,
	Breitengrad      float NULL,
	Laengengrad      float NULL
   );   
   
CREATE TABLE Brandenburg_Staedte (
	Land_ID          integer NULL,
	Kreis_ID         integer NULL,
	Gemeinde_ID      integer NULL,
	Stadt            varchar(75) NULL,
	Stadt_sorbisch   varchar(75) NULL,
	Abkuerzung_Kreis varchar(10) NULL,
	Status           varchar(75) NULL
   );
   
CREATE TABLE Brandenburg(
	Land_ID          integer NULL,
	Region_ID        integer NULL,
	Kreis_ID         integer NULL,
	Gemeinde_ID      integer NULL,
	Ortsteil_ID      integer NULL,
	Strasse_ID       integer NULL,
	HNR              integer NULL,	
	ADZ              varchar(5) NULL,
	Land             varchar(75) NULL,
	Kreis            varchar(75) NULL,
	Amt              varchar(75) NULL,
	Gemeinde         varchar(75) NULL,
	Ort              varchar(75) NULL,
	Strasse          varchar(75) NULL,
	PLZ              varchar(5) NULL,
	Latitude         float NULL,
	Longitude        float NULL
   );

CREATE VIEW Brandenburg_District_Township AS
SELECT Land_ID, Region_ID, Kreis_ID, Gemeinde_ID, Ortsteil_ID, Land, Kreis, Gemeinde, Ort, count(*) AS Anzahl
FROM Brandenburg
GROUP BY Land_ID, Region_ID, Kreis_ID, Gemeinde_ID, Ortsteil_ID, Land, Kreis, Gemeinde, Ort;


CREATE TABLE Berlin(
	Land_ID          integer NULL,
	Bezirk_ID        integer NULL,
	Ortsteil_ID      integer NULL,
	Strasse_ID       integer NULL,
	Land             varchar(75) NULL,
	Bezirk           varchar(75) NULL,
	Ortsteil         varchar(75) NULL,
	Strasse          varchar(75) NULL,
	PLZ              varchar(5) NULL,
	HNR              integer NULL,
	ADZ              varchar(5) NULL,
	Latitude         float NULL,
	Longitude        float NULL
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

INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 51, 'Brandenburg an der Havel', 'kreisfreie Stadt', 'BRB', 52.414000, 12.551900)
INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 52, 'Cottbus', 'kreisfreie Stadt', 'CB', 51.758600, 14.335600)
INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 53, 'Frankfurt (Oder)', 'kreisfreie Stadt', 'FF', 52.336100, 14.546100)
INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 54, 'Potsdam', 'kreisfreie Stadt', 'P', 52.390600, 13.064500)
INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Kreisstadt, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 60, 'Barnim', 'Eberswalde', 'Kreis', 'BAR', 52.834700, 13.827400);
INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Kreisstadt, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 61, 'Dahme-Spreewald', 'Lübben (Spreewald)', 'Kreis', 'LDS', 51.944500, 13.889400);
INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Kreisstadt, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 62, 'Elbe-Elster', 'Herzberg (Elster)', 'Kreis', 'EE', 51.694300, 13.222200);
INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Kreisstadt, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 63, 'Havelland', 'Rathenow', 'Kreis', 'HVL', 52.609300, 12.340900);
INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Kreisstadt, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 64, 'Märkisch-Oderland', 'Seelow', 'Kreis', 'MOL', 52.494700, 14.383300);
INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Kreisstadt, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 65, 'Oberhavel', 'Oranienburg', 'Kreis', 'OHV', 52.755400, 13.246400);
INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Kreisstadt, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 66, 'Oberspreewald-Lausitz', 'Senftenberg', 'Kreis', 'OSL', 51.521400, 14.001900);
INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Kreisstadt, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 67, 'Oder-Spree', 'Beeskow', 'Kreis', 'LOS', 52.171100, 14.248900);
INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Kreisstadt, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 68, 'Ostprignitz-Ruppin', 'Neuruppin', 'Kreis', 'OPR', 52.925800, 12.801800);
INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Kreisstadt, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 69, 'Potsdam-Mittelmark', 'Bad Belzig', 'Kreis', 'PM', 52.144200, 12.587400);
INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Kreisstadt, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 70, 'Prignitz', 'Perleberg', 'Kreis', 'PR', 53.072500, 11.864400);
INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Kreisstadt, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 71, 'Spree-Neiße', 'Forst (Lausitz)', 'Kreis', 'SPN', 51.729500, 14.634200);
INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Kreisstadt, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 72, 'Teltow-Fläming', 'Luckenwalde', 'Kreis', 'TF', 52.081100, 13.173900);
INSERT INTO Brandenburg_Kreise (Land_ID, Kreis_ID, Kreis, Kreisstadt, Status, Abkuerzung, Breitengrad, Laengengrad) VALUES(12, 73, 'Uckermark', 'Prenzlau', 'Kreis', 'UM', 53.317200, 53.317200);

INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Altlandsberg', NULL, 'MOL', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Angermünde', NULL, 'UM', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Bad Belzig', NULL, 'PM', 'Kreisstadt');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Bad Freienwalde (Oder)', NULL, 'MOL', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Bad Liebenwerda', NULL, 'EE', 'verbandsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Bad Wilsnack', NULL, 'PR', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Baruth/Mark', NULL, 'TF', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Beelitz', NULL, 'PM', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Beeskow', NULL, 'LOS', 'Kreisstadt');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Bernau bei Berlin', NULL, 'BAR', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Biesenthal', NULL, 'BAR', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Brandenburg an der Havel', NULL, 'BRB', 'kreisfrei');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Brück', NULL, 'PM', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Brüssow', NULL, 'UM', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Buckow (Märkische Schweiz)', NULL, 'MOL', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Calau', NULL, 'OSL', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Cottbus', 'Chóśebuz', 'CB', 'kreisfrei');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Dahme/Mark', NULL, 'TF', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Doberlug-Kirchhain', NULL, 'EE', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Döbern', NULL, 'SPN', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Drebkau', 'Drjowk', 'SPN', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Eberswalde', NULL, 'BAR', 'Kreisstadt');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Eisenhüttenstadt', NULL, 'LOS', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Elsterwerda', NULL, 'EE', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Erkner', NULL, 'LOS', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Falkenberg/Elster', NULL, 'EE', 'verbandsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Falkensee', NULL, 'HVL', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Finsterwalde', NULL, 'EE', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Forst (Lausitz)', NULL, 'SPN', 'Kreisstadt');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Frankfurt (Oder)', NULL, 'FF', 'kreisfrei');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Friedland', NULL, 'LOS', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Friesack', NULL, 'HVL', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Fürstenberg/Havel', NULL, 'OHV', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Fürstenwalde/Spree', NULL, 'LOS', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Gartz (Oder)', NULL, 'UM', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Golßen', NULL, 'LDS', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Gransee', NULL, 'OHV', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Großräschen', NULL, 'OSL', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Guben', NULL, 'SPN', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Havelsee', NULL, 'PM', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Hennigsdorf', NULL, 'OHV', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Herzberg (Elster)', NULL, 'EE', 'Kreisstadt');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Hohen Neuendorf', NULL, 'OHV', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Joachimsthal', NULL, 'BAR', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Jüterbog', NULL, 'TF', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Ketzin/Havel', NULL, 'HVL', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Königs Wusterhausen', NULL, 'LDS', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Kremmen', NULL, 'OHV', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Kyritz', NULL, 'OPR', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Lauchhammer', NULL, 'OSL', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Lebus', NULL, 'MOL', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Lenzen (Elbe)', NULL, 'PR', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Liebenwalde', NULL, 'OHV', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Lieberose', NULL, 'LDS', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Lindow (Mark)', NULL, 'OPR', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Lübbenau/Spreewald', 'Lubnjow/Błota', 'OSL', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Lübben (Spreewald)', NULL, 'LDS', 'Kreisstadt');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Luckau', NULL, 'LDS', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Luckenwalde', NULL, 'TF', 'Kreisstadt');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Ludwigsfelde', NULL, 'TF', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Lychen', NULL, 'UM', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Märkisch Buchholz', NULL, 'LDS', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Meyenburg', NULL, 'PR', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Mittenwalde', NULL, 'LDS', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Mühlberg/Elbe', NULL, 'EE', 'verbandsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Müllrose', NULL, 'LOS', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Müncheberg', NULL, 'MOL', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Nauen', NULL, 'HVL', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Neuruppin', NULL, 'OPR', 'Kreisstadt');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Neustadt (Dosse)', NULL, 'OPR', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Niemegk', NULL, 'PM', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Oderberg', NULL, 'BAR', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Oranienburg', NULL, 'OHV', 'Kreisstadt');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Ortrand', NULL, 'OSL', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Peitz', 'Picnjo', 'SPN', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Perleberg', NULL, 'PR', 'Kreisstadt');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Potsdam', NULL, 'P', 'kreisfrei');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Premnitz', NULL, 'HVL', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Prenzlau', NULL, 'UM', 'Kreisstadt');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Pritzwalk', NULL, 'PR', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Putlitz', NULL, 'PR', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Rathenow', NULL, 'HVL', 'Kreisstadt');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Rheinsberg', NULL, 'OPR', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Rhinow', NULL, 'HVL', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Ruhland', NULL, 'OSL', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Schlieben', NULL, 'EE', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Schönewalde', NULL, 'EE', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Schwarzheide', NULL, 'OSL', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Schwedt/Oder', NULL, 'UM', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Seelow', NULL, 'MOL', 'Kreisstadt');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Senftenberg', NULL, 'OSL', 'Kreisstadt');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Sonnewalde', NULL, 'EE', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Spremberg', 'Grodk', 'SPN', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Storkow (Mark)', NULL, 'LOS', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Strausberg', NULL, 'MOL', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Teltow', NULL, 'PM', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Templin', NULL, 'UM', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Teupitz', NULL, 'LDS', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Trebbin', NULL, 'TF', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Treuenbrietzen', NULL, 'PM', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Uebigau-Wahrenbrück', NULL, 'EE', 'verbandsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Velten', NULL, 'OHV', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Vetschau/Spreewald', 'Wětošow/Błota', 'OSL', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Welzow', NULL, 'SPN', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Werder (Havel)', NULL, 'PM', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Werneuchen', NULL, 'BAR', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Wildau', NULL, 'LDS', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Wittenberge', NULL, 'PR', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Wittstock/Dosse', NULL, 'OPR', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Wriezen', NULL, 'MOL', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Zehdenick', NULL, 'OHV', NULL);
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Ziesar', NULL, 'PM', 'amtsangehörig');
INSERT INTO Brandenburg_Staedte (Stadt, Stadt_Sorbisch, Abkuerzung_Kreis, Status) VALUES ('Zossen', NULL, 'TF', NULL);

/* SQL Server */
UPDATE Bbg_Stadt
SET Land_ID = Bbg_Kreis.Land_ID, Kreis_ID = Bbg_Kreis.Kreis_ID
FROM Brandenburg_Staedte Bbg_Stadt join Brandenburg_Kreise Bbg_Kreis ON Bbg_Kreis.Abkuerzung = Bbg_Stadt.Abkuerzung_Kreis;


update a
set a.gemeinde_id = b.gemeinde_id
from brandenburg_staedte a join 
   ( Select distinct land_id, kreis_id, gemeinde_id, Ortsteil_ID, Kreis, Gemeinde, Ort
     from brandenburg) b
	     on b.land_id = a.land_id and b.kreis_id  = a.kreis_id and a.stadt = b.gemeinde
where a.gemeinde_id is null

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

