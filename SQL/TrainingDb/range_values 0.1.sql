/*
Projekt: Training
Inhalt:  F�llen der Wertebereiche der Datenbank
Autor:   Volker Hillmann (adecc Systemhaus GmbH)
Datum:   24.04.2016
Copyright � 2001 - 2016. Alle Rechte vorbehalten.

*/

INSERT INTO AddressTypes (ID, Denotation, Abbreviation, Description, UrgentValue ) VALUES
   (1, 'Hauptadresse', 'HA', 'Hauptadresse f�r die Anwendung', 1),
   (2, 'Rechnungsadresse', 'RA', 'Rechnungsadresse f�r die Anwendung', 0),
   (3, 'Lieferadresse', 'LA', 'Lieferadresse f�r die Trainingsanwendung', 0),
   (4, 'Urlaubsadresse', 'UA', 'eine Adresse, in der die Person im Urlaub erreichbar ist', 0);

INSERT INTO PhoneTypes (ID, Denotation, Abbreviation, Description, UrgentValue) VALUES
   (1, 'Telefon', 'Tel', 'Telefonnummer zu einer Person', 1),
   (2, 'Fax', 'Fax', 'Faxnummer zu einer Person', 1),
   (3, 'Mobil', 'Mbl', 'Mobiltelefonnummer zu einer Person', 1);
GO

INSERT INTO BankingTypes (ID, Denotation, Abbreviation, Description, UrgentValue) VALUES
   (1, 'Hauptkonto', 'HK', 'Hauptkonto f�r die Personen in der Anwendung', 1);
GO

INSERT INTO InternetTypes (ID, Denotation, Abbreviation, Description, Prefix, UrgentValue) VALUES
   (1, 'Internet', 'HTTP', 'Die Homepage einer Person', 'http://', 1),
   (2, 'Email', 'Mail', 'Email- Adresse einer Person', 'mailto:', 1),
   (3, 'Skype', 'Skype', 'Skype- Name einer Person', 'skype:', 1),
   (4, 'Telefon', 'VoIP', 'VoIP- Nummer einer Person', 'phone:', 1);
GO

INSERT INTO FamilyTypes (ID, Denotation, Abbreviation, Description, UrgentValue) VALUES
   (1, 'Mann', 'M', 'Person mit m�nnlichem Geschlecht', 1),
   (2, 'Frau', 'F', 'Person mit weiblichen Geschlecht', 1),
   (3, 'Firma', 'Fa', 'Person ist Firma', 1),
   (4, 'Familie', 'Fam', 'Famile', 0),
   (5, 'Verein', 'EV', 'eingetragener Verein', 0);
GO

INSERT INTO FormOfAddress (ID, Denotation, Abbreviation, Description, TypeSpec, Salutation, Valediction, UrgentValue) VALUES
   (1, 'Herr', 'Hr', 'Anredesteuerung f�r Herr', 1, 'Sehr geehrter Herr', 'Mit freundlichen Gr��en', 1),
   (2, 'Frau', 'Fr', 'Anredesteuerung f�r Frauen', 2, 'Sehr geehrte Frau', 'Mit freundlichen Gr��en', 1),
   (3, 'Firma', 'Fa', 'Anredesteuerung f�r Firmen', 3, 'Sehr geehrte Damen und Herren', 'Mit freundlichen Gr��en', 0);
GO

INSERT INTO Countries (ID, Denotation, Abbreviation, Description, CountryDialing, ISO_Code, UrgentValue) VALUES
   (1, 'Deutschland', 'BRD', 'Bundesrebublik Deutschland', '+49', 'DE', 1),
   (2, '�sterreich', 'AUT', '�stereich', '+43', 'AT', 1),
   (3, 'Schweiz', 'CHE', 'Schweizerische Eidgenossenschaft', '+41', 'CH', 1),
   (4, 'Frankreich', 'France', 'Franz�sische Republik', '+33', 'FR', 0),
   (5, 'Luxemburg', 'Lux', 'Gro�herzogtum Luxemburg', '+352', 'LU', 0),
   (6, 'Liechtenstein', 'LIE', 'F�rstentum Liechtenstein', '+432', 'LI', 0),
   (7, 'Belgien', 'BEL', 'K�nigreich Belgien ', '+32', 'BE', 0),
   (8, 'Niederlande', 'NDL', 'Niederlande', '+31', 'NL', 0),
   (9, 'Gro�britannien', 'GBR', 'Vereinigtes K�nigreich Gro�britannien und Nordirland', '+44', 'GB', 0);
GO

INSERT INTO JobPositions (ID, Denotation, Abbreviation, Description, UrgentValue) VALUES
   (1, 'Vorstand', 'V', 'Vorstand des Unternehmens', 0),
   (2, 'Bereichsleiter', 'BL', 'Bereichsleiter im Unternehmen', 0),
   (3, 'Abteilungsleiter', 'AL', 'Abteilungsleiter des Unternehmens', 0),
   (4, 'Gruppenleiter', 'GL', 'Gruppenleiter im Unternehmen', 0),
   (5, 'Angestellter', 'AN', 'Angestellter im Unternehmen', 0),
   (6, 'Aushilfe', 'AH', 'Aushilfe im Unternehmen (auch 400 �- Basis)', 0),
   (7, 'Lehrling', 'LE', 'Lehrling im Unternehmen', 0);
GO
 
