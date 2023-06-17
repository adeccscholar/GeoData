﻿ 
#include "Processes.h"

#include "MyLocation.h"
#include "MyDatabaseExceptions.h"

using new_migration_details = std::tuple<std::string, bool, std::function<void(TProcess::concrete_query&, TProcess::concrete_query&, int)>>;

using Migrate_New_Data = std::pair<std::tuple<std::string, std::string>, std::vector<new_migration_details>>;



template <my_db_credentials ty>
std::tuple<TProcess::existing_entity_sets_type, std::vector<std::string>, Migrate_New_Data> CreateMigration(/* später Parameter möglich*/) {
   TProcess::existing_entity_sets_type Migrate_New_Model_Berlin_Clean = {
        { TProcess::EEntity_type::view,  "vw_neu_Berlin"s },
        { TProcess::EEntity_type::table, "neu_Bln_Adr_OT_Bez"s },
        { TProcess::EEntity_type::table, "neu_Bln_Adr_Str_Bez"s },
        { TProcess::EEntity_type::table, "neu_Bln_OT_Bzk_Bez"s },
        { TProcess::EEntity_type::table, "neu_Bln_Str_OT_Bez"s },
        { TProcess::EEntity_type::table, "neu_Berlin"s },
        { TProcess::EEntity_type::table, "neu_Berlin_Strasse_ohne_HNR"s },
        { TProcess::EEntity_type::table, "neu_Berlin_Qualitaet"s },
        { TProcess::EEntity_type::table, "neu_Berlin_Strassen"s },
        { TProcess::EEntity_type::table, "neu_Berlin_Ortsteile"s },
        { TProcess::EEntity_type::table, "neu_Berlin_Bezirke"s }
      };

   std::vector<std::string> New_Model;
   // Erstellen der Tabellen
   if constexpr (std::is_same<ty, TMyMSSQL>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Bezirke (\n"s +
         "   ID INTEGER Identity(1,1) NOT NULL,\n"s +
         "   Bezirk varchar(50)       NOT NULL,\n"s +
         "   Gueltig_ab DATE          NOT NULL,\n"s +
         "   Land_Kz INTEGER          NOT NULL,\n"s +
         "   Bezirk_Kz INTEGER        NOT NULL\n"s +
         "   )"s); 
      }
   else if constexpr (std::is_same<ty, TMyMySQL>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Bezirke (\n"s +
         "   ID INTEGER AUTO_INCREMENT PRIMARY KEY,\n"s +
         "   Bezirk varchar(50)       NOT NULL,\n"s +
         "   Gueltig_ab DATE          NOT NULL,\n"s +
         "   Land_Kz INTEGER          NOT NULL,\n"s +
         "   Bezirk_Kz INTEGER        NOT NULL\n"s +
         "   )"s);
      }
   else if constexpr (std::is_same<ty, TMySQLite>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Bezirke (\n"s +
         "   ID INTEGER PRIMARY KEY AUTOINCREMENT,\n"s +
         "   Bezirk varchar(50)       NOT NULL UNIQUE,\n"s +
         "   Gueltig_ab DATE          NOT NULL,\n"s +
         "   Land_Kz INTEGER          NOT NULL CHECK (Land_Kz > 0 AND Land_Kz < 100),\n"s +
         "   Bezirk_Kz INTEGER        NOT NULL CHECK (Bezirk_Kz > 0 AND Bezirk_Kz < 100),\n"s +
         "   UNIQUE (Land_Kz, Bezirk_Kz)\n"s
         "   )"s);
      }
   else if constexpr (std::is_same<ty, TMyInterbase>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Bezirke (\n"s +
         "   ID INTEGER GENERATED BY DEFAULT AS IDENTITY NOT NULL,\n"s +
         "   Bezirk varchar(50)       NOT NULL,\n"s +
         "   Gueltig_ab DATE          NOT NULL,\n"s +
         "   Land_Kz INTEGER          NOT NULL,\n"s +
         "   Bezirk_Kz INTEGER        NOT NULL\n"s +
         "   )"s);
      }
   else if constexpr (std::is_same<ty, TMyOracle>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Bezirke (\n"s +
         "   ID INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,\n"s +
         "   Bezirk varchar(50)       NOT NULL,\n"s +
         "   Gueltig_ab DATE          NOT NULL,\n"s +
         "   Land_Kz INTEGER          NOT NULL,\n"s +
         "   Bezirk_Kz INTEGER        NOT NULL\n"s +
         "   )"s);
      }


   if constexpr (std::is_same<ty, TMyMSSQL>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Ortsteile (\n"s +
         "   ID INTEGER Identity(1,1) NOT NULL,\n"s +
         "   Ortsteil VARCHAR(50)     NOT NULL,\n"s +
         "   Gueltig_ab DATE          NOT NULL,\n"s +
         "   Land_Kz INTEGER          NOT NULL,\n"s +
         "   Bezirk_Kz INTEGER        NOT NULL,\n"s +
         "   Ortsteil_Kz INTEGER      NOT NULL\n"s +
         "   )"s);
      }
   else if constexpr (std::is_same<ty, TMyMySQL>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Ortsteile (\n"s +
         "   ID INTEGER AUTO_INCREMENT PRIMARY KEY,\n"s +
         "   Ortsteil VARCHAR(50)     NOT NULL,\n"s +
         "   Gueltig_ab DATE          NOT NULL,\n"s +
         "   Land_Kz INTEGER          NOT NULL,\n"s +
         "   Bezirk_Kz INTEGER        NOT NULL,\n"s +
         "   Ortsteil_Kz INTEGER      NOT NULL\n"s +
         "   )"s);
      }
   else if constexpr (std::is_same<ty, TMySQLite>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Ortsteile (\n"s +
         "   ID INTEGER PRIMARY KEY AUTOINCREMENT,\n"s +
         "   Ortsteil VARCHAR(50)     NOT NULL UNIQUE,\n"s +
         "   Gueltig_ab DATE          NOT NULL,\n"s +
         "   Land_Kz INTEGER          NOT NULL CHECK (Land_Kz > 0 AND Land_Kz < 100),\n"s +
         "   Bezirk_Kz INTEGER        NOT NULL CHECK (Bezirk_Kz > 0 AND Bezirk_Kz < 100),\n"s +
         "   Ortsteil_Kz INTEGER      NOT NULL CHECK (Ortsteil_Kz > 0 AND Ortsteil_Kz < 100),\n"s +
         "   UNIQUE (Land_Kz, Bezirk_Kz, Ortsteil_Kz)\n"s
         "   )"s);
      }
   else if constexpr (std::is_same<ty, TMyInterbase>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Ortsteile (\n"s +
         "   ID INTEGER GENERATED BY DEFAULT AS IDENTITY NOT NULL,\n"s +
         "   Ortsteil VARCHAR(50)     NOT NULL,\n"s +
         "   Gueltig_ab DATE          NOT NULL,\n"s +
         "   Land_Kz INTEGER          NOT NULL,\n"s +
         "   Bezirk_Kz INTEGER        NOT NULL,\n"s +
         "   Ortsteil_Kz INTEGER      NOT NULL\n"s +
         "   )"s);
      }
   else if constexpr (std::is_same<ty, TMyOracle>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Ortsteile (\n"s +
         "   ID INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,\n"s +
         "   Ortsteil VARCHAR(50)     NOT NULL,\n"s +
         "   Gueltig_ab DATE          NOT NULL,\n"s +
         "   Land_Kz INTEGER          NOT NULL,\n"s +
         "   Bezirk_Kz INTEGER        NOT NULL,\n"s +
         "   Ortsteil_Kz INTEGER      NOT NULL\n"s +
         "   )"s);
      }

   // ----------------------------------------------------------------------------------------
   //   Erstellen der Tabelle "neu_Berlin_Strassen"
   if constexpr (std::is_same<ty, TMyMSSQL>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Strassen (\n"s +
         "   ID INTEGER Identity(1,1) NOT NULL,\n"s +
         "   Strasse VARCHAR(75)      NOT NULL,\n"s +
         "   Strasse_Kz INTEGER       NOT NULL,\n"s +
         "   Strasse_Datum DATE       NULL\n"s +
         "   )"s);
      }
   else if constexpr (std::is_same<ty, TMyMySQL>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Strassen (\n"s +
         "   ID INTEGER AUTO_INCREMENT PRIMARY KEY,\n"s +
         "   Strasse VARCHAR(75)      NOT NULL,\n"s +
         "   Strasse_Kz INTEGER       NOT NULL,\n"s +
         "   Strasse_Datum DATE       NULL\n"s +
         "   )"s);
      }
   else if constexpr (std::is_same<ty, TMySQLite>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Strassen (\n"s +
         "   ID INTEGER PRIMARY KEY AUTOINCREMENT,\n"s +
         "   Strasse VARCHAR(75)      NOT NULL,\n"s +
         "   Strasse_Kz INTEGER       NOT NULL UNIQUE CHECK (Strasse_Kz > 0 AND Strasse_Kz < 100000),\n"s +
         "   Strasse_Datum DATE       NULL\n"s +
         "   )"s);
      }
   else if constexpr (std::is_same<ty, TMyInterbase>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Strassen (\n"s +
         "   ID INTEGER GENERATED BY DEFAULT AS IDENTITY NOT NULL,\n"s +
         "   Strasse VARCHAR(75)      NOT NULL,\n"s +
         "   Strasse_Kz INTEGER       NOT NULL,\n"s +
         "   Strasse_Datum DATE\n"s +
         "   )"s);
   }
   else if constexpr (std::is_same<ty, TMyOracle>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Strassen (\n"s +
         "   ID INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,\n"s +
         "   Strasse VARCHAR(75)      NOT NULL,\n"s +
         "   Strasse_Kz INTEGER       NOT NULL,\n"s +
         "   Strasse_Datum DATE       NULL\n"s +
         "   )"s);
      }


   if constexpr (std::is_same<ty, TMyMSSQL>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Qualitaet (\n"s +
         "   ID INTEGER Identity(1,1) NOT NULL,\n"s +
         "   Description VARCHAR(100) NULL\n" +
         "   )"s);
      }
   else if constexpr (std::is_same<ty, TMyMySQL>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Qualitaet (\n"s +
         "   ID INTEGER AUTO_INCREMENT PRIMARY KEY,\n"s +
         "   Description VARCHAR(100) NULL\n" +
         "   )"s);
      }
   else if constexpr (std::is_same<ty, TMySQLite>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Qualitaet (\n"s +
         "   ID INTEGER PRIMARY KEY AUTOINCREMENT,\n"s +
         "   Description VARCHAR(100) NULL UNIQUE\n" +
         "   )"s);
      }
   else if constexpr (std::is_same<ty, TMyInterbase>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Qualitaet (\n"s +
         "   ID INTEGER GENERATED BY DEFAULT AS IDENTITY NOT NULL,\n"s +
         "   Description VARCHAR(100)\n" +
         "   )"s);
   }
   else if constexpr (std::is_same<ty, TMyOracle>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Qualitaet (\n"s +
         "   ID INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,\n"s +
         "   Description VARCHAR(100) NULL\n" +
         "   )"s);
      }

   if constexpr (!std::is_same<ty, TMySQLite>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Strasse_ohne_HNR(\n"s +
         "   Strasse_ID INTEGER      NOT NULL,\n"s +
         "   PLZ VARCHAR(5)          NOT NULL,\n"s +
         "   Latitude FLOAT          NOT NULL,\n"s +
         "   Longitude FLOAT         NOT NULL,\n"s +
         "   Qualitaet INTEGER       NOT NULL\n"s +
         "   )"s);
      }
   else {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Strasse_ohne_HNR(\n"s +
         "   Strasse_ID INTEGER      NOT NULL,\n"s +
         "   PLZ VARCHAR(5)          NOT NULL,\n"s +
         "   Latitude FLOAT          NOT NULL CHECK (Latitude >= -90 AND Latitude <= 90),\n"s +
         "   Longitude FLOAT         NOT NULL CHECK (Longitude >= -180 AND Longitude <= 180),\n"s +
         "   Qualitaet INTEGER       NOT NULL,\n"s +
         "   FOREIGN KEY(Strasse_ID) REFERENCES neu_Berlin_Strassen (ID),\n"s +
         "   FOREIGN KEY(Qualitaet) REFERENCES neu_Berlin_Qualitaet (ID)\n"s +
         "   )"s);
      }

   if constexpr (std::is_same<ty, TMyMSSQL>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin (\n"s +
         "   ID INTEGER Identity(1,1) NOT NULL,\n"s +
         "   Latitude FLOAT           NOT NULL ,\n"s +
         "   Longitude FLOAT          NOT NULL,\n"s +
         "   Adr_Datum DATE,\n"s +
         "   Qualitaet INTEGER        NOT NULL\n"s +
         "   )"s);
      }
   else if constexpr (std::is_same<ty, TMyMySQL>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin (\n"s +
         "   ID INTEGER AUTO_INCREMENT PRIMARY KEY,\n"s +
         "   Latitude FLOAT           NOT NULL,\n"s +
         "   Longitude FLOAT          NOT NULL,\n"s +
         "   Adr_Datum DATE       ,\n"s +
         "   Qualitaet INTEGER        NOT NULL\n"s +
         "   )"s);
      }
   else if constexpr (std::is_same<ty, TMySQLite>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin (\n"s +
         "   ID INTEGER PRIMARY KEY AUTOINCREMENT,\n"s +
         "   Latitude FLOAT           NOT NULL CHECK (Latitude >= -90 AND Latitude <= 90),\n"s +
         "   Longitude FLOAT          NOT NULL CHECK (Longitude >= -180 AND Longitude <= 180),\n"s +
         "   Adr_Datum DATE       ,\n"s +
         "   Qualitaet INTEGER        NOT NULL,\n"s +
         "   FOREIGN KEY(Qualitaet) REFERENCES neu_Berlin_Qualitaet (ID)\n"s +
         "   )"s);
      }
   else if constexpr (std::is_same<ty, TMyInterbase>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin (\n"s +
         "   ID INTEGER GENERATED BY DEFAULT AS IDENTITY NOT NULL,\n"s +
         "   Latitude FLOAT           NOT NULL ,\n"s +
         "   Longitude FLOAT          NOT NULL,\n"s +
         "   Adr_Datum DATE,\n"s +
         "   Qualitaet INTEGER        NOT NULL\n"s +
         "   )"s);
      }
   else if constexpr (std::is_same<ty, TMyOracle>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin (\n"s +
         "   ID INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,\n"s +
         "   Latitude  FLOAT NOT NULL,\n"s +
         "   Longitude FLOAT NOT NULL,\n"s +
         "   Adr_Datum DATE,\n"s +
         "   Qualitaet INTEGER NOT NULL\n"s +
         "   )"s);
      }

   New_Model.emplace_back(
      "CREATE TABLE neu_Bln_Adr_Str_Bez (\n"s +
      "   Adresse_ID INTEGER      NOT NULL,\n"s +
      "   Strasse_ID INTEGER      NOT NULL,\n"s +
      "   Nummer INTEGER          ,\n"s +
      "   ADZ VARCHAR(5)          ,\n"s +
      "   PLZ VARCHAR(5)          NOT NULL\n"s +
      "   )"s);

   New_Model.emplace_back(
      "CREATE TABLE neu_Bln_Adr_OT_Bez (\n"s +
      "   Adresse_ID INTEGER      NOT NULL,\n"s +
      "   Ortsteil_ID INTEGER     NOT NULL\n"s +
      "   )"s);

   New_Model.emplace_back(
      "CREATE TABLE neu_Bln_OT_Bzk_Bez (\n"s +
      "   Ortsteil_ID INTEGER     NOT NULL,\n"s +
      "   Bezirk_ID INTEGER       NOT NULL\n"s +
      "   )"s);

   New_Model.emplace_back(
      "CREATE TABLE neu_Bln_Str_OT_Bez (\n"s +
      "   Strasse_ID INTEGER      NOT NULL,\n"s +
      "   Ortsteil_ID INTEGER     NOT NULL\n"s +
      "   )"s);

      // Definition von Sichten auf der Datenbank
   if constexpr (std::is_same<ty, TMyOracle>::value || std::is_same<ty, TMyInterbase>::value) {
      New_Model.emplace_back(
         "CREATE VIEW vw_neu_Berlin AS\n"s +
         "   SELECT bz.Land_Kz AS LAND_ID, bz.Bezirk_Kz AS Bezirk_ID,\n"s +
         "          bz.Bezirk_Kz * 100 + ort.Ortsteil_Kz AS Ortsteil_ID, bs.Strasse_Kz AS Strasse_ID,\n"s +
         "          'Berlin' AS Land, 'Berlin' AS Stadt, bz.Bezirk,\n"s +
         "          ort.Ortsteil AS Ortsteil, bs.Strasse AS Strasse, bso.PLZ, NULL AS HNR, NULL AS ADZ,\n"s +
         "          bso.Latitude, bso.Longitude, bs.Strasse_Datum, NULL AS Adr_Datum,\n"s +
         "          qa.Description AS Adr_Qualitaet, 'Platz/Straße ohne HNR' AS Adr_Typ\n"s +
         "   FROM neu_Berlin_Strasse_ohne_HNR bso\n"s +
         "             JOIN neu_Berlin_Strassen bs ON(bs.ID = bso.Strasse_ID)\n"s +
         "             JOIN neu_Bln_Str_OT_Bez so ON(so.Strasse_ID = bs.ID)\n"s +
         "             JOIN neu_Berlin_Ortsteile ort ON(ort.ID = so.Ortsteil_ID)\n"s +
         "             JOIN neu_Bln_OT_Bzk_Bez obb ON(obb.Ortsteil_ID = ort.ID)\n"s +
         "             JOIN neu_Berlin_Bezirke bz ON(bz.ID = obb.Bezirk_ID)\n"s +
         "             JOIN neu_Berlin_Qualitaet qa ON(qa.ID = bso.Qualitaet)\n"s +
         "   UNION\n"s +
         "   SELECT bz.Land_Kz AS LAND_ID, bz.Bezirk_Kz AS Bezirk_ID,\n"s +
         "          bz.Bezirk_Kz * 100 + ort.Ortsteil_Kz AS Ortsteil_ID, bs.Strasse_Kz AS Strasse_ID,\n"s +
         "          'Berlin' AS Land, 'Berlin' AS Stadt, bz.Bezirk,\n"s +
         "          ort.Ortsteil AS Ortsteil, bs.Strasse AS Strasse, asb.PLZ,\n"s +
         "          asb.Nummer AS HNR, asb.ADZ, a.Latitude, a.Longitude, bs.Strasse_Datum,\n"s +
         "          a.Adr_Datum, aq.Description AS Adr_Qualitaet, 'Adresse' AS Adr_Typ\n"s +
         "   FROM neu_Berlin a JOIN neu_Bln_Adr_OT_Bez ot ON(ot.Adresse_ID = a.ID)\n"s +
         "                     JOIN neu_Berlin_Ortsteile ort ON(ort.ID = ot.Ortsteil_ID)\n"s +
         "                     JOIN neu_Bln_OT_Bzk_Bez obb ON(obb.Ortsteil_ID = ort.ID)\n"s +
         "                     JOIN neu_Berlin_Bezirke bz ON(bz.ID = obb.Bezirk_ID)\n"s +
         "                     JOIN neu_Bln_Adr_Str_Bez asb ON(asb.Adresse_ID = a.ID)\n"s +
         "                     JOIN neu_Berlin_Strassen bs ON(bs.ID = asb.Strasse_ID)\n"s +
         "                     JOIN neu_Berlin_Qualitaet aq ON (aq.ID = a.Qualitaet)"s);
      }
   else {
      New_Model.emplace_back(
         "CREATE VIEW vw_neu_Berlin AS\n"s +
         "   SELECT bz.Land_Kz AS LAND_ID, bz.Bezirk_Kz AS Bezirk_ID,\n"s +
         "          bz.Bezirk_Kz * 100 + ort.Ortsteil_Kz AS Ortsteil_ID, bs.Strasse_Kz AS Strasse_ID,\n"s +
         "          'Berlin' AS Land, 'Berlin' AS Stadt, bz.Bezirk,\n"s +
         "          ort.Ortsteil AS Ortsteil, bs.Strasse AS Strasse, bso.PLZ, NULL AS HNR, NULL AS ADZ,\n"s +
         "          bso.Latitude, bso.Longitude, bs.Strasse_Datum, NULL AS Adr_Datum,\n"s +
         "          qa.Description AS Adr_Qualitaet, 'Platz/Straße ohne HNR' AS Adr_Typ\n"s +
         "   FROM neu_Berlin_Strasse_ohne_HNR bso\n"s +
         "             JOIN neu_Berlin_Strassen bs ON(bs.ID = bso.Strasse_ID)\n"s +
         "             JOIN neu_Bln_Str_OT_Bez so ON(so.Strasse_ID = bs.ID)\n"s +
         "             JOIN neu_Berlin_Ortsteile ort ON(ort.ID = so.Ortsteil_ID)\n"s +
         "             JOIN neu_Bln_OT_Bzk_Bez obb ON(obb.Ortsteil_ID = ort.ID)\n"s +
         "             JOIN neu_Berlin_Bezirke bz ON(bz.ID = obb.Bezirk_ID)\n"s +
         "             JOIN neu_Berlin_Qualitaet qa ON(qa.ID = bso.Qualitaet)\n"s +
         "   UNION\n"s +
         "   SELECT bz.Land_Kz AS LAND_ID, bz.Bezirk_Kz AS Bezirk_ID,\n"s +
         "          bz.Bezirk_Kz * 100 + ort.Ortsteil_Kz AS Ortsteil_ID, bs.Strasse_Kz AS Strasse_ID,\n"s +
         "          'Berlin' AS Land, 'Berlin' AS Stadt, bz.Bezirk,\n"s +
         "          ort.Ortsteil AS Ortsteil, bs.Strasse AS Strasse, asb.PLZ,\n"s +
         "          asb.Nummer AS HNR, asb.ADZ, a.Latitude, a.Longitude, bs.Strasse_Datum,\n"s +
         "          a.Adr_Datum, aq.Description AS Adr_Qualitaet, 'Adresse' AS Adr_Typ\n"s +
         "   FROM neu_Berlin a JOIN neu_Bln_Adr_OT_Bez ot ON(ot.Adresse_ID = a.ID)\n"s +
         "                     JOIN neu_Berlin_Ortsteile ort ON(ort.ID = ot.Ortsteil_ID)\n"s +
         "                     JOIN neu_Bln_OT_Bzk_Bez obb ON(obb.Ortsteil_ID = ort.ID)\n"s +
         "                     JOIN neu_Berlin_Bezirke bz ON(bz.ID = obb.Bezirk_ID)\n"s +
         "                     JOIN neu_Bln_Adr_Str_Bez asb ON(asb.Adresse_ID = a.ID)\n"s +
         "                     JOIN neu_Berlin_Strassen bs ON(bs.ID = asb.Strasse_ID)\n"s +
         "                     JOIN neu_Berlin_Qualitaet aq ON (aq.ID = a.Qualitaet)"s);
      }

   // Schlüssel und Abhängigkeiten, Check- Bedingungen für alle Tabellen

   if constexpr (std::is_same<ty, TMyMSSQL>::value || std::is_same<ty, TMyInterbase>::value) {
      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Bezirke\n"s +
         "ADD CONSTRAINT pk_Bln_Bezirke PRIMARY KEY(ID)"s);
      }

   if constexpr (!std::is_same<ty, TMySQLite>::value) {
      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Bezirke\n"s +
         "ADD CONSTRAINT uk_Bln_Bezirke_Bezirk UNIQUE(Bezirk)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Bezirke\n"s +
         "ADD CONSTRAINT uk_Bln_Bezirke_Land_Bezirk_Kz UNIQUE (Land_Kz, Bezirk_Kz)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Bezirke\n"s +
         "ADD CONSTRAINT ck_Bln_Bezirke_Land_Kz CHECK (Land_Kz > 0 AND Land_Kz < 100)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Bezirke\n"s +
         "ADD CONSTRAINT ck_Bln_Bezirke_Bezirk_Kz CHECK (Bezirk_Kz > 0 AND Bezirk_Kz < 100)"s);
      }

   if constexpr (std::is_same<ty, TMyMSSQL>::value || std::is_same<ty, TMyInterbase>::value) {
      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Ortsteile\n"s +
         "ADD CONSTRAINT pk_Bln_Ortsteile PRIMARY KEY (ID)"s);
      }

   if constexpr (!std::is_same<ty, TMySQLite>::value) {
      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Ortsteile\n"s +
         "ADD CONSTRAINT uk_Bln_Ortsteile_Ortsteil UNIQUE (Ortsteil)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Ortsteile\n"s +
         "ADD CONSTRAINT uk_Bln_Ortsteile_Kz UNIQUE (Land_Kz, Bezirk_Kz, Ortsteil_Kz)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Ortsteile\n"s +
         "ADD CONSTRAINT ck_Bln_Ortsteile_Land_Kz CHECK (Land_Kz > 0 AND Land_Kz < 100)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Ortsteile\n"s +
         "ADD CONSTRAINT ck_Bln_Ortsteile_Bezirk_Kz CHECK (Bezirk_Kz > 0 AND Bezirk_Kz < 100)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Ortsteile\n"s +
         "ADD CONSTRAINT ck_Bln_Ortsteile_Ortsteil_Kz CHECK (Ortsteil_Kz > 0 AND Ortsteil_Kz < 100)"s);
      }

   if constexpr (std::is_same<ty, TMyMSSQL>::value || std::is_same<ty, TMyInterbase>::value) {
      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Strassen\n"s +
         "ADD CONSTRAINT pk_Bln_Strassen PRIMARY KEY (ID)"s);
      }

   if constexpr (!std::is_same<ty, TMySQLite>::value) {
      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Strassen\n"s +
         "ADD CONSTRAINT ck_Bln_Strassen_Kz CHECK (Strasse_Kz > 0 AND Strasse_Kz < 100000)"s);

      New_Model.emplace_back(
         "CREATE INDEX idx_neu_Bln_Str_Str ON neu_Berlin_Strassen (Strasse)"s);
      }

   if constexpr (std::is_same<ty, TMyMSSQL>::value || std::is_same<ty, TMyInterbase>::value) {
      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Qualitaet\n"s +
         "ADD CONSTRAINT pk_Bln_Qualitaet PRIMARY KEY (ID)"s);
      }

   if constexpr (!std::is_same<ty, TMySQLite>::value) {

      if constexpr (std::is_same<ty, TMyOracle>::value || std::is_same<ty, TMyInterbase>::value) {
         New_Model.emplace_back(
            "ALTER TABLE neu_Berlin_Qualitaet\n"s +
            "ADD CONSTRAINT uk_Bln_Qualitaet UNIQUE (Description)"s);
         }
      else {
         New_Model.emplace_back(
            "ALTER TABLE neu_Berlin_Qualitaet\n"s +
            "ADD CONSTRAINT uk_Bln_Qualitaet UNIQUE (Description)"s);
         }

      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Strasse_ohne_HNR\n"s +
         "ADD CONSTRAINT pk_Bln_Str_ohne_HNR PRIMARY KEY(Strasse_ID)"s);
      }

   if constexpr (std::is_same<ty, TMyMSSQL>::value || std::is_same<ty, TMyInterbase>::value) {
      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin\n"s +
         "ADD CONSTRAINT pk_neu_Berlin PRIMARY KEY (ID)"s);
      }

   if constexpr (!std::is_same<ty, TMySQLite>::value) {
      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin\n"s +
         "ADD CONSTRAINT ck_neu_Berlin_Lat CHECK (Latitude >= -90 AND Latitude <= 90)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin\n"s +
         "ADD CONSTRAINT ck_neu_Berlin_Long CHECK (Longitude >= -180 AND Longitude <= 180)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Bln_Adr_Str_Bez\n"s +
         "ADD CONSTRAINT pk_neu_Bln_Adr_Str_Bez PRIMARY KEY (Adresse_ID)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Bln_Adr_Str_Bez\n"s +
         "ADD CONSTRAINT uk_neu_Bln_Adr_Str_Bez_Str UNIQUE(Strasse_ID, Nummer, ADZ)"s);
      }


   New_Model.emplace_back(
         "CREATE INDEX idx_neu_Bln_Adr_Str_Bez ON neu_Bln_Adr_Str_Bez (PLZ)"s);

   if constexpr (!std::is_same<ty, TMySQLite>::value) {
      New_Model.emplace_back(
         "ALTER TABLE neu_Bln_Adr_OT_Bez\n"s +
         "ADD CONSTRAINT pk_neu_Bln_Adr_OT_Bez PRIMARY KEY (Adresse_ID)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Bln_OT_Bzk_Bez\n"s +
         "ADD CONSTRAINT pk_neu_Bln_OT_Bez    PRIMARY KEY (Ortsteil_ID)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Bln_Str_OT_Bez\n"s +
         "ADD CONSTRAINT pk_neu_Bln_Str_Bez PRIMARY KEY (Strasse_ID, Ortsteil_ID)"s);

      }

   if constexpr (!std::is_same<ty, TMySQLite>::value) { // && !std::is_same<ty, TMyInterbase>::value) {
      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Strasse_ohne_HNR\n"s +
         "ADD CONSTRAINT fk_Bln_Str_ohne_HNR_Str FOREIGN KEY(Strasse_ID) REFERENCES neu_Berlin_Strassen(ID)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Strasse_ohne_HNR\n"s +
         "ADD CONSTRAINT fk_Bln_Str_ohne_HNR_Qual FOREIGN KEY(Qualitaet) REFERENCES neu_Berlin_Qualitaet(ID)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin\n"s +
         "ADD CONSTRAINT fk_neu_Berlin_Qualitaet FOREIGN KEY(Qualitaet) REFERENCES neu_Berlin_Qualitaet (ID)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Bln_Adr_Str_Bez\n"s +
         "ADD CONSTRAINT fk_neu_Bln_Adr_Str_Bez_Bln FOREIGN KEY(Adresse_ID) REFERENCES neu_Berlin (ID)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Bln_Adr_Str_Bez\n"s +
         "ADD CONSTRAINT fk_neu_Bln_Adr_Str_Bez_Str FOREIGN KEY(Strasse_ID) REFERENCES neu_Berlin_Strassen (ID)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Bln_Adr_OT_Bez\n"s +
         "ADD CONSTRAINT fk_neu_Bln_Adr_OT_Bez_Ort FOREIGN KEY(Ortsteil_ID) REFERENCES neu_Berlin_Ortsteile (ID)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Bln_OT_Bzk_Bez\n"s +
         "ADD CONSTRAINT fk_neu_Bln_OT_Bzk_OT FOREIGN KEY (Ortsteil_ID) REFERENCES neu_Berlin_Ortsteile (ID)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Bln_OT_Bzk_Bez\n"s +
         "ADD CONSTRAINT fk_neu_Bln_OT_Bez FOREIGN KEY (Bezirk_ID) REFERENCES neu_Berlin_Bezirke (ID)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Bln_Str_OT_Bez\n"s +
         "ADD CONSTRAINT fk_neu_Bln_Str_Str FOREIGN KEY (Strasse_ID) REFERENCES neu_Berlin_Strassen (ID)"s);

      New_Model.emplace_back(
         "ALTER TABLE neu_Bln_Str_OT_Bez\n"s +
         "ADD CONSTRAINT fk_neu_Bln_Str_OT FOREIGN KEY (Ortsteil_ID) REFERENCES neu_Berlin_Ortsteile (ID)"s);
   }

   // ----------------------------------------------------------------------------------------
   // Füllen der Tabellen mit Daten, die direkt aufgebaut werden können

   New_Model.emplace_back(
      "INSERT INTO neu_Berlin_Bezirke (Bezirk, Gueltig_ab, Land_Kz, Bezirk_Kz)\n"s +
      "  SELECT DISTINCT Bezirk, '01.01.2001', Land_ID, Bezirk_ID\n"s +
      "  FROM Berlin"s);


   New_Model.emplace_back(
      "INSERT INTO neu_Berlin_Ortsteile (Ortsteil, Gueltig_ab, Land_Kz, Bezirk_Kz, Ortsteil_Kz)\n"s +
      "  SELECT DISTINCT Ortsteil, '01.01.2001', Land_ID, Bezirk_ID, Ortsteil_ID - (100 * Bezirk_ID)\n"s +
      "  FROM Berlin"s);

   New_Model.emplace_back(
      "INSERT INTO neu_Berlin_Strassen (Strasse, Strasse_Kz, Strasse_Datum)\n"s +
      "  SELECT Strasse, Strasse_ID, MAX(Strasse_Datum)\n"s +
      "  FROM Berlin\n"s +
      "  GROUP BY Strasse, Strasse_ID"s);

   New_Model.emplace_back(
      "INSERT INTO neu_Berlin_Qualitaet (Description)\n"s +
      "  SELECT DISTINCT Qualitaet\n"s +
      "  FROM Berlin"s);

   
   New_Model.emplace_back(
      "INSERT INTO neu_Berlin_Strasse_ohne_HNR (Strasse_ID, PLZ, Latitude, Longitude, Qualitaet)\n"s +
      "  SELECT bs.ID AS Strasse_ID, a.PLZ, a.Latitude, a.Longitude, bq.ID\n"s +
      "  FROM Berlin a JOIN neu_Berlin_Strassen bs ON(bs.Strasse_Kz = a.Strasse_ID)\n"s +
      "                JOIN neu_Berlin_Qualitaet bq ON(bq.Description = a.Qualitaet)\n"s +
      "  WHERE a.Adr_Typ = 'Platz/Straße ohne HNR'\n"s);

   New_Model.emplace_back(
      "INSERT INTO neu_Bln_OT_Bzk_Bez (Ortsteil_ID, Bezirk_ID)\n"s +
      "  SELECT DISTINCT a.ID AS Ortsteil_ID, b.ID AS Bezirk_ID\n"s +
      "  FROM neu_Berlin_Ortsteile a\n"s +
      "      JOIN neu_Berlin_Bezirke b ON (b.Land_Kz = a.Land_Kz AND\n"s +
      "                                    b.Bezirk_Kz = a.Bezirk_Kz)"s);

   New_Model.emplace_back(
      "INSERT INTO neu_Bln_Str_OT_Bez (Strasse_ID, Ortsteil_ID)\n" +
      "  SELECT DISTINCT s.ID AS Strasse_ID, o.ID AS Ortsteil_ID\n"s +
      "  FROM Berlin a JOIN neu_Berlin_Strassen s ON (s.Strasse_Kz = a.Strasse_ID)\n"s +
      "         JOIN neu_Berlin_Ortsteile o ON (o.Bezirk_Kz = a.Bezirk_ID AND\n"s +
      "                                         o.Ortsteil_Kz = a.Ortsteil_ID - 100 * a.Bezirk_ID)"s);


   Migrate_New_Data Split_New_Model_Berlin = {
      {  "new model for Berlin data"s,
         "SELECT a.PLZ, a.HNR AS Nummer, a.ADZ, a.Latitude, a.Longitude,a.Adr_Datum,\n"s +
         "       s.ID AS Strasse_ID, o.ID AS Ortsteil_ID, aq.ID AS Adr_Qualitaet\n"s +
         "FROM Berlin a JOIN neu_Berlin_Strassen s ON (s.Strasse_Kz = a.Strasse_ID)\n"s +
         "              JOIN neu_Berlin_Ortsteile o ON (o.Bezirk_Kz = a.Bezirk_ID AND \n"s +
         "                                              o.Ortsteil_Kz = Ortsteil_ID - 100 * Bezirk_ID)\n"s +
         "              JOIN neu_Berlin_Qualitaet aq ON (aq.Description = a.Qualitaet)\n"s +   
         "WHERE a.Adr_Typ <> 'Platz/Straße ohne HNR'"},
      { { "INSERT INTO neu_Berlin (Latitude, Longitude, Adr_Datum, Qualitaet)\n"s +
          "VALUES (:Latitude, :Longitude, :Adr_Datum, :Qualitaet)"s, true,
          [](TProcess::concrete_query& qry, TProcess::concrete_query& ins, int id) {
               ins.Set("Latitude",  qry.Get<double>("Latitude"));
               ins.Set("Longitude", qry.Get<double>("Longitude"));
               ins.Set("Adr_Datum", qry.Get<std::chrono::year_month_day>("Adr_Datum"));
               ins.Set("Qualitaet", qry.Get<int>("Adr_Qualitaet"));
               } } ,
        { "INSERT INTO neu_Bln_Adr_Str_Bez(Adresse_ID,Strasse_ID,Nummer,ADZ,PLZ)\n"s +
          "VALUES (:Adresse_ID,:Strasse_ID,:Nummer,:ADZ,:PLZ)"s, false,
          [](TProcess::concrete_query& qry, TProcess::concrete_query& ins, int id) {
               ins.Set("Adresse_ID", id);
               ins.Set("Strasse_ID", qry.Get<int>("Strasse_ID"));
               ins.Set("Nummer",     qry.Get<int>("Nummer"));
               ins.Set("ADZ",        qry.Get<std::string>("ADZ"));
               ins.Set("PLZ",        qry.Get<std::string>("PLZ"));
               } },
        { "INSERT INTO neu_Bln_Adr_OT_Bez (Adresse_ID,Ortsteil_ID)\n"s +
          "VALUES (:Adresse_ID,:Ortsteil_ID)"s, false,
          [](TProcess::concrete_query& qry, TProcess::concrete_query& ins, int id) {
               ins.Set("Adresse_ID",  id);
               ins.Set("Ortsteil_ID", qry.Get<int>("Ortsteil_ID"));
               } }
      } };


   return { Migrate_New_Model_Berlin_Clean, New_Model , Split_New_Model_Berlin };
   }



void TProcess::print_migrate_Berlin(std::ostream& out) {
   auto [clean, prepare, run] = CreateMigration<concrete_db_server>();
   try {
      TMyWait wait;
      for (auto const& stmt : prepare) {
         out << stmt << ";" << std::endl << std::endl;
         }
      }
   catch (TMy_Db_Exception& ex) {
      HandleException("print migrating statements for new model for Berlin", ex);
      }
   catch (std::exception& ex) {
      HandleException("print migrating statements for new model for Berlin", ex);
      }
   }

void TProcess::migrate_neues_Model(void) {
   static constinit int iStepstoMessage = 25'000;
   std::string strMessage { "new Model"s };

   try {

      TMyWait wait;
      auto [clean, prepare, run] = CreateMigration<concrete_db_server>();
      strMessage = get<0>(run.first);
      auto start = std::chrono::system_clock::now();
      std::cerr << std::format("{}: inserting {} started ...\n", get_current_time_and_date(), get<0>(run.first));
      std::clog << std::format("inserting {} started\n", get<0>(run.first));
      TMyForm::ProcessEvents();

      auto allViews = db.GetViewNames("");
      auto allTables = db.GetTableNames("");
      auto query = db.CreateQuery();
      bool boExecute = false;
      for(auto& [etype, name] : clean) {
         if constexpr (std::is_same<concrete_db_server, TMyOracle>::value || std::is_same<concrete_db_server, TMyInterbase>::value) {
            std::transform(name.begin(), name.end(), name.begin(), [](auto c) { return std::toupper(c);  });
            }
         else if constexpr (std::is_same<concrete_db_server, TMyMySQL>::value) {
            std::transform(name.begin(), name.end(), name.begin(), [](auto c) { return std::tolower(c);  });
            }

         switch(etype) {
            case EEntity_type::view:
               if (boExecute = allViews.find(name) != allViews.end(); boExecute) query.SetSQL(std::format("DROP VIEW {}", name));
               break;
            case EEntity_type::table:
               if (boExecute = allTables.find(name) != allTables.end(); boExecute) query.SetSQL(std::format("DROP TABLE {}", name));
               break; 
            default:
               throw TMy_RuntimeError("unexpected entity tpye in cleanup");
            }
         if(boExecute) query.Execute();
         }

      for(auto const& stmt : prepare) {
         query.SetSQL(stmt);
         query.Execute();
         }


      db.StartTransaction();
      query.SetSQL(get<1>(run.first));
      std::vector<TProcess::concrete_query> ins_qry;
      for(auto const& val : run.second) {
         
         if constexpr (std::is_same<concrete_db_server, TMyOracle>::value) {
            if (std::get<1>(val)) {
               auto query = db.CreateQuery(std::get<0>(val) + " RETURNING ID INTO :last_Id");
               ins_qry.emplace_back(query);
               }
            else ins_qry.emplace_back(db.CreateQuery(std::get<0>(val)));
            }
         else if constexpr (std::is_same<concrete_db_server, TMyInterbase>::value) {
            if (std::get<1>(val)) {
               auto query = db.CreateQuery(std::get<0>(val) + " RETURNING ID");
               ins_qry.emplace_back(query);
               }
            else ins_qry.emplace_back(db.CreateQuery(std::get<0>(val)));
            }
         else {
         
            ins_qry.emplace_back(db.CreateQuery(std::get<0>(val)));
            }
         }

      size_t linecnt = 0;

      for(query.Execute(), query.First(); !query.IsEof(); query.Next()) {
         int last_ID = 0;

         for (size_t i = 0; auto const& val : run.second) {
            std::get<2>(val)(query, ins_qry[i], last_ID);
  
            if constexpr (std::is_same<concrete_db_server, TMyOracle>::value) {
               if (std::get<1>(val)) {
                  auto id_qry = static_cast<QSqlQuery&>(ins_qry[i]);
                  auto text = ins_qry[i].GetSQL();
                  QVariant ret(QVariant::Int);
                  id_qry.bindValue(":last_Id", ret);
                  if (id_qry.exec()) {
                     last_ID = id_qry.boundValue(":last_Id").toInt(); 
                     }
                  else throw TMy_RuntimeError(text + "\n"s + id_qry.lastError().text().toStdString());
                  }
               else {
                  ins_qry[i].Execute();
                  }
               }
            else if constexpr (std::is_same<concrete_db_server, TMyInterbase>::value) {
               if (std::get<1>(val)) {
                  ins_qry[i].Execute(); ins_qry[i].Next(); // ID Lesen
                  last_ID = *ins_qry[i].Get<int>("ID");
                  }
               else {
                  ins_qry[i].Execute();
                  }
               }
            else {
               ins_qry[i].Execute();
               if(std::get<1>(val)) last_ID = static_cast<QSqlQuery&>(ins_qry[i]).lastInsertId().toInt();
               }

            ++i;
            }
         if (++linecnt % iStepstoMessage == 0) {
            std::clog << get<0>(run.first) << " -> " << linecnt << " rows inserted" << std::endl;
            TMyForm::ProcessEvents();
            }

         }

      db.Commit();
      std::string strEndMessage = std::format("{}, {} rows inserted in {}", get<0>(run.first), linecnt, FormatExecutionTime(start));
      std::cerr << std::format("{}: {}\n", get_current_time_and_date(), strEndMessage);
      std::clog << strEndMessage << std::endl;
      }
   catch (TMy_Db_Exception& ex) {
      HandleException(std::format("migrate {}", strMessage), ex);
      }
   catch (std::exception& ex) {
      db.Rollback();
      HandleException(std::format("migrate {}", strMessage), ex);
      }

   }



