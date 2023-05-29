
DROP VIEW vw_Berliner_Strassen;
DROP VIEW vw_Berliner_Strassen_Bezirk;
DROP VIEW vw_Berliner_Strassen_Ortsteile;
DROP VIEW vw_Berliner_Ortsteile;
DROP VIEW vw_Berliner_Bezirke;

DROP TABLE Berlin;

DROP TABLE Berliner_Ortsteile
DROP TABLE Berliner_Stadtbezirke

CREATE TABLE Berliner_Stadtbezirke (
    Stadtbezirk        varchar(75) NULL,
    Abkuerzung         varchar(10) NULL,
    Bezirk_ID          integer NULL,
    Breite_Mitte       float NULL,
    Laenge_Mitte       float NULL,
    Rathaus            varchar(75) NULL,
    Rathaus_PLZ        varchar(5) NULL,
    Rathaus_Ort        varchar(75) NULL,
    Rathaus_Strasse    varchar(75) NULL,
    Rathaus_Nummer     varchar(20) NULL,
    Rathaus_Breite     float NULL,
    Rathaus_Laenge     float NULL
);
   

CREATE TABLE Berliner_Ortsteile (
    Land_ID      integer NULL,
    Bezirk_ID    integer NULL, 
    Ortsteil_ID  integer NULL, 
    Bezirk       varchar(75) NULL, 
    Ortsteil     varchar(75) NULL, 
    Breite       float NULL, 
    Laenge        float NULL
);
   
CREATE TABLE Berlin (
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

CREATE VIEW vw_Berliner_Bezirke
AS
SELECT DISTINCT Land_ID, Bezirk_ID, Land, Bezirk
FROM Berlin;


CREATE VIEW vw_Berliner_Ortsteile
AS
SELECT DISTINCT Land_ID, Bezirk_ID, Ortsteil_ID, Land, Bezirk, Ortsteil
FROM Berlin;


CREATE VIEW vw_Berliner_Strassen_Ortsteile
AS
SELECT DISTINCT Land_ID, Bezirk_ID,  Ortsteil_ID, Strasse_ID, Land, Bezirk, Ortsteile, Strasse
FROM Berlin;


CREATE VIEW vw_Berliner_Strassen_Bezirk
AS
SELECT DISTINCT Land_ID, Bezirk_ID, Strasse_ID, Land, Bezirk, Strasse
FROM Berlin;


CREATE VIEW vw_Berliner_Strassen
AS
SELECT DISTINCT Land_ID, Strasse_ID, Land, Strasse
FROM Berlin;


INSERT INTO Berliner_Stadtbezirke (Stadtbezirk,Abkuerzung,Bezirk_ID,Breite_Mitte,Laenge_Mitte,Rathaus,Rathaus_PLZ,Rathaus_Ort,Rathaus_Strasse,Rathaus_Nummer,Rathaus_Breite,Rathaus_Laenge) VALUES ('Mitte','MI',1,52.522905,13.37536,'Rotes Rathaus','10178','Berlin','Rathausstraße','15',52.517378,13.409549);
INSERT INTO Berliner_Stadtbezirke (Stadtbezirk,Abkuerzung,Bezirk_ID,Breite_Mitte,Laenge_Mitte,Rathaus,Rathaus_PLZ,Rathaus_Ort,Rathaus_Strasse,Rathaus_Nummer,Rathaus_Breite,Rathaus_Laenge) VALUES ('Friedrichshain-Kreuzberg','FDK',2,52.507856,13.450524,'Rathaus Friedrichshain-Kreuzberg','10969','Berlin','Frankfurter Allee','35-37',52.505428,13.444956);
INSERT INTO Berliner_Stadtbezirke (Stadtbezirk,Abkuerzung,Bezirk_ID,Breite_Mitte,Laenge_Mitte,Rathaus,Rathaus_PLZ,Rathaus_Ort,Rathaus_Strasse,Rathaus_Nummer,Rathaus_Breite,Rathaus_Laenge) VALUES ('Pankow','PA',3,52.575607,13.425345,'Rathaus Pankow','13156','Berlin','Breite Straße','24A',52.564098,13.404712);
INSERT INTO Berliner_Stadtbezirke (Stadtbezirk,Abkuerzung,Bezirk_ID,Breite_Mitte,Laenge_Mitte,Rathaus,Rathaus_PLZ,Rathaus_Ort,Rathaus_Strasse,Rathaus_Nummer,Rathaus_Breite,Rathaus_Laenge) VALUES ('Charlottenburg-Wilmersdorf','CW',4,52.493034,13.309527,'Rathaus Charlottenburg-Wilmersdorf','10585','Berlin','Otto-Suhr-Allee','100',52.505939,13.295589);
INSERT INTO Berliner_Stadtbezirke (Stadtbezirk,Abkuerzung,Bezirk_ID,Breite_Mitte,Laenge_Mitte,Rathaus,Rathaus_PLZ,Rathaus_Ort,Rathaus_Strasse,Rathaus_Nummer,Rathaus_Breite,Rathaus_Laenge) VALUES ('Spandau','SP',5,52.532738,13.202738,'Rathaus Spandau','13597','Berlin','Carl-Schurz-Straße','2/6',52.534228,13.201968);
INSERT INTO Berliner_Stadtbezirke (Stadtbezirk,Abkuerzung,Bezirk_ID,Breite_Mitte,Laenge_Mitte,Rathaus,Rathaus_PLZ,Rathaus_Ort,Rathaus_Strasse,Rathaus_Nummer,Rathaus_Breite,Rathaus_Laenge) VALUES ('Steglitz-Zehlendorf','SZ',6,52.437407,13.235389,'Rathaus Steglitz','12169','Berlin','Schloßstraße','37',52.457402,13.299266);
INSERT INTO Berliner_Stadtbezirke (Stadtbezirk,Abkuerzung,Bezirk_ID,Breite_Mitte,Laenge_Mitte,Rathaus,Rathaus_PLZ,Rathaus_Ort,Rathaus_Strasse,Rathaus_Nummer,Rathaus_Breite,Rathaus_Laenge) VALUES ('Tempelhof-Schöneberg','TS',7,52.456696,13.378567,'Rathaus Schöneberg','10825','Berlin','John-F.-Kennedy-Platz','1',52.484937,13.349126);
INSERT INTO Berliner_Stadtbezirke (Stadtbezirk,Abkuerzung,Bezirk_ID,Breite_Mitte,Laenge_Mitte,Rathaus,Rathaus_PLZ,Rathaus_Ort,Rathaus_Strasse,Rathaus_Nummer,Rathaus_Breite,Rathaus_Laenge) VALUES ('Neukölln','NK',8,52.43937,13.458079,'Rathaus Neukölln','12043','Berlin','Karl-Marx-Straße','83',52.475938,13.437934);
INSERT INTO Berliner_Stadtbezirke (Stadtbezirk,Abkuerzung,Bezirk_ID,Breite_Mitte,Laenge_Mitte,Rathaus,Rathaus_PLZ,Rathaus_Ort,Rathaus_Strasse,Rathaus_Nummer,Rathaus_Breite,Rathaus_Laenge) VALUES ('Treptow-Köpenick','TK',9,52.426747,13.573816,'Rathaus Köpenick','12555','Berlin','Alt-Köpenick','21',52.452114,13.576106);
INSERT INTO Berliner_Stadtbezirke (Stadtbezirk,Abkuerzung,Bezirk_ID,Breite_Mitte,Laenge_Mitte,Rathaus,Rathaus_PLZ,Rathaus_Ort,Rathaus_Strasse,Rathaus_Nummer,Rathaus_Breite,Rathaus_Laenge) VALUES ('Marzahn-Hellersdorf','MH',10,52.52948,13.597586,'Rathaus Marzahn','12679','Berlin','Helene-Weigel-Platz','8',52.541502,13.586758);
INSERT INTO Berliner_Stadtbezirke (Stadtbezirk,Abkuerzung,Bezirk_ID,Breite_Mitte,Laenge_Mitte,Rathaus,Rathaus_PLZ,Rathaus_Ort,Rathaus_Strasse,Rathaus_Nummer,Rathaus_Breite,Rathaus_Laenge) VALUES ('Lichtenberg','LB',11,52.5285,13.493551,'Rathaus Lichtenberg','10365','Berlin','Möllendorffstraße','6',52.529024,13.502508);
INSERT INTO Berliner_Stadtbezirke (Stadtbezirk,Abkuerzung,Bezirk_ID,Breite_Mitte,Laenge_Mitte,Rathaus,Rathaus_PLZ,Rathaus_Ort,Rathaus_Strasse,Rathaus_Nummer,Rathaus_Breite,Rathaus_Laenge) VALUES ('Reinickendorf','RD',12,52.595237,13.287497,'Rathaus Reinickendorf','13435','Berlin','Eichborndamm','215-239',52.596303,13.299512);


INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 1, 101,'Mitte',                      'Mitte', 52.5179, 13.4044);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 1, 102,'Mitte',                      'Moabit', 52.5301, 13.3421);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 1, 103,'Mitte',                      'Hansaviertel', 52.5206, 13.3386);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 1, 104,'Mitte',                      'Tiergarten', 52.5095, 13.3572);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 1, 105,'Mitte',                      'Wedding', 52.5501, 13.3417);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 1, 106,'Mitte',                      'Gesundbrunnen', 52.5487, 13.3845);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 2, 201,'Friedrichshain-Kreuzberg',   'Friedrichshain', 52.5159, 13.4543);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 2, 202,'Friedrichshain-Kreuzberg',   'Kreuzberg', 52.4972, 13.4113);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 3, 301,'Pankow',                     'Prenzlauer Berg', 52.5379, 13.4219);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 3, 302,'Pankow',                     'Weißensee', 52.5542, 13.4562);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 3, 303,'Pankow',                     'Blankenburg', 52.5973, 13.4634);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 3, 304,'Pankow',                     'Heinersdorf', 52.5793, 13.4337);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 3, 305,'Pankow',                     'Karow', 52.6182, 13.4717);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 3, 306,'Pankow',                     'Stadtrandsiedlung Malchow', 52.6019, 13.4857);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 3, 307,'Pankow',                     'Pankow', 52.5702, 13.4079);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 3, 308,'Pankow',                     'Blankenfelde', 52.5699, 13.4393);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 3, 309,'Pankow',                     'Buch', 52.6364, 13.5044);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 3, 310,'Pankow',                     'Französisch Buchholz', 52.6161, 13.4039);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 3, 311,'Pankow',                     'Niederschönhausen', 52.5828, 13.4002);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 3, 312,'Pankow',                     'Rosenthal', 52.5964, 13.3826);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 3, 313,'Pankow',                     'Wilhelmsruh', 52.5973, 13.3794);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 4, 401,'Charlottenburg-Wilmersdorf', 'Charlottenburg', 52.5166, 13.3082);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 4, 402,'Charlottenburg-Wilmersdorf', 'Wilmersdorf', 52.4913, 13.3127);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 4, 403,'Charlottenburg-Wilmersdorf', 'Schmargendorf', 52.4696, 13.2777);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 4, 404,'Charlottenburg-Wilmersdorf', 'Grunewald', 52.4866, 13.2519);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 4, 405,'Charlottenburg-Wilmersdorf', 'Westend', 52.5155, 13.2836);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 4, 406,'Charlottenburg-Wilmersdorf', 'Charlottenburg-Nord', 52.5428, 13.2872);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 4, 407,'Charlottenburg-Wilmersdorf', 'Halensee', 52.4966, 13.2931);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 5, 501,'Spandau',                    'Spandau', 52.5354, 13.1988);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 5, 502,'Spandau',                    'Haselhorst', 52.5435, 13.2005);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 5, 503,'Spandau',                    'Siemensstadt', 52.5307, 13.2597);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 5, 504,'Spandau',                    'Staaken', 52.5323, 13.1304);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 5, 505,'Spandau',                    'Gatow', 52.4807, 13.1263);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 5, 506,'Spandau',                    'Kladow', 52.4361, 13.1482);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 5, 507,'Spandau',                    'Hakenfelde', 52.5411, 13.1725);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 5, 508,'Spandau',                    'Falkenhagener Feld', 52.5631, 13.1363);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 5, 509,'Spandau',                    'Wilhelmstadt', 52.5203, 13.1907);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 6, 601,'Steglitz-Zehlendorf',        'Steglitz', 52.4575, 13.2979);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 6, 602,'Steglitz-Zehlendorf',        'Lichterfelde', 52.4373, 13.2875);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 6, 603,'Steglitz-Zehlendorf',        'Lankwitz', 52.4346, 13.3322);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 6, 604,'Steglitz-Zehlendorf',        'Zehlendorf', 52.4337, 13.2574);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 6, 605,'Steglitz-Zehlendorf',        'Dahlem', 52.4573, 13.2933);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 6, 606,'Steglitz-Zehlendorf',        'Nikolassee', 52.4322, 13.2106);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 6, 607,'Steglitz-Zehlendorf',        'Wannsee', 52.4207, 13.1552);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 6, 608,'Steglitz-Zehlendorf',        'Schlachtensee', 52.4338, 13.1764);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 7, 701,'Tempelhof-Schöneberg',       'Schöneberg', 52.4829, 13.3525);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 7, 702,'Tempelhof-Schöneberg',       'Friedenau', 52.4729, 13.3339);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 7, 703,'Tempelhof-Schöneberg',       'Tempelhof', 52.4685, 13.4042);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 7, 704,'Tempelhof-Schöneberg',       'Mariendorf', 52.4392, 13.3853);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 7, 705,'Tempelhof-Schöneberg',       'Marienfelde', 52.4204, 13.3629);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 7, 706,'Tempelhof-Schöneberg',       'Lichtenrade', 52.3995, 13.4079);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 8, 801,'Neukölln<',                  'Neukölln', 52.4814, 13.4377);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 8, 802,'Neukölln<',                  'Britz', 52.4559, 13.4421);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 8, 803,'Neukölln<',                  'Buckow', 52.4319, 13.4685);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 8, 804,'Neukölln<',                  'Rudow', 52.4216, 13.5025);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 8, 805,'Neukölln<',                  'Gropiusstadt', 52.4197, 13.4606);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 9, 901,'Treptow-Köpenick',           'Alt-Treptow', 52.4934, 13.4611);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 9, 902,'Treptow-Köpenick',           'Plänterwald', 52.4884, 13.4764);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 9, 903,'Treptow-Köpenick',           'Baumschulenweg', 52.4667, 13.5027);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 9, 904,'Treptow-Köpenick',           'Johannisthal', 52.4446, 13.5259);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 9, 905,'Treptow-Köpenick',           'Niederschöneweide', 52.4558, 13.4997);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 9, 906,'Treptow-Köpenick',           'Altglienicke', 52.4045, 13.5527);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 9, 907,'Treptow-Köpenick',           'Adlershof', 52.4379, 13.5372);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 9, 908,'Treptow-Köpenick',           'Bohnsdorf', 52.4044, 13.6101);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 9, 909,'Treptow-Köpenick',           'Oberschöneweide', 52.4627, 13.5133);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 9, 910,'Treptow-Köpenick',           'Köpenick', 52.4545, 13.5766);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 9, 911,'Treptow-Köpenick',           'Friedrichshagen', 52.4428, 13.6161);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 9, 912,'Treptow-Köpenick',           'Rahnsdorf', 52.4194, 13.6825);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 9, 913,'Treptow-Köpenick',           'Grünau', 52.4138, 13.5883);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 9, 914,'Treptow-Köpenick',           'Müggelheim', 52.4007, 13.6402);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11, 9, 915,'Treptow-Köpenick',           'Schmöckwitz', 52.3678, 13.6315);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,10,1001,'Marzahn-Hellersdorf',        'Marzahn', 52.5368, 13.5736);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,10,1002,'Marzahn-Hellersdorf',        'Biesdorf', 52.4984, 13.5545);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,10,1003,'Marzahn-Hellersdorf',        'Kaulsdorf', 52.5001, 13.5993);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,10,1004,'Marzahn-Hellersdorf',        'Mahlsdorf', 52.4786, 13.6164);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,10,1005,'Marzahn-Hellersdorf',        'Hellersdorf', 52.5315, 13.5971);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,11,1101,'Lichtenberg',                'Friedrichsfelde', 52.5022, 13.5088);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,11,1102,'Lichtenberg',                'Karlshorst', 52.4756, 13.5355);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,11,1103,'Lichtenberg',                'Lichtenberg', 52.5177, 13.4965);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,11,1104,'Lichtenberg',                'Falkenberg', 52.5382, 13.5786);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,11,1106,'Lichtenberg',                'Malchow', 52.5727, 13.4852);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,11,1107,'Lichtenberg',                'Wartenberg', 52.5654, 13.5604);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,11,1109,'Lichtenberg',                'Neu-Hohenschönhausen', 52.5708, 13.4896);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,11,1110,'Lichtenberg',                'Alt-Hohenschönhausen', 52.5625, 13.5042);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,11,1111,'Lichtenberg',                'Fennpfuhl', 52.5289, 13.4986);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,11,1112,'Lichtenberg',                'Rummelsburg', 52.5002, 13.4772);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,12,1201,'Reinickendorf',              'Reinickendorf', 52.5752, 13.3292);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,12,1202,'Reinickendorf',              'Tegel', 52.5868, 13.2909);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,12,1203,'Reinickendorf',              'Konradshöhe', 52.5834, 13.2142);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,12,1204,'Reinickendorf',              'Heiligensee', 52.6191, 13.2344);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,12,1205,'Reinickendorf',              'Frohnau', 52.6196, 13.2827);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,12,1206,'Reinickendorf',              'Hermsdorf', 52.6172, 13.2797);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,12,1207,'Reinickendorf',              'Waidmannslust', 52.6162, 13.3095);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,12,1208,'Reinickendorf',              'Lübars', 52.6077, 13.3379);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,12,1209,'Reinickendorf',              'Wittenau', 52.5986, 13.3267);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,12,1210,'Reinickendorf',              'Märkisches Viertel', 52.6199, 13.3651);
INSERT INTO Berliner_Ortsteile (Land_ID, Bezirk_ID, Ortsteil_ID, Bezirk, Ortsteil, Breite, Laenge) VALUES (11,12,1211,'Reinickendorf',              'Borsigwalde', 52.5769, 13.3047);
