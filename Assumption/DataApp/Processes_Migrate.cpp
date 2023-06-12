 
#include "Processes.h"

#include "MyLocation.h"
#include "MyDatabaseExceptions.h"

enum class EEntity_type : int { unknow, table, view };

using existing_entity_sets_type = std::vector<std::pair<EEntity_type, std::string>>;

using Migrate_New_Data = std::pair<std::tuple<std::string, std::string>,
   std::vector<std::tuple<std::string, bool,
   std::function<void(TProcess::concrete_query&,
      TProcess::concrete_query&,
      int)>>>>;



template <my_db_credentials ty>
std::tuple<existing_entity_sets_type, std::vector<std::string>, Migrate_New_Data> CreateMigration(/* später Parameter möglich*/) {
   existing_entity_sets_type Migrate_New_Model_Berlin_Clean = {
        { EEntity_type::view,  "vw_neu_Berlin"s },
        { EEntity_type::table, "neu_Bln_Adr_OT_Bez"s },
        { EEntity_type::table, "neu_Bln_Adr_Str_Bez"s },
        { EEntity_type::table, "neu_Bln_OT_Bzk_Bez"s },
        { EEntity_type::table, "neu_Bln_Str_OT_Bez"s },
        { EEntity_type::table, "neu_Berlin"s },
        { EEntity_type::table, "neu_Berlin_Strasse_ohne_HNR"s },
        { EEntity_type::table, "neu_Berlin_Qualitaet"s },
        { EEntity_type::table, "neu_Berlin_Strassen"s },
        { EEntity_type::table, "neu_Berlin_Ortsteile"s },
        { EEntity_type::table, "neu_Berlin_Bezirke"s }
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
   else {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Bezirke (\n"s +
         "   ID INTEGER AUTO_INCREMENT PRIMARY KEY,\n"s +
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
   else {
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

   if constexpr (std::is_same<ty, TMyMSSQL>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Strassen (\n"s +
         "   ID INTEGER Identity(1,1) NOT NULL,\n"s +
         "   Strasse VARCHAR(75)      NOT NULL,\n"s +
         "   Strasse_Kz INTEGER       NOT NULL,\n"s +
         "   Strasse_Datum DATE       NULL\n"s +
         "   )"s);
      }
   else {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Strassen (\n"s +
         "   ID INTEGER AUTO_INCREMENT PRIMARY KEY,\n"s +
         "   Strasse VARCHAR(75)      NOT NULL,\n"s +
         "   Strasse_Kz INTEGER       NOT NULL,\n"s +
         "   Strasse_Datum DATE       NULL\n"s +
         "   )"s);
      }

   New_Model.emplace_back(
      "CREATE TABLE neu_Berlin_Strasse_ohne_HNR(\n"s +
      "   Strasse_ID INTEGER      NOT NULL,\n"s +
      "   PLZ VARCHAR(5)          NOT NULL,\n"s +
      "   Latitude FLOAT          NOT NULL,\n"s +
      "   Longitude FLOAT         NOT NULL,\n"s +
      "   Qualitaet INTEGER       NOT NULL\n"s +
      "   )"s);

   if constexpr (std::is_same<ty, TMyMSSQL>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Qualitaet (\n"s +
         "   ID INTEGER Identity(1,1) NOT NULL,\n"s +
         "   Value VARCHAR(100) NULL\n" +
         "   )"s);
      }
   else {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin_Qualitaet (\n"s +
         "   ID INTEGER AUTO_INCREMENT PRIMARY KEY,\n"s +
         "   Value VARCHAR(100) NULL\n" +
         "   )"s);
      }

   if constexpr (std::is_same<ty, TMyMSSQL>::value) {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin (\n"s +
         "   ID INTEGER Identity(1,1) NOT NULL,\n"s +
         "   Latitude FLOAT           NOT NULL,\n"s +
         "   Longitude FLOAT          NOT NULL,\n"s +
         "   Adresse_Datum DATE       NULL,\n"s +
         "   Qualitaet INTEGER        NOT NULL"s +
         "   );"s);
      }
   else {
      New_Model.emplace_back(
         "CREATE TABLE neu_Berlin (\n"s +
         "   ID INTEGER AUTO_INCREMENT PRIMARY KEY,\n"s +
         "   Latitude FLOAT           NOT NULL,\n"s +
         "   Longitude FLOAT          NOT NULL,\n"s +
         "   Adresse_Datum DATE       NULL,\n"s +
         "   Qualitaet INTEGER        NOT NULL"s +
         "   );"s);
      }

   New_Model.emplace_back(
      "CREATE TABLE neu_Bln_Adr_Str_Bez (\n"s +
      "   Adresse_ID INTEGER      NOT NULL,\n"s +
      "   Strasse_ID INTEGER      NOT NULL,\n"s +
      "   Nummer INTEGER          NULL,\n"s +
      "   ADZ VARCHAR(5)          NULL,\n"s +
      "   PLZ VARCHAR(5)          NOT NULL\n"s +
      "   );"s);

   New_Model.emplace_back(
      "CREATE TABLE neu_Bln_Adr_OT_Bez (\n"s +
      "   Adresse_ID INTEGER      NOT NULL,\n"s +
      "   Ortsteil_ID INTEGER     NOT NULL\n"s +
      "   );"s);

   New_Model.emplace_back(
      "CREATE TABLE neu_Bln_OT_Bzk_Bez (\n"s +
      "   Ortsteil_ID INTEGER     NOT NULL,\n"s +
      "   Bezirk_ID INTEGER       NOT NULL\n"s +
      "   );"s);

   New_Model.emplace_back(
      "CREATE TABLE neu_Bln_Str_OT_Bez (\n"s +
      "   Strasse_ID INTEGER      NOT NULL,\n"s +
      "   Ortsteil_ID INTEGER     NOT NULL\n"s +
      "   );"s);

      // Definition von Sichten auf der Datenbank
   New_Model.emplace_back(
      "CREATE VIEW vw_neu_Berlin AS\n"s +
      "   SELECT bz.Land_Kz AS LAND_ID, bz.Bezirk_Kz AS Bezirk_ID,\n"s +
      "          bz.Bezirk_Kz * 100 + ort.Ortsteil_Kz AS Ortsteil_ID, bs.Strasse_Kz AS Strasse_ID,\n"s +
      "          'Berlin' AS Land, 'Berlin' AS Stadt, bz.Bezirk,\n"s +
      "          ort.Ortsteil AS Ortsteil, bs.Strasse AS Strasse, bso.PLZ, NULL AS HNR, NULL AS ADZ,\n"s +
      "          bso.Latitude, bso.Longitude, bs.Strasse_Datum, NULL AS Adresse_Datum,\n"s +
      "          qa.Value AS Adr_Qualitaet, 'Platz/Straße ohne HNR' AS Adr_Typ\n"s +
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
      "          a.Adresse_Datum, aq.Value AS Adr_Qualitaet, 'Adresse' AS Adr_Typ\n"s +
      "   FROM neu_Berlin a JOIN neu_Bln_Adr_OT_Bez ot ON(ot.Adresse_ID = a.ID)\n"s +
      "                     JOIN neu_Berlin_Ortsteile ort ON(ort.ID = ot.Ortsteil_ID)\n"s +
      "                     JOIN neu_Bln_OT_Bzk_Bez obb ON(obb.Ortsteil_ID = ort.ID)\n"s +
      "                     JOIN neu_Berlin_Bezirke bz ON(bz.ID = obb.Bezirk_ID)\n"s +
      "                     JOIN neu_Bln_Adr_Str_Bez asb ON(asb.Adresse_ID = a.ID)\n"s +
      "                     JOIN neu_Berlin_Strassen bs ON(bs.ID = asb.Strasse_ID)\n"s +
      "                     JOIN neu_Berlin_Qualitaet aq ON (aq.ID = a.Qualitaet)"s);

      // Schlüssel und Abhängigkeiten, Check- Bedingungen für alle Tabellen

   if constexpr (std::is_same<ty, TMyMSSQL>::value) {
      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Bezirke\n"s +
         "ADD CONSTRAINT pk_Bln_Bezirke PRIMARY KEY(ID)"s);
      }

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

   if constexpr (std::is_same<ty, TMyMSSQL>::value) {
      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Ortsteile\n"s +
         "ADD CONSTRAINT pk_Bln_Ortsteile PRIMARY KEY (ID)"s);
      }

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

   if constexpr (std::is_same<ty, TMyMSSQL>::value) {
      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Strassen\n"s +
         "ADD CONSTRAINT pk_Bln_Strassen PRIMARY KEY (ID)"s);
      }

   New_Model.emplace_back(
      "ALTER TABLE neu_Berlin_Strassen\n"s +
      "ADD CONSTRAINT ck_Bln_Strassen_Kz CHECK (Strasse_Kz > 0 AND Strasse_Kz < 100000)"s);

   New_Model.emplace_back(
      "CREATE INDEX idx_neu_Bln_Str_Str ON neu_Berlin_Strassen (Strasse)"s);

   if constexpr (std::is_same<ty, TMyMSSQL>::value) {
      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin_Qualitaet\n"s +
         "ADD CONSTRAINT pk_Bln_Qualitaet PRIMARY KEY (ID)"s);
      }

   New_Model.emplace_back(
      "ALTER TABLE neu_Berlin_Qualitaet\n"s +
      "ADD CONSTRAINT uk_Bln_Qualitaet UNIQUE (Value)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Berlin_Strasse_ohne_HNR\n"s +
      "ADD CONSTRAINT pk_Bln_Str_ohne_HNR PRIMARY KEY(Strasse_ID)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Berlin_Strasse_ohne_HNR\n"s +
      "ADD CONSTRAINT fk_Bln_Str_ohne_HNR_Str FOREIGN KEY(Strasse_ID) REFERENCES neu_Berlin_Strassen(ID)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Berlin_Strasse_ohne_HNR\n"s +
      "ADD CONSTRAINT fk_Bln_Str_ohne_HNR_Qual FOREIGN KEY(Qualitaet) REFERENCES neu_Berlin_Qualitaet(ID)"s);

   if constexpr (std::is_same<ty, TMyMSSQL>::value) {
      New_Model.emplace_back(
         "ALTER TABLE neu_Berlin\n"s +
         "ADD CONSTRAINT pk_neu_Berlin PRIMARY KEY (ID)"s);
      }

   New_Model.emplace_back(
      "ALTER TABLE neu_Berlin\n"s +
      "ADD CONSTRAINT ck_neu_Berlin_Lat CHECK (Latitude >= -90 AND Latitude <= 90)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Berlin\n"s +
      "ADD CONSTRAINT ck_neu_Berlin_Long CHECK (Longitude >= -180 AND Longitude <= 180)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Berlin\n"s +
      "ADD CONSTRAINT fk_neu_Berlin_Qualitaet FOREIGN KEY(Qualitaet) REFERENCES neu_Berlin_Qualitaet (ID)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Bln_Adr_Str_Bez\n"s +
      "ADD CONSTRAINT pk_neu_Bln_Adr_Str_Bez PRIMARY KEY (Adresse_ID)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Bln_Adr_Str_Bez\n"s +
      "ADD CONSTRAINT uk_neu_Bln_Adr_Str_Bez_Str UNIQUE(Strasse_ID, Nummer, ADZ)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Bln_Adr_Str_Bez\n"s +
      "ADD CONSTRAINT fk_neu_Bln_Adr_Str_Bez_Bln FOREIGN KEY(Adresse_ID) REFERENCES neu_Berlin (ID)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Bln_Adr_Str_Bez\n"s +
      "ADD CONSTRAINT fk_neu_Bln_Adr_Str_Bez_Str FOREIGN KEY(Strasse_ID) REFERENCES neu_Berlin_Strassen (ID)"s);

   New_Model.emplace_back(
      "CREATE INDEX idx_neu_Bln_Adr_Str_Bez ON neu_Bln_Adr_Str_Bez (PLZ)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Bln_Adr_OT_Bez\n"s +
      "ADD CONSTRAINT pk_neu_Bln_Adr_OT_Bez PRIMARY KEY (Adresse_ID)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Bln_Adr_OT_Bez\n"s +
      "ADD CONSTRAINT fk_neu_Bln_Adr_OT_Bez_Bln FOREIGN KEY (Adresse_ID) REFERENCES neu_Berlin (ID)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Bln_Adr_OT_Bez\n"s +
      "ADD CONSTRAINT fk_neu_Bln_Adr_OT_Bez_Ort FOREIGN KEY(Ortsteil_ID) REFERENCES neu_Berlin_Ortsteile (ID)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Bln_OT_Bzk_Bez\n"s +
      "ADD CONSTRAINT pk_neu_Bln_OT_Bez    PRIMARY KEY (Ortsteil_ID)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Bln_OT_Bzk_Bez\n"s +
      "ADD CONSTRAINT fk_neu_Bln_OT_Bzk_OT FOREIGN KEY (Ortsteil_ID) REFERENCES neu_Berlin_Ortsteile (ID)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Bln_OT_Bzk_Bez\n"s +
      "ADD CONSTRAINT fk_neu_Bln_OT_Bez FOREIGN KEY (Bezirk_ID) REFERENCES neu_Berlin_Bezirke (ID)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Bln_Str_OT_Bez\n"s +
      "ADD CONSTRAINT pk_neu_Bln_Str_Bez PRIMARY KEY (Strasse_ID, Ortsteil_ID)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Bln_Str_OT_Bez\n"s +
      "ADD CONSTRAINT fk_neu_Bln_Str_Str FOREIGN KEY (Strasse_ID) REFERENCES neu_Berlin_Strassen (ID)"s);

   New_Model.emplace_back(
      "ALTER TABLE neu_Bln_Str_OT_Bez\n"s +
      "ADD CONSTRAINT fk_neu_Bln_Str_OT FOREIGN KEY (Ortsteil_ID) REFERENCES neu_Berlin_Ortsteile (ID)"s);

   // Füllen der Tabellen mit Daten, die direkt aufgebaut werden können

   New_Model.emplace_back(
      "INSERT INTO neu_Berlin_Bezirke (Bezirk, Gueltig_ab, Land_Kz, Bezirk_Kz)\n"s +
      "  SELECT DISTINCT Bezirk, '01.01.2001', Land_ID, Bezirk_ID\n"s +
      "  FROM Berlin"s);

   New_Model.emplace_back(
      "INSERT neu_Berlin_Ortsteile (Ortsteil, Gueltig_ab, Land_Kz, Bezirk_Kz, Ortsteil_Kz)\n"s +
      "  SELECT DISTINCT Ortsteil, '01.01.2001', Land_ID, Bezirk_ID, Ortsteil_ID - 100 * Bezirk_ID\n"s +
      "  FROM Berlin"s);

   New_Model.emplace_back(
      "INSERT INTO neu_Berlin_Strassen (Strasse, Strasse_Kz, Strasse_Datum)\n"s +
      "  SELECT Strasse, Strasse_ID, MAX(Strasse_Datum)\n"s +
      "  FROM Berlin\n"s +
      "  GROUP BY Strasse, Strasse_ID"s);

   New_Model.emplace_back(
      "INSERT neu_Berlin_Qualitaet (Value)\n"s +
      "  SELECT DISTINCT Qualitaet\n"s +
      "  FROM Berlin"s);

   New_Model.emplace_back(
      "INSERT INTO neu_Berlin_Strasse_ohne_HNR (Strasse_ID, PLZ, Latitude, Longitude, Qualitaet)\n"s +
      "  SELECT bs.ID AS Strasse_ID, a.PLZ, a.Latitude, a.Longitude, bq.ID\n"s +
      "  FROM Berlin a JOIN neu_Berlin_Strassen bs ON(bs.Strasse_Kz = a.Strasse_ID)\n"s +
      "                JOIN neu_Berlin_Qualitaet bq ON(bq.Value = a.Qualitaet)\n"s +
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
         "SELECT a.PLZ, a.HNR AS Nummer, a.ADZ, a.Latitude, a.Longitude,a.Adresse_Datum,\n"s +
         "       s.ID AS Strasse_ID, o.ID AS Ortsteil_ID, aq.ID AS Adr_Qualitaet\n"s +
         "FROM Berlin a JOIN neu_Berlin_Strassen s ON (s.Strasse_Kz = a.Strasse_ID)\n"s +
         "              JOIN neu_Berlin_Ortsteile o ON (o.Bezirk_Kz = a.Bezirk_ID AND \n"s +
         "                                              o.Ortsteil_Kz = Ortsteil_ID - 100 * Bezirk_ID)"s +
         "              JOIN neu_Berlin_Qualitaet aq ON (aq.Value = a.Qualitaet)"
         "WHERE a.Adr_Typ <> 'Platz/Straße ohne HNR'"},
      { { "INSERT INTO neu_Berlin (Latitude, Longitude, Adresse_Datum, Qualitaet)\n"s +
          "VALUES (:Latitude, :Longitude, :Adresse_Datum, :Qualitaet)"s, true,
          [](TProcess::concrete_query& qry, TProcess::concrete_query& ins, int id) {
               ins.Set("Latitude",  qry.Get<double>("Latitude"));
               ins.Set("Longitude", qry.Get<double>("Longitude"));
               ins.Set("Adresse_Datum", qry.Get<std::chrono::year_month_day>("Adresse_Datum"));
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
      for(auto const& [etype, name] : clean) {
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


      query.SetSQL(get<1>(run.first));
      std::vector<TProcess::concrete_query> ins_qry;
      for(auto const& val : run.second) {
         ins_qry.emplace_back(db.CreateQuery(std::get<0>(val)));
         }

      size_t linecnt = 0;
      for(query.Execute(), query.First(); !query.IsEof(); query.Next()) {
         int last_ID = 0;
         for (size_t i = 0; auto const& val : run.second) {
            std::get<2>(val)(query, ins_qry[i], last_ID);
            ins_qry[i].Execute();
            if(std::get<1>(val)) last_ID = static_cast<QSqlQuery&>(ins_qry[i]).lastInsertId().toInt();
            ++i;
            }
         if (++linecnt % iStepstoMessage == 0) {
            std::clog << get<0>(run.first) << " -> " << linecnt << " rows inserted" << std::endl;
            TMyForm::ProcessEvents();
            }
         }
      std::string strEndMessage = std::format("{}, {} rows inserted in {}", get<0>(run.first), linecnt, FormatExecutionTime(start));
      std::cerr << std::format("{}: {}\n", get_current_time_and_date(), strEndMessage);
      std::clog << strEndMessage << std::endl;

      }
   catch (TMy_Db_Exception& ex) {
      HandleException(std::format("migrate {}", strMessage), ex);
      }
   catch (std::exception& ex) {
      HandleException(std::format("migrate {}", strMessage), ex);
      }
   }



std::vector<TProcess::migrate_data> TProcess::MigrationControl {
   
      {  // Berliner Rohdaten 
      "data for Berlin"s, "Berlin"s, "d:\\test\\Adressen_-_Berlin.csv"s, ",",
      "DELETE FROM Berlin"s,
      "INSERT INTO Berlin (Land_ID,Bezirk_ID,Ortsteil_ID,Strasse_ID,Land,Stadt,Bezirk,Ortsteil,Strasse,PLZ,HNR,ADZ,Latitude,Longitude,Adresse_Datum,Strasse_Datum,Qualitaet,Adr_Typ)\n"s
      "VALUES(:Land_ID,:Bezirk_ID,:Ortsteil_ID,:Strasse_ID,:Land,:Stadt,:Bezirk,:Ortsteil,:Strasse,:PLZ,:HNR,:ADZ,:Latitude,:Longitude,:Adresse_Datum,:Strasse_Datum,:Qualitaet,:Adr_Typ)"s,
      [](concrete_query& query, std::vector<std::string_view> const& data) {
         query.Set("Land_ID", 11);
         query.Set("Bezirk_ID", string_to_int<int>(data[10]));
         query.Set("Ortsteil_ID", string_to_int<int>(data[12]));
         query.Set("Strasse_ID", string_to_int<int>(data[6]));
         query.Set("Land", data[21]);
         query.Set("Stadt", data[21]);
         query.Set("Bezirk", data[9]);
         query.Set("Ortsteil", data[11]);
         query.Set("Strasse", data[7]);
         query.Set("PLZ", data[8]);
         query.Set("HNR", string_to_int<int>(data[4]));
         query.Set("ADZ", data[5]);
         for (auto const& [id, field] : { std::make_pair( 16, "Adresse_Datum"s), 
                                          std::make_pair( 17, "Strasse_Datum"s) } ){
            std::istringstream ins(std::string { data[id].begin(), data[id].end() });
            std::chrono::year_month_day aDate;
            std::chrono::from_stream(ins, "%Y/%m/%d", aDate);
            query.Set(field, aDate);
            }
         query.Set("Qualitaet", data[18]);
         query.Set("Adr_Typ", data[19]);
         myMercatorETRS89<double> loc { string_to_float<double>(data[0]), string_to_float<double>(data[1]) };
         auto position = Location<double>::ConvertMercatorETRS89ToWGS84(loc);
         query.Set("Latitude", position.first);
         query.Set("Longitude", position.second);
         return true;
         }
      },
      {  // Brandenburger Rohdaten 
      "data for Brandenburg"s, "Brandenburg"s, "d:\\test\\Adressen_-_Brandenburg.csv"s, ",",
      "DELETE FROM Brandenburg"s,
      "INSERT INTO Brandenburg (Land_ID, Region_ID,Kreis_ID,Gemeinde_ID,Ortsteil_ID,Strasse_ID,HNR,ADZ,Land,Kreis,Amt,Gemeinde,Ort,Strasse,PLZ,Latitude,Longitude)\n"s
      "VALUES (:Land_ID,:Region_ID,:Kreis_ID,:Gemeinde_ID,:Ortsteil_ID,:Strasse_ID,:HNR,:ADZ,:Land,:Kreis,:Amt,:Gemeinde,:Ort,:Strasse,:PLZ,:X,:Y)"s,
      [](concrete_query& query, std::vector<std::string_view> const& data) {
         query.Set("Land_ID",     string_to_int<int>(data[5]));
         query.Set("Region_ID",   string_to_int<int>(data[6]));
         query.Set("Kreis_ID",    string_to_int<int>(data[7]));
         query.Set("Gemeinde_ID", string_to_int<int>(data[8]));
         query.Set("Ortsteil_ID", string_to_int<int>(data[9]));
         query.Set("Strasse_ID",  string_to_int<int>(data[10]));
         query.Set("HNR",         string_to_int<int>(data[13]));
         query.Set("ADZ",         data[14]);
         query.Set("Land",        data[16]);
         query.Set("Kreis",       data[17]);
         query.Set("Amt",         data[18]);
         query.Set("Gemeinde",    data[19]);
         query.Set("Ort",         data[20]);
         query.Set("Strasse",     data[21]);
         query.Set("PLZ",         data[22]);
         myMercatorETRS89<double> loc { string_to_float<double>(data[0]), string_to_float<double>(data[1]) };
         auto position = Location<double>::ConvertMercatorETRS89ToWGS84(loc);
         query.Set("X", position.first);
         query.Set("Y", position.second);
         return true;
         }
      },      
      {  // zusätzliche Daten zur Verwaltungen 
      "data for administrations"s, "Verwaltungen"s, "d:\\test\\Verwaltungen.txt"s, ";",
      "DELETE FROM Verwaltungen"s,
      "INSERT INTO Verwaltungen (Schluessel,Kategorie,Bezug,Bezeichnung,Strasse,Strasse_Nummer,PLZ,Stadt,Breitengrad,Laengengrad)\n"s
      "VALUES(:Schluessel,:Kategorie,:Bezug,:Bezeichnung,:Strasse,:Strasse_Nummer,:PLZ,:Stadt,:Breitengrad,:Laengengrad)"s,
      [](concrete_query& query, std::vector<std::string_view> const& data) {
         if (data.size() != 10) {
            std::ostringstream os;
            os << "corrupted data found: "s
               << std::string{ data[0].begin(), data[0].end() } << " / "
               << std::string{ data[1].begin(), data[1].end() } << " / "
               << std::string{ data[2].begin(), data[2].end() } << ".\n";
            throw TMy_RuntimeError(os.str());
            }

         query.Set("Schluessel",     data[0]);
         query.Set("Kategorie",      data[1]);
         query.Set("Bezug",          data[2]);
         query.Set("Bezeichnung",    data[3]);
         query.Set("Strasse",        data[4]);
         query.Set("Strasse_Nummer", data[5]);
         query.Set("PLZ",            data[6]);
         query.Set("Stadt",          data[7]);
         query.Set("Breitengrad",    string_to_float<double>(data[8]));
         query.Set("Laengengrad",    string_to_float<double>(data[9]));
         return true;
         }
      },
      { 
      "keys for Thuringa"s, "Thueringen_Schluessel"s, "d:\\test\\schluessel-th.txt"s, ";",
      "DELETE FROM Thueringen_Schluessel"s,
      "INSERT INTO Thueringen_Schluessel (Satzart, Land_ID, Region_ID, Kreis_ID, Gemeinde_ID, Bezeichnung)\n"s +
      "VALUES(:Satzart, :Land_ID, :Region_ID, :Kreis_ID, :Gemeinde_ID, :Bezeichnung)"s,
      [](concrete_query& query, std::vector<std::string_view> const& data) {
         static std::optional<int> null_value = { };   // concept
         //static int null_value = 0;
         switch (data[0][0]) {
         case 'L':
            query.Set("Satzart", "Land");
            query.Set("Land_ID", std::make_optional(string_to_int<int>(data[1])));
            query.Set("Region_ID",   null_value);
            query.Set("Kreis_ID",    null_value);
            query.Set("Gemeinde_ID", null_value);
            query.Set("Bezeichnung", data[2]);
            break;
         case 'R': return false;
         case 'K':
            query.Set("Satzart", "Kreis");
            query.Set("Land_ID", string_to_int<int>(data[1]));
            query.Set("Region_ID", string_to_int<int>(data[2]));
            query.Set("Kreis_ID", string_to_int<int>(data[3]));
            query.Set("Gemeinde_ID", null_value);
            query.Set("Bezeichnung", data[4]);
            break;
         case 'G':
            query.Set("Satzart", "Gemeinde");
            query.Set("Land_ID", string_to_int<int>(data[1]));
            query.Set("Region_ID", string_to_int<int>(data[2]));
            query.Set("Kreis_ID",    string_to_int<int>(data[3]));
            query.Set("Gemeinde_ID", string_to_int<int>(data[4]));
            query.Set("Bezeichnung", data[5]);
            break;
         default:
            throw TMy_RuntimeError("Unexpected Content for Data: "s + std::string { data[0].begin(), data[0].end() });
            }
         return true;
         }
      },
      {   // Einfügen der Daten für Thüringen 
      "data for Thuringa"s, "Thueringen"s, "d:\\test\\Adressen_-_Thueringen.csv"s, ",",
      "DELETE FROM Thueringen"s,
      "INSERT INTO Thueringen (Land_ID,Region_ID,Kreis_ID,Gemeinde_ID,Ortsteil_ID,Strasse_ID,Strasse,HNR,ADZ,PLZ,Laengengrad,Breitengrad)\n"s +
      "VALUES(:Land_ID,:Region_ID,:Kreis_ID,:Gemeinde_ID,:Ortsteil_ID,:Strasse_ID,:Strasse,:HNR,:ADZ,:PLZ,:Laengengrad,:Breitengrad)"s,
      [](concrete_query& query, std::vector<std::string_view> const& data) {
         query.Set("Land_ID",     string_to_int<int>(data[6]));
         query.Set("Region_ID",   string_to_int<int>(data[7]));
         query.Set("Kreis_ID",    string_to_int<int>(data[8]));
         query.Set("Gemeinde_ID", string_to_int<int>(data[9]));
         query.Set("Ortsteil_ID", string_to_int<int>(data[10]));
         query.Set("Strasse_ID",  string_to_int<int>(data[11]));
         query.Set("Strasse",     data[16]);
         query.Set("HNR",         string_to_int<int>(data[12]));
         query.Set("ADZ",         data[13]);
         query.Set("PLZ", "");
         myMercatorETRS89<double> loc { string_to_float<double>(data[0]), string_to_float<double>(data[1]) };
         auto position = Location<double>::ConvertMercatorETRS89ToWGS84(loc);
         query.Set("Laengengrad", position.first);
         query.Set("Breitengrad", position.second);
         return true;
         }
      },
      { 
      "keys for Saxony"s, "Sachsen_Schluessel"s, "d:\\test\\hk_sn_schluessel.txt"s, ";",
      "DELETE FROM Sachsen_Schluessel"s,
      "INSERT INTO Sachsen_Schluessel (Satzart, Land_ID, Region_ID, Kreis_ID, Gemeinde_ID, Ortsteil_ID, Bezeichnung)\n"s +
      "VALUES(:Satzart, :Land_ID, :Region_ID, :Kreis_ID, :Gemeinde_ID, :Ortsteil_ID, :Bezeichnung)"s,
      [](concrete_query& query, std::vector<std::string_view> const& data) {
         static std::optional<int> null_value = { };   // concept
         //static int null_value = 0;
         switch (data[0][0]) {
         case 'L':
            query.Set("Satzart", "Land");
            query.Set("Land_ID",     std::make_optional(string_to_int<int>(data[1])));
            query.Set("Region_ID",   null_value);
            query.Set("Kreis_ID",    null_value);
            query.Set("Gemeinde_ID", null_value);
            query.Set("Ortsteil_ID", null_value);
            query.Set("Bezeichnung", data[2]);
            break;
         case 'R':
            query.Set("Satzart", "Region");
            query.Set("Land_ID",     string_to_int<int>(data[1]));
            query.Set("Region_ID",   string_to_int<int>(data[2]));
            query.Set("Kreis_ID",    null_value);
            query.Set("Gemeinde_ID", null_value);
            query.Set("Ortsteil_ID", null_value);
            query.Set("Bezeichnung", data[3]);
            break;
         case 'K':
            query.Set("Satzart", "Kreis");
            query.Set("Land_ID", string_to_int<int>(data[1]));
            query.Set("Region_ID", string_to_int<int>(data[2]));
            query.Set("Kreis_ID", string_to_int<int>(data[3]));
            query.Set("Gemeinde_ID", null_value);
            query.Set("Ortsteil_ID", null_value);
            query.Set("Bezeichnung", data[4]);
            break;
         case 'G':
            query.Set("Satzart", "Gemeinde");
            query.Set("Land_ID",     string_to_int<int>(data[1]));
            query.Set("Region_ID",   string_to_int<int>(data[2]));
            query.Set("Kreis_ID",    string_to_int<int>(data[3]));
            query.Set("Gemeinde_ID", string_to_int<int>(data[4]));
            query.Set("Ortsteil_ID", null_value);
            if (data[5] == "unbesetzt"sv) query.Set("Bezeichnung", null_value);
            else query.Set("Bezeichnung", data[5]);
            break;
         case 'O':
            query.Set("Satzart", "Ortsteil");
            query.Set("Land_ID", string_to_int<int>(data[1]));
            query.Set("Region_ID", string_to_int<int>(data[2]));
            query.Set("Kreis_ID", string_to_int<int>(data[3]));
            query.Set("Gemeinde_ID", string_to_int<int>(data[4]));
            query.Set("Ortsteil_ID", string_to_int<int>(data[5]));
            if (data[6] == "unbesetzt"sv) query.Set("Bezeichnung", null_value);
            else query.Set("Bezeichnung", data[6]);
            break;
         default:
            throw TMy_RuntimeError("Unexpected Content for Data: "s + std::string { data[0].begin(), data[0].end() });
            }
         return true;
         }
      },
      {
      "data for Saxony"s, "Sachsen"s, "d:\\test\\Adressen_-_Sachsen.csv"s, ",",
         "DELETE FROM Sachsen"s,
         "INSERT INTO Sachsen (Strasse, Nummer, Zusatz, PLZ, Ort, Ortsteil, Land_ID, Region_ID, Kreis_ID, Gemeinde_ID, Ortsteil_ID, Strasse_ID, Laengengrad, Breitengrad)"s +
         "VALUES(:Strasse, :Nummer, :Zusatz, :PLZ, :Ort, :Ortsteil, :Land_ID, :Region_ID, :Kreis_ID, :Gemeinde_ID, :Ortsteil_ID, :Strasse_ID, :Laengengrad, :Breitengrad)"s,
      [](concrete_query& query, std::vector<std::string_view> const& data) {
         query.Set("Nummer", string_to_int<int>(data[4]));
         query.Set("Zusatz", data[5]);
         query.Set("Strasse", data[6]);
         query.Set("PLZ", data[7]);
         query.Set("Ort", data[8]);
         query.Set("Ortsteil", data[9]);
         query.Set("Land_ID", string_to_int<int>(data[10]));
         query.Set("Region_ID", string_to_int<int>(data[11]));
         query.Set("Kreis_ID", string_to_int<int>(data[12]));
         query.Set("Gemeinde_ID", string_to_int<int>(data[13]));
         query.Set("Ortsteil_ID", string_to_int<int>(data[14]));
         query.Set("Strasse_ID", string_to_int<int>(data[15]));
         myMercatorETRS89<double> loc { string_to_float<double>(data[0]), string_to_float<double>(data[1]) };
         auto position = Location<double>::ConvertMercatorETRS89ToWGS84(loc);
         query.Set("Laengengrad", position.first);
         query.Set("Breitengrad", position.second);
         return true;
         }
     },
  };

void TProcess::insert_into_database(std::vector<migrate_variants> kinds) {
   static constexpr auto col_val = [](migrate_data_columns col) { return static_cast<int>(col); };
   std::string strBuffer;
   bool boDeleteBeforeInsert = false;
   std::string strMessage = ""s;
   std::ostringstream os;
   for (size_t i{ 0 }; auto const& kind : kinds) {
      TProcess::migrate_data const& contrl = MigrationControl[static_cast<int>(kind)];
      os << (i++ > 0 ? "\n" : "") << std::get<col_val(migrate_data_columns::theme)>(contrl);
      }
   try {
      switch (auto ret = frm.Message(EMyMessageType::question, os.str(), "Want you delete the existing data?"); ret) {
         case EMyRetResults::ok:
            boDeleteBeforeInsert = true;
            break;
         case EMyRetResults::no: break;
         case EMyRetResults::cancel: throw TMy_UserBreak(os.str() + " canceled by user.");
         default: throw TMy_RuntimeError(os.str() + ", unexpected answer for Message for delete existig data.");
         }

        TMyWait wait;
        for (auto const& kind : kinds) {
           TProcess::migrate_data const& contrl = MigrationControl[static_cast<int>(kind)];
           strMessage = "inserting "s + std::get<col_val(migrate_data_columns::theme)>(contrl);
           if (boDeleteBeforeInsert == true) {
              auto del_query = db.CreateQuery();
              del_query.SetSQL(std::get<col_val(migrate_data_columns::del_stmt)>(contrl));
              del_query.Execute();
           }

           auto start = std::chrono::system_clock::now();
           auto query = db.CreateQuery();
           query.SetSQL(std::get<col_val(migrate_data_columns::ins_stmt)>(contrl));
           std::cerr << std::format("{}: inserting {} started ...\n", get_current_time_and_date(), 
                                                   std::get<col_val(migrate_data_columns::theme)>(contrl));
           std::clog << std::format("inserting {} started\n", std::get<col_val(migrate_data_columns::theme)>(contrl));
           TMyForm::ProcessEvents();
           int linecnt = 0;
           for (auto const& line : my_lines{ GetContent(std::get<col_val(migrate_data_columns::input_file)>(contrl), strBuffer) }) {
              auto test = std::string_view{ line.begin(), line.end() } | std::views::split(std::get<col_val(migrate_data_columns::delimiter)>(contrl))
                 | std::views::transform([](auto d) { return std::string_view{ d.begin(), d.end() }; })
                 | std::ranges::to<std::vector>();

              if (std::get<col_val(migrate_data_columns::set)>(contrl)(query, test)) query.Execute();
              if (++linecnt % 50000 == 0) {
                 std::clog << std::get<col_val(migrate_data_columns::theme)>(contrl) << " -> " << linecnt << " rows inserted" << std::endl;
                 TMyForm::ProcessEvents();
              }
           }
           std::string strEndMessage = std::format(myLoc, "{}, {} rows inserted in {}", std::get<col_val(migrate_data_columns::theme)>(contrl), linecnt, FormatExecutionTime(start));
           std::cerr << std::format("{}: {}\n", get_current_time_and_date(), strEndMessage);
           std::clog << strEndMessage << std::endl;
        }
        std::clog << "all finished";
        std::cerr << get_current_time_and_date() << ": " << " finished.\n";
     }
     catch (TMy_UserBreak& ex) {
        HandleException(strMessage, ex);
     }
     catch (TMy_Db_Exception& ex) {
        HandleException(strMessage, ex);
     }
     catch (std::exception& ex) {
        HandleException(strMessage, ex);
     }
  }
