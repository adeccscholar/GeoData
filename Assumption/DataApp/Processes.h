#pragma once

#include "MyDatabase.h"

#include "MyFileIterator.h"
#include "MyConvert.h"
#include "MyHelper.h"

#include <adecc_Scholar/MyForm.h>
#include <adecc_Scholar/MyStream.h>

#include <iostream>
#include <tuple>
#include <string>
#include <stack>
#include <string_view>
#include <ranges>
#include <format>
#include <chrono>



class TProcess {
public:
   // Einstellungen für das konkrete Programm
   using concrete_db_server     = TMyMSSQL; // TMyMSSQL TMyMySQL TMyOracle TMyInterbase
   using concrete_framework     = TMyQtDb<concrete_db_server>;   // Möglichkeit, define zu nutzen
   using concrete_db_connection = TMyDatabase<TMyQtDb, concrete_db_server>;
   using concrete_query         = TMyQuery<TMyQtDb, concrete_db_server>;

   using control_data = std::tuple<std::string, std::vector<tplList<Narrow>>, std::function <void(std::ostream&, concrete_query const&)>>;

   enum class migrate_data_columns : int { theme = 0, base_table, input_file, delimiter, del_stmt, ins_stmt, set };
   using migrate_data = std::tuple </*  0 */ std::string,        // theme
                                    /*  1 */ std::string,        // table to check
                                    /*  2 */ std::string,        // input file
                                    /*  3 */ std::string_view,   // delimiter for file
                                    /*  4 */ std::string,        // statement for delete
                                    /*  5 */ std::string,        // statement for insert
                                    /*  6 */ std::function <bool(concrete_query&, std::vector<std::string_view> const&)>>;
   using myCaption  = tplList<Narrow>;
   using myCaptions = std::vector<myCaption>;
   enum class show_data_columns : int { theme = 0, query, set, columns, show, confirm, select, 
                                        action, prepare, finish  };
   using show_data    = std::tuple</* 0 */ std::string,                                            // theme
                                   /* 1 */ std::string,                                            // query
                                   /* 2 */ std::function <my_db_params (TProcess&, TMyForm&)>,     // set params
                                   /* 3 */ myCaptions,                                             // Columns
                                   /* 4 */ std::function <void(concrete_query&, std::ostream&)>,   // show in stream
                                   /* 5 */ std::function <void (TProcess&, TMyForm&)>,             // confirm to process
                                   /* 6 */ std::function <void(TProcess&, TMyForm&)>,              // select function
                                   /* 7 */ std::function <void(TProcess&, TMyForm&)>,              // action function
                                   /* 8 */ std::function <bool(TMyForm&, myCaptions const&)>,      // prepare, check
                                   /* 9 */ std::function <void(TMyForm&)>>;                        // finish

   enum class show_variants : int {
      all_countries = 0,
      bln_districts,
      bdb_districts, bdb_townships, bdb_cities,
      blank = 98, undefined = 99
      };

   using show_history = std::stack<std::pair<show_variants, my_db_params>>;
   using show_countries = std::map<std::string, std::tuple<show_variants>>;

   enum class migrate_variants : int {
      bln_opendata     = 0,
      bdb_opendata,    
      administrations,
      th_opendata_keys, 
      th_opendata,
      sn_opendata_keys,
      sn_opendata,
      undefined = 99
      };
   using login_return = std::tuple<std::string, std::string, bool>;
   
   static show_countries               ShowCountries;
   static std::vector<tplList<Narrow>> Administrations_Columns;

   /*
   static std::vector<tplList<Narrow>> Country_Columns;
   static std::vector<tplList<Narrow>> Berlin_Districts_Columns;
   static std::vector<tplList<Narrow>> Berlin_District_Neighborhoods_Columns;
   static std::vector<tplList<Narrow>> Brandenburg_Districts_Columns;
   static std::vector<tplList<Narrow>> Brandenburg_District_Township_Columns;
   static std::vector<tplList<Narrow>> Brandenburg_Cities;
   */
   static inline TStreamWrapper<Narrow> old_cout { std::cout };
   static inline TStreamWrapper<Narrow> old_cerr { std::cerr };
   static inline TStreamWrapper<Narrow> old_clog { std::clog };

private:
   static std::vector<std::string> vecButtons;

   static std::vector<migrate_data> MigrationControl;
   static std::map<show_variants, show_data>    ShowData;

   show_history history;
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
   
   
   //void insert_berlin_into_database();                 // alt
   //void insert_brandenburg_into_database();            // ALT
   //void insert_administrations_into_database();        // ALT
   
   void print_migrate_Berlin(std::ostream& out);
   void migrate_neues_Model(void);

   void show_countries_database(void);                 // ALT
   void show_bln_districts_database(void);             // ALT
   void show_bdb_districts_townships_database(void);   // ALT

   void show(show_variants variant, bool boHistory = true, my_db_params const& = {});
   void clear_history();
   void show_last();
   void show_precursor();

   std::vector<tplRepVal> Districts_Brandenburg(void);

   void Action();
   void Changed_Selection();

   void test_function(void); // Methode für Test
private:
   myCaptions const& get_columns(show_variants variant);

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
