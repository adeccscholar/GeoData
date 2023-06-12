#pragma once

#include <adecc_Scholar/MyForm.h>
#include <adecc_Scholar/MyStream.h>

#include "MyDatabase.h"

#include "MyFileIterator.h"
#include "MyConvert.h"
#include "MyHelper.h"

#include <tuple>
#include <string>
#include <string_view>
#include <ranges>
#include <format>
#include <chrono>



class TProcess {
public:
   // Einstellungen für das konkrete Programm
   using concrete_db_server     = TMyMSSQL; // TMyMSSQL TMyMySQL TMyOracle
   using concrete_framework     = TMyQtDb<concrete_db_server>;   // Möglichkeit, define zu nutzen
   using concrete_db_connection = TMyDatabase<TMyQtDb, concrete_db_server>;
   using concrete_query         = TMyQuery<TMyQtDb, concrete_db_server>;

   using control_data = std::tuple<std::string, std::vector<tplList<Narrow>>, std::function <void(std::ostream&, concrete_query const&)>>;

   enum class migrate_data_columns : int { theme = 0, input_file, delimiter, del_stmt, ins_stmt, set };
   using migrate_data = std::tuple </*  0 */ std::string,        // theme
                                    /*  1 */ std::string,        // input file
                                    /*  2 */ std::string_view,   // delimiter for file
                                    /*  3 */ std::string,        // statement for delete
                                    /*  4 */ std::string,        // statement for insert
                                    /*  5 */ std::function <bool(concrete_query&, std::vector<std::string_view> const&)>>;
   
   enum class show_data_columns : int { theme = 0, query = 1, set = 2, show = 3, confirm = 4, select = 5, 
                                        action = 6, prepare = 7, finish = 8  };
   using show_data    = std::tuple</* 0 */ std::string,             // theme
                                   /* 1 */ std::string,             // query
                                   /* 2 */ std::function <void(concrete_query&, TMyForm&)>,        // set params
                                   /* 3 */ std::function <void(concrete_query&, std::ostream&)>,   // show in stream
                                   /* 4 */ std::function <void (TProcess&, TMyForm&)>,             // confirm to process
                                   /* 5 */ std::function <void(TProcess&, TMyForm&)>,              // select function
                                   /* 6 */ std::function <void(TProcess&, TMyForm&)>,              // action function
                                   /* 7 */ std::function <bool(TMyForm&)>,                         // prepare, check
                                   /* 8 */ std::function <void(TMyForm&)>>;                        // finish

   enum class show_variants : int {
      all_countries = 0,
      bln_districts,
      bdb_districts, bdb_townships, bdb_cities,
      undefined = 99
      };

   enum class migrate_variants : int {
      bln_opendata     = 0,
      bdb_opendata,    
      administrations,
      th_opendata_keys, 
      th_opendata,
      undefined = 99
      };
   using login_return = std::tuple<std::string, std::string, bool>;
   using country_data = std::tuple<std::string, std::string, int>;

   static std::vector<tplList<Narrow>> Country_Columns;
   static std::vector<tplList<Narrow>> Administrations_Columns;
   static std::vector<tplList<Narrow>> Berlin_Districts_Columns;
   static std::vector<tplList<Narrow>> Berlin_District_Neighborhoods_Columns;
   static std::vector<tplList<Narrow>> Brandenburg_Districts_Columns;
   static std::vector<tplList<Narrow>> Brandenburg_District_Township_Columns;
   static std::vector<tplList<Narrow>> Brandenburg_Cities;

private:
   static std::vector<std::string> vecButtons;

   static std::vector<migrate_data> MigrationControl;
   static std::vector<show_data>    ShowData;
   static std::vector<country_data> Countries;
   static inline std::string strApplication = "DataApp"s;
   TMyForm frm;
   static std::locale myLoc;
   concrete_db_connection db{ };

   show_variants choosen_list                               = show_variants::undefined;
   std::function <void(TProcess&, TMyForm&)> choosen_action = nullptr;
   std::function <void(TProcess&, TMyForm&)> choosen_select = nullptr;
public:
   TProcess() = default;
   TProcess(TProcess const&) = delete;

   void init_mainform(TMyForm&& form);
   login_return Login(TMyForm&& dlg, std::string const& server, bool integrated, std::string const& user = "");

   void disconnect_from_database();
   void connect_to_database(TMyForm&&);

   // blindes Einfügen
   void insert_into_database(std::vector<migrate_variants> kinds);
   //void insert_berlin_into_database();
   //void insert_brandenburg_into_database();
   //void insert_administrations_into_database();
   
   void show_countries_database(void);
   void show_bln_districts_database(void);
   void show_bdb_districts_townships_database(void);

   void show(show_variants variant);

   std::vector<tplRepVal> Districts_Brandenburg(void);

   void Action();
   void Changed_Selection();

   void test_function(void); // Methode für Test
private:
   void call_query(show_data const& data);

   void HandleException(std::string const& theme, std::exception const& ex, src_loc const& loc = src_loc::current());
   void HandleException(std::string const& theme, TMy_InputError const& ex);
   void HandleException(std::string const& theme, TMy_UserBreak const& ex);
   void HandleException(std::string const& theme, TMy_Db_Exception const& ex);

   void BeginUpdate(std::string const& component = "tblOutput"s) {
      this->frm.EnableUpdates<EMyFrameworkType::listview>(component, false);
      }

   void Refresh(std::string const& component = "tblOutput"s) {
      frm.EnableUpdates<EMyFrameworkType::listview>(component, true);
      TMyForm::ProcessEvents();
      frm.EnableUpdates<EMyFrameworkType::listview>(component, false);
      }

   void EndUpdate(std::string const& component = "tblOutput"s) {
      frm.EnableUpdates<EMyFrameworkType::listview>(component, true);
      }

   std::string FormatExecutionTime(std::chrono::system_clock::time_point const& start, bool withMinutes = true);
};
