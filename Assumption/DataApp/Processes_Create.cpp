
#include "Processes.h"
#include "MyLocation.h"
#include "MyDatabaseExceptions.h"

std::vector<TProcess::migrate_data> TProcess::MigrationControl {

   {  // Berliner Rohdaten 
      "data for Berlin"s, 
      { { TProcess::EEntity_type::view, "vw_Berliner_Strassen_Bezirk"s }, 
        { TProcess::EEntity_type::view, "vw_Berliner_Strassen_Ortsteile"s },
        { TProcess::EEntity_type::view, "vw_Berliner_Strassen"s },
        { TProcess::EEntity_type::view, "vw_Berliner_Ortsteile"s },
        { TProcess::EEntity_type::view, "vw_Berliner_Bezirke"s },
        { TProcess::EEntity_type::table, "Berliner_Ortsteile"s },
        { TProcess::EEntity_type::table, "Berliner_Stadtbezirke" },
        { TProcess::EEntity_type::table, "Berlin"s } },

      { "CREATE TABLE Berlin (\n"s +
        "   Land_ID       INTEGER ,\n"s +
        "   Bezirk_ID     INTEGER ,\n"s +
        "   Ortsteil_ID   INTEGER ,\n"s +
        "   Strasse_ID    INTEGER ,\n"s +
        "   Land          VARCHAR(75) ,\n"s +
        "   Stadt         VARCHAR(75) ,\n"s +
        "   Bezirk        VARCHAR(75) ,\n"s +
        "   Ortsteil      VARCHAR(75) ,\n"s +
        "   Strasse       VARCHAR(75) ,\n"s +
        "   PLZ           VARCHAR(5) ,\n"s +
        "   HNR           INTEGER ,\n"s +
        "   ADZ           VARCHAR(5) ,\n"s +
        "   Latitude      FLOAT ,\n"s +
        "   Longitude     FLOAT ,\n"s +
        "   Adr_Datum     DATE ,\n"s +
        "   Strasse_Datum DATE ,\n"s +
        "   Qualitaet     VARCHAR(100) ,\n"s +
        "   Adr_Typ       VARCHAR(100) ,\n"s +
        "   HKO_ID        VARCHAR(20) \n"s +
        "   )"s, 
      
        "CREATE TABLE Berliner_Stadtbezirke ("s +
        "   Stadtbezirk        VARCHAR(75),"s +
        "   Abkuerzung         VARCHAR(10),"s +
        "   Land_ID            INTEGER,"s +
        "   Bezirk_ID          INTEGER,"s +
        "   Breite_Mitte       FLOAT,"s +
        "   Laenge_Mitte       FLOAT,"s +
        "   Rathaus            VARCHAR(75),"s +
        "   Rathaus_PLZ        VARCHAR(5),"s +
        "   Rathaus_Ort        VARCHAR(75),"s +
        "   Rathaus_Strasse    VARCHAR(75),"s +
        "   Rathaus_Nummer     VARCHAR(20),"s +
        "   Rathaus_Breite     FLOAT,"s +
        "   Rathaus_Laenge     FLOAT"s +
        "   )"s,

        "CREATE TABLE Berliner_Ortsteile( "s +
        "   Land_ID      INTEGER,"s +
        "   Bezirk_ID    INTEGER,"s +
        "   Ortsteil_ID  INTEGER,"s +
        "   Bezirk       VARCHAR(75),"s +
        "   Ortsteil     VARCHAR(75),"s +
        "   Breite       FLOAT,"s +
        "   Laenge       FLOAT"s +
        "   )"s,

        "CREATE VIEW vw_Berliner_Bezirke\n"s +
        "AS\n"s +
        "   SELECT DISTINCT Land_ID, Bezirk_ID, Land, Stadt, Bezirk\n"s +
        "   FROM Berlin"s,

        "CREATE VIEW vw_Berliner_Ortsteile\n"s +
        "AS\n"s +
        "  SELECT DISTINCT Land_ID, Bezirk_ID, Ortsteil_ID, Land, Stadt, Bezirk, Ortsteil\n"s +
        "  FROM Berlin"s,

        "CREATE VIEW vw_Berliner_Strassen_Ortsteile\n"s +
        "AS\n"s +
        "  SELECT DISTINCT Land_ID, Bezirk_ID,  Ortsteil_ID, Strasse_ID, Land, Stadt, Bezirk, Ortsteil, Strasse\n"s +
        "  FROM Berlin"s,

        "CREATE VIEW vw_Berliner_Strassen_Bezirk\n"s +
        "AS\n"s +
        "  SELECT DISTINCT Land_ID, Bezirk_ID, Strasse_ID, Land, Stadt, Bezirk, Strasse\n"s +
        "  FROM Berlin"s,

        "CREATE VIEW vw_Berliner_Strassen\n"s +
        "AS\n"s +
        "  SELECT DISTINCT Land_ID, Strasse_ID, Land, Strasse\n"s +
        "  FROM Berlin"s
      
      },

      "d:\\test\\Adressen_-_Berlin.csv"s, ",", "d:\\test\\Berlin_Zusatz.txt"s,
      { "DELETE FROM Berlin"s,
        "DELETE FROM Berliner_Ortsteile",
        "DELETE FROM Berliner_Stadtbezirke" },
      "INSERT INTO Berlin (Land_ID,Bezirk_ID,Ortsteil_ID,Strasse_ID,Land,Stadt,Bezirk,Ortsteil,Strasse,PLZ,HNR,ADZ,Latitude,Longitude,Adr_Datum,Strasse_Datum,Qualitaet,Adr_Typ,HKO_ID)\n"s
      "VALUES(:Land_ID,:Bezirk_ID,:Ortsteil_ID,:Strasse_ID,:Land,:Stadt,:Bezirk,:Ortsteil,:Strasse,:PLZ,:HNR,:ADZ,:Latitude,:Longitude,:Adr_Datum,:Strasse_Datum,:Qualitaet,:Adr_Typ,:HKO_ID)"s,
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
         for (auto const& [id, field] : { std::make_pair(16, "Adr_Datum"s),
                                          std::make_pair(17, "Strasse_Datum"s) }) {
            std::istringstream ins(std::string { data[id].begin(), data[id].end() });
            std::chrono::year_month_day aDate;
            std::chrono::from_stream(ins, "%Y/%m/%d", aDate);
            query.Set(field, aDate);
            }
         query.Set("Qualitaet", data[18]);
         query.Set("Adr_Typ", data[19]);
         query.Set("HKO_ID", data[20]);

         myMercatorETRS89<double> loc { string_to_float<double>(data[0]), string_to_float<double>(data[1]) };
         auto position = Location<double>::ConvertMercatorETRS89ToWGS84(loc);
         query.Set("Latitude", position.first);
         query.Set("Longitude", position.second);
         return true;
         }
   },
   {  // Brandenburger Rohdaten 
      "data for Brandenburg"s, 
      {  { TProcess::EEntity_type::view,  "vw_Brandenburger_Gemeinden"s },
         { TProcess::EEntity_type::view,  "vw_Brandenburger_Kreise"s },
         { TProcess::EEntity_type::view,  "vw_Brandenburger_Struktur"s },
         { TProcess::EEntity_type::table, "Brandenburg_Gemeinden"s },
         { TProcess::EEntity_type::table, "Brandenburg_Staedte"s },
         { TProcess::EEntity_type::table, "Brandenburg_Kreise"s },
         { TProcess::EEntity_type::table, "Brandenburg"s } 
      },

      { "CREATE TABLE Brandenburg (\n"s +
        "  Land_ID     integer ,\n"s +
        "  Region_ID   integer ,\n"s +
        "  Kreis_ID    integer ,\n"s +
        "  Gemeinde_ID integer ,\n"s +
        "  Ortsteil_ID integer ,\n"s +
        "  Strasse_ID  integer ,\n"s +
        "  HNR         integer ,\n"s +
        "  ADZ         varchar(5) ,\n"s +
        "  Land        varchar(75) ,\n"s +
        "  Kreis       varchar(75) ,\n"s +
        "  Amt         varchar(75) ,\n"s +
        "  Gemeinde    varchar(75) ,\n"s +
        "  Ort         varchar(75) ,\n"s +
        "  Strasse     varchar(75) ,\n"s +
        "  PLZ         varchar(5) ,\n"s +
        "  Latitude    float ,\n"s +
        "  Longitude   float \n"s +
        "  )"s,

        "CREATE TABLE Brandenburg_Kreise (\n"s +
        "  Kreis            varchar(75),\n"s +
        "  Kreisstadt       varchar(75),\n"s +
        "  Status           varchar(75),\n"s +
        "  Abkuerzung       varchar(10),\n"s +
        "  Land_ID          integer,\n"s +
        "  Kreis_ID         integer,\n"s +
        "  Breite           float,\n"s +
        "  Laenge           float,\n"s +
        "  Rathaus          varchar(75),\n"s +
        "  Rathaus_PLZ      varchar(5),\n"s +
        "  Rathaus_Ort      varchar(75),\n"s +
        "  Rathaus_Strasse  varchar(75),\n"s +
        "  Rathaus_Nummer   varchar(20),\n"s +
        "  Rathaus_Breite   float,\n"s +
        "  Rathaus_Laenge   float\n"s +
        "  )"s,

        "CREATE TABLE Brandenburg_Staedte (\n"s +
        "  Stadt            varchar(75),\n"s +
        "  Stadt_sorbisch   varchar(75),\n"s +
        "  Kreis            varchar(75),\n"s +
        "  Abkuerzung_Kreis varchar(10),\n"s +
        "  Status           varchar(75),\n"s +
        "  Breite           float,\n"s +
        "  Laenge           float,\n"s +
        "  Land_ID          integer,\n"s +
        "  Kreis_ID         integer,\n"s +
        "  Gemeinde_ID      integer,\n"s +
        "  Rathaus          varchar(75),\n"s +
        "  Rathaus_PLZ      varchar(5),\n"s +
        "  Rathaus_Ort      varchar(75),\n"s +
        "  Rathaus_Strasse  varchar(75),\n"s +
        "  Rathaus_Nummer   varchar(20),\n"s +
        "  Rathaus_Breite   float,\n"s +
        "  Rathaus_Laenge   float\n"s +
        "  )"s,

        "CREATE TABLE Brandenburg_Gemeinden (\n"s +
        "  Gemeinde           varchar(75),\n"s +
        "  Landkreis          varchar(75),\n"s +
        "  Amt                varchar(75),\n"s +
        "  Art                varchar(75),\n"s +
        "  Breite             float,\n"s +
        "  Laenge             float,\n"s +
        "  Land_ID            integer,\n"s +
        "  Kreis_ID           integer,\n"s +
        "  Gemeinde_ID        integer,\n"s +
        "  Ort                varchar(75),\n"s +
        "  Verwaltung         varchar(75),\n"s +
        "  Verwaltung_PLZ     varchar(5),\n"s +
        "  Verwaltung_Ort     varchar(75),\n"s +
        "  Verwaltung_Strasse varchar(75),\n"s +
        "  Verwaltung_Nummer  varchar(20),\n"s +
        "  Verwaltung_Breite  float,\n"s +
        "  Verwaltung_Laenge  float\n"s +
        "  )"s,

        "CREATE VIEW vw_Brandenburger_Struktur\n"s +
        "AS\n"s +
        "  SELECT Land_ID, Region_ID, Kreis_ID, Gemeinde_ID, Ortsteil_ID, Land, Kreis, Gemeinde, Ort, count(*) AS Anzahl\n"s +
        "  FROM Brandenburg\n"s +
        "  GROUP BY Land_ID, Region_ID, Kreis_ID, Gemeinde_ID, Ortsteil_ID, Land, Kreis, Gemeinde, Ort"s,

        "CREATE VIEW vw_Brandenburger_Kreise\n"s +
        "AS\n"s +
        "  SELECT DISTINCT a.Land_ID, a.Kreis_ID, a.Land, a.Kreis, 'kreisfreie Stadt' AS Art\n"s +
        "  FROM Brandenburg a\n"s +
        "  WHERE NOT EXISTS(SELECT *\n"s +
        "                   FROM Brandenburg b\n"s +
        "                   WHERE b.Land_ID = a.Land_ID AND b.Kreis_ID = a.Kreis_ID AND\n"s +
        "                         b.Gemeinde_ID < > 0)\n"s +
        "UNION\n"s +
        "  SELECT DISTINCT a.Land_ID, a.Kreis_ID, a.Land, a.Kreis, 'Landkreis' AS Art\n"s +
        "  FROM Brandenburg a\n"s +
        "  WHERE EXISTS(SELECT *\n"s +
        "               FROM Brandenburg b\n"s +
        "               WHERE b.Land_ID = a.Land_ID AND b.Kreis_ID = a.Kreis_ID AND\n"s +
        "                     b.Gemeinde_ID < > 0)"s,

        "CREATE VIEW vw_Brandenburger_Gemeinden\n"s +
        "AS\n"s +
        "  SELECT DISTINCT a.Land_ID, a.Kreis_ID, a.Gemeinde_ID, a.Land, a.Kreis, a.Gemeinde, 'Gemeinde' AS Art\n"s +
        "  FROM Brandenburg a\n"s +
        "  WHERE NOT EXISTS(SELECT *\n"s +
        "                    FROM Brandenburg_Staedte b\n"s +
        "                   WHERE b.Land_ID = a.Land_ID AND b.Kreis_ID = a.Kreis_ID AND b.Gemeinde_ID = a.Gemeinde_ID)\n"s +
        "UNION\n"s +
        "  SELECT DISTINCT a.Land_ID, a.Kreis_ID, a.Gemeinde_ID, a.Land, a.Kreis, a.Gemeinde, 'Stadt' AS Art\n"s +
        "  FROM Brandenburg a\n"s +
        "  WHERE EXISTS(SELECT *\n"s +
        "                FROM Brandenburg_Staedte b\n"s +
        "                WHERE b.Land_ID = a.Land_ID AND b.Kreis_ID = a.Kreis_ID AND b.Gemeinde_ID = a.Gemeinde_ID)"s
      },

      "d:\\test\\Adressen_-_Brandenburg.csv"s, ",", "d:\\test\\Brandenburg_Zusatz.txt"s,
      { "DELETE FROM Brandenburg"s },
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
      "data for administrations"s, 
      { { TProcess::EEntity_type::table, "Verwaltungen"s } },
      { "CREATE TABLE Verwaltungen (\n"s +
        "  Schluessel     varchar(75) ,\n"s +
        "  Kategorie      varchar(75) ,\n"s +
        "  Bezug          varchar(75) ,\n"s +
        "  Bezeichnung    varchar(75) ,\n"s +
        "  Strasse        varchar(75) ,\n"s +
        "  Strasse_Nummer varchar(20) ,\n"s +
        "  PLZ            varchar(5) ,\n"s +
        "  Stadt          varchar(75) ,\n"s +
        "  Breitengrad    float ,\n"s +
        "  Laengengrad    float \n"s + 
        "  )"s },

      "d:\\test\\Verwaltungen.txt"s, ";", ""s,
      { "DELETE FROM Verwaltungen"s },
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
      "keys for Thuringa"s, 
      { { TProcess::EEntity_type::table, "Thueringen_Schluessel"s } },
      { "CREATE TABLE Thueringen_Schluessel (\n"s +
        "  Satzart          varchar(20) ,\n"s +
        "  Land_ID          integer ,\n"s +
        "  Region_ID        integer ,\n"s +
        "  Kreis_ID         integer ,\n"s +
        "  Gemeinde_ID      integer ,\n"s +
        "  Bezeichnung      varchar(75)\n"s +
        "  )\n"s },

      "d:\\test\\schluessel-th.txt"s, ";", ""s,
      { "DELETE FROM Thueringen_Schluessel"s },
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
      "data for Thuringa"s, 
      { { TProcess::EEntity_type::table, "Thueringen"s } },
      { "CREATE TABLE Thueringen(\n"s +
        "  Land_ID          integer ,\n"s +
        "  Region_ID        integer ,\n"s +
        "  Kreis_ID         integer ,\n"s +
        "  Gemeinde_ID      integer ,\n"s +
        "  Strasse_ID       integer ,\n"s +
        "  Strasse          varchar(75) ,\n"s +
        "  HNR              integer ,\n"s +
        "  ADZ              varchar(5) ,\n"s +
        "  PLZ              varchar(5) ,\n"s +
        "  Laengengrad      float ,\n"s +
        "  Breitengrad      float \n"s +
        "  )"s },

      "d:\\test\\Adressen_-_Thueringen.csv"s, ",", ""s,
      { "DELETE FROM Thueringen"s },
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
      "keys for Saxony"s, 
      { { TProcess::EEntity_type::table, "Sachsen_Schluessel"s } },
      { "CREATE TABLE Sachsen_Schluessel (\n"s +
        "  Satzart          VARCHAR(20) ,\n"s +
        "  Land_ID          INTEGER ,\n"s +
        "  Region_ID        INTEGER ,\n"s +
        "  Kreis_ID         INTEGER ,\n"s +
        "  Gemeinde_ID      INTEGER ,\n"s +
        "  Ortsteil_ID      INTEGER ,\n"s +
        "  Bezeichnung      VARCHAR(75)\n"s +
        "  )"s },

      "d:\\test\\hk_sn_schluessel.txt"s, ";", ""s,
      { "DELETE FROM Sachsen_Schluessel"s } ,
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
      "data for Saxony"s, 
      { { TProcess::EEntity_type::table, "Sachsen"s } },
      { "CREATE TABLE Sachsen (\n"s +
        "  Strasse     VARCHAR(75) ,\n"s +
        "  Nummer      INTEGER ,\n"s +
        "  Zusatz      VARCHAR(20) ,\n"s +
        "  PLZ         VARCHAR(5) ,\n"s +
        "  Ort         VARCHAR(75) ,\n"s +
        "  Ortsteil    VARCHAR(75) ,\n"s +
        "  Land_ID     INTEGER ,\n"s +
        "  Region_ID   INTEGER ,\n"s +
        "  Kreis_ID    INTEGER ,\n"s +
        "  Gemeinde_ID INTEGER ,\n"s +
        "  Ortsteil_ID INTEGER ,\n"s +
        "  Strasse_ID  INTEGER ,\n"s +
        "  Laengengrad FLOAT ,\n"s +
        "  Breitengrad FLOAT \n"s +
        "  )"s },

      "d:\\test\\Adressen_-_Sachsen.csv"s, ",", ""s,
      { "DELETE FROM Sachsen"s },
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

   try {

   auto allViews = db.GetViewNames("");
   auto allTables = db.GetTableNames("");

   auto query = db.CreateQuery();
   bool boExecute = false;
   for (auto const& kind : kinds) {
      TProcess::migrate_data& contrl = MigrationControl[static_cast<int>(kind)];
      for (auto& [etype, name] : std::get<col_val(migrate_data_columns::to_delete)>(contrl)) {
         if constexpr (std::is_same<concrete_db_server, TMyOracle>::value || std::is_same<concrete_db_server, TMyInterbase>::value) {
            std::transform(name.begin(), name.end(), name.begin(), [](auto c) { return std::toupper(c);  });
            }
         else if constexpr (std::is_same<concrete_db_server, TMyMySQL>::value) {
            std::transform(name.begin(), name.end(), name.begin(), [](auto c) { return std::tolower(c);  });
            }

         switch (etype) {
            case EEntity_type::view:
               if (boExecute = allViews.find(name) != allViews.end(); boExecute) query.SetSQL(std::format("DROP VIEW {}", name));
               break;
            case EEntity_type::table:
               if (boExecute = allTables.find(name) != allTables.end(); boExecute) query.SetSQL(std::format("DROP TABLE {}", name));
               break;
            default:
               throw TMy_RuntimeError("unexpected entity tpye in cleanup");
            }
         if (boExecute) {
            query.Execute();
            std::cerr << query.GetSQL() << std::endl;
            }
         }

      for (auto const& stmt : std::get<col_val(migrate_data_columns::to_create)>(contrl)) {
         query.SetSQL(stmt);
         query.Execute();
         }
      }
   }
   catch (TMy_Db_Exception& ex) {
      HandleException(strMessage, ex);
      }
   catch (std::exception& ex) {
      HandleException(strMessage, ex);
      }

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
            for(auto const& stmt : std::get<col_val(migrate_data_columns::del_stmt)>(contrl)) {
               del_query.SetSQL(stmt);
               del_query.Execute();
               }
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

         // additional statements
         std::wstring strwBuffer;
         for (auto const& line : my_lines<call_with_wstring>{ GetContent<call_with_wstring>(std::get<col_val(migrate_data_columns::additional)>(contrl), strwBuffer) }) {
            if(line.length() > 0) {
               query.SetSQL(line);
               query.Execute();
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
