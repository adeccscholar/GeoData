#include "Processes.h"

#include "MyLocation.h"

TStreamWrapper<Narrow> inline old_cout(std::cout);
TStreamWrapper<Narrow> inline old_cerr(std::cerr);
TStreamWrapper<Narrow> inline old_clog(std::clog);

std::vector<TProcess::country_data> TProcess::Countries {
              { "Brandenburg"s, "Adressen_-_Brandenburg.csv"s, 12},
              { "Berlin"s,      "Adressen_-_Berlin.csv"s, 11 }
              };

std::vector<std::string> TProcess::vecButtons { "btnDisconnect"s, "btnShowCountries"s, 
                                                "btnShowDistrictsBbg"s ,"btnShow"s,
                                                "btnShowBlnDistricts"s,
                                                "btnInsertBbg"s, "btnInsertBln"s, 
                                                "btnInsertTh", "btnInsertAdm"s };

std::vector<tplList<Narrow>> TProcess::Brandenburg_Districts_Columns {
      tplList<Narrow> { "district",      200, EMyAlignmentType::left   },
      tplList<Narrow> { "district town", 200, EMyAlignmentType::left   },
      tplList<Narrow> { "category",      150, EMyAlignmentType::center },
      tplList<Narrow> { "abbr",          100, EMyAlignmentType::center },
      tplList<Narrow> { "country#",        0, EMyAlignmentType::right  },
      tplList<Narrow> { "district#",       0, EMyAlignmentType::right  },
      tplList<Narrow> { "latitude",      130, EMyAlignmentType::right  },
      tplList<Narrow> { "longitude",     130, EMyAlignmentType::right  }
};

std::vector<tplList<Narrow>> TProcess::Brandenburg_District_Township_Columns {
      tplList<Narrow> { "district",     200, EMyAlignmentType::left   },
      tplList<Narrow> { "township",     200, EMyAlignmentType::left   },
      tplList<Narrow> { "city",         200, EMyAlignmentType::left   },
      tplList<Narrow> { "count",        100, EMyAlignmentType::right  }
   };

std::vector<tplList<Narrow>> TProcess::Brandenburg_Cities {
   };

std::vector<tplList<Narrow>> TProcess::Country_Columns {
      tplList<Narrow> { "country",      190, EMyAlignmentType::left   },
      tplList<Narrow> { "kind",         160, EMyAlignmentType::left   },
      tplList<Narrow> { "capital",      170, EMyAlignmentType::left   },
      tplList<Narrow> { "abbr",         110, EMyAlignmentType::center },
      tplList<Narrow> { "latitude",     130, EMyAlignmentType::right  },
      tplList<Narrow> { "longitude",    130, EMyAlignmentType::right  },
      tplList<Narrow> { "code",          90, EMyAlignmentType::right  }
};

std::vector<tplList<Narrow>> TProcess::Administrations_Columns {
      tplList<Narrow> { "owner",        150, EMyAlignmentType::left   },
      tplList<Narrow> { "category",      90, EMyAlignmentType::left   },
      tplList<Narrow> { "key",          190, EMyAlignmentType::left   },
      tplList<Narrow> { "designation",  180, EMyAlignmentType::left   },
      tplList<Narrow> { "street",       180, EMyAlignmentType::left   },
      tplList<Narrow> { "number",        80, EMyAlignmentType::left   },
      tplList<Narrow> { "zipcode",       70, EMyAlignmentType::right  },
      tplList<Narrow> { "city",         180, EMyAlignmentType::left   },
      tplList<Narrow> { "latitude",      80, EMyAlignmentType::right  },
      tplList<Narrow> { "longitude",     80, EMyAlignmentType::right  }
};

std::vector<tplList<Narrow>> TProcess::Berlin_Districts_Columns {
      tplList<Narrow> { "District",     190, EMyAlignmentType::left   },
      tplList<Narrow> { "Abbr.",         60, EMyAlignmentType::left   },
      tplList<Narrow> { "Code",          70, EMyAlignmentType::center },
      tplList<Narrow> { "City hall",    210, EMyAlignmentType::left   },
      tplList<Narrow> { "Zipcode",       70, EMyAlignmentType::left   },
      tplList<Narrow> { "City",         150, EMyAlignmentType::left   },
      tplList<Narrow> { "Street",       180, EMyAlignmentType::left   },
      tplList<Narrow> { "latitude",      80, EMyAlignmentType::right  },
      tplList<Narrow> { "longitude",     80, EMyAlignmentType::right  }
};

std::vector<tplList<Narrow>> TProcess::Berlin_District_Neighborhoods_Columns {
      tplList<Narrow> { "District",     200, EMyAlignmentType::left   },
      tplList<Narrow> { "Abbr.",         80, EMyAlignmentType::left   }, 
      tplList<Narrow> { "Neighborhood", 200, EMyAlignmentType::left   },
      tplList<Narrow> { "state#",        80, EMyAlignmentType::center },
      tplList<Narrow> { "district#",     80, EMyAlignmentType::center },
      tplList<Narrow> { "latitude",      80, EMyAlignmentType::right  },
      tplList<Narrow> { "longitude",     80, EMyAlignmentType::right  }
};

struct TMyNum : public std::numpunct<char> {
   char_type   do_decimal_point() const { return ','; }
   char_type   do_thousands_sep() const { return '.'; }
   string_type do_truename()      const { return "ja"; }
   string_type do_falsename()     const { return "nein"; }
   std::string do_grouping()      const { return "\3"; }
};

TMyNum newNumPunct;
std::locale TProcess::myLoc;

void TProcess::test_function() {
   auto now = std::chrono::system_clock::now();

   // Datum in einen Zeitpunkt umwandeln
   //auto time_point = std::chrono::system_clock::to_time_t(now);
   auto time_point = std::chrono::current_zone()->to_local(now);

   // Zeitpunkt in ein year_month_day-Objekt umwandeln
   auto date = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(now));

   // Wochentag ermitteln
   auto weekday = std::chrono::weekday(date);
   
   std::chrono::year_month_day firstDay { std::chrono::year(2023) / std::chrono::February / std::chrono::day(1) };
   std::chrono::year_month_day lastDay {std::chrono::year(2023) / std::chrono::February / std::chrono::last };

   //std::chrono::month { date };
   date = std::chrono::sys_days { date } + std::chrono::days { 5 };

   // ISO-Kalenderwoche ermitteln
   auto iso_calendar_week = std::chrono::weekday(date).iso_encoding();
   std::cerr << std::format("{:%d.%m.%Y} ", firstDay);
   std::cerr << std::format("{:%d.%m.%Y} ", lastDay);
   std::cerr << std::format("{:%d.%m.%Y %X} ", time_point);
   std::cerr << iso_calendar_week << std::endl;

}


void TProcess::init_mainform(TMyForm&& form) {
   swap(frm, form);
   try {
      std::ios_base::sync_with_stdio(false);
      myLoc = std::locale(std::locale("de_DE"), &newNumPunct);
      std::locale::global(myLoc);

      frm.SetCaption(std::format("application \"{}\" for {} not connected ...", strApplication, concrete_db_server::ServerType()));
      frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", Country_Columns);
      frm.GetAsStream<Narrow, EMyFrameworkType::memo>(old_cerr, "txtError");
      frm.GetAsStream<Narrow, EMyFrameworkType::statusbar>(old_clog, "sbMain");

      frm.Set<EMyFrameworkType::checkbox, std::string>("chbShowMigrate",      "Show Action for Migration");
      frm.Set<EMyFrameworkType::checkbox, bool>       ("chbShowMigrate",      false);
      frm.Set<EMyFrameworkType::button,   std::string>("btnConnect",          "login ...");
      frm.Set<EMyFrameworkType::button,   std::string>("btnDisconnect",       "disconnect");
      frm.Set<EMyFrameworkType::button,   std::string>("btnShowCountries",    "show all countries");
      frm.Set<EMyFrameworkType::button,   std::string>("btnShowBlnDistricts", "show districts for Berlin");
      frm.Set<EMyFrameworkType::button,   std::string>("btnShowDistrictsBbg", "show districts for Brandenburg");
      frm.Set<EMyFrameworkType::button,   std::string>("btnShow",             "show district/township");
      frm.Set<EMyFrameworkType::button,   std::string>("btnInsertBbg",        "migrate Brandenburg"s);
      frm.Set<EMyFrameworkType::button,   std::string>("btnInsertBln",        "migrate Berlin"s);
      frm.Set<EMyFrameworkType::button,   std::string>("btnInsertTh",         "migrate Thuringia"s);
      frm.Set<EMyFrameworkType::button,   std::string>("btnInsertAdm",        "migrate Administrations"s);
      frm.Set<EMyFrameworkType::button,   std::string>("btnTest",             "Test");
      frm.Set<EMyFrameworkType::button,   std::string>("btnClose",            "close");

      frm.Enable<EMyFrameworkType::button>("btnConnect", true);
      for (auto const& btn : vecButtons) frm.Enable<EMyFrameworkType::button>(btn, false);
      }
   catch (std::exception& ex) {
      frm.Message(EMyMessageType::information, std::format("error while prepare application \"{}\"", strApplication), ex.what());
      }
   for (auto& s : { &std::cout, &std::cerr, &std::clog }) {
      s->imbue(myLoc);
      s->setf(std::ios::fixed);
      }
   std::clog << std::format("application \"{}\" is successful started and ready\n", strApplication);
   }


TProcess::login_return TProcess::Login(TMyForm&& form, std::string const& server, bool integrated, std::string const& user) {
   TMyForm dlg;
   swap(dlg, form);
   dlg.SetCaption(server);
   dlg.Set<EMyFrameworkType::groupbox, std::string>("grpUser", "credentials");


   dlg.Set<EMyFrameworkType::edit, std::string>("edtUser", user);
   dlg.Set<EMyFrameworkType::edit, std::string>("edtPassword", "");
   dlg.Set<EMyFrameworkType::label, std::string>("lblUser", "user:");
   dlg.Set<EMyFrameworkType::label, std::string>("lblPassword", "password:");

   dlg.Set< EMyFrameworkType::checkbox, std::string>("chbIntegrated", "use integrated security");
   if(db.HasIntegratedSecurity()) {
      dlg.Visible< EMyFrameworkType::checkbox>("chbIntegrated", true);
      dlg.Set<EMyFrameworkType::checkbox, bool>("chbIntegrated", integrated);
      }
   else {
      dlg.Set<EMyFrameworkType::checkbox, bool>("chbIntegrated", false);
      dlg.Visible< EMyFrameworkType::checkbox>("chbIntegrated", false);
      }

   dlg.Set<EMyFrameworkType::button, std::string>("btnOk", "login");
   dlg.Set<EMyFrameworkType::button, std::string>("btnCancel", "cancel");

   if (dlg.ShowModal() == EMyRetResults::ok) {
      auto boIntegrated = db.HasIntegratedSecurity() ? dlg.Get<EMyFrameworkType::checkbox, bool>("chbIntegrated").value_or(false) : false;
      if (boIntegrated) return { ""s, ""s, boIntegrated };
      else {
         auto strUser = dlg.Get<EMyFrameworkType::edit, std::string>("edtUser");
         auto strPwd = dlg.Get<EMyFrameworkType::edit, std::string>("edtPassword");

         if (strUser) return { *strUser, strPwd.value_or(""s), boIntegrated };
         else throw TMy_InputError("no username was entered in the login dialog.");
         }
      }
   else throw TMy_UserBreak(std::format("the user canceled the login process for the database \"{}\".", db.GetDatabase()));
   }


void TProcess::HandleException(std::string const& theme, TMy_UserBreak const& ex) {
   frm.Message(EMyMessageType::information, theme, ex.what());
   std::clog << ex.what() << "\n";
   }

void TProcess::HandleException(std::string const& theme, std::exception const& ex, src_loc const& loc) {
   auto timepoint = std::chrono::system_clock::now();
   auto const timestamp = std::chrono::current_zone()->to_local(timepoint);
   auto const millis = std::chrono::duration_cast<std::chrono::milliseconds>(timepoint.time_since_epoch()) % 1000;

   std::string position = std::format("\n[error at {:%d.%m.%Y %X},{:03d} in file \"{}\" at line {}]",
      timestamp, millis.count(), loc.file_name(), loc.line());

   frm.Message(EMyMessageType::error, theme, std::format("{}\n\n{}", ex.what(), position));
   std::cerr << std::format("unexpected error while {}\n{}\n{}\n{}.\n",
      theme, db.GetInformations(), ex.what(), position);

   std::clog << std::format("unexpected error while {}.\n", theme);

   }


void TProcess::HandleException(std::string const& theme, TMy_Db_Exception const& ex) {
   frm.Message(EMyMessageType::error, theme, ex.information());
   std::cerr << std::format("error while {}\n{}\n{}.", theme, db.GetInformations(), ex.information()) << std::endl;
   std::clog << std::format("error while {}. {}", theme, ex.what()) << std::endl;
   }

void TProcess::HandleException(std::string const& theme, TMy_InputError const& ex) {
   frm.Message(EMyMessageType::error, theme, ex.what());
   std::clog << std::format("error while {}: {}\n", theme, ex.what());
   }

template <typename ty>
ty CreateTest(void) {
   if constexpr (std::is_same<ty, TMyMSSQL>::value) {
      TMyMSSQL database{ "GeoDaten" };
      return database;
      }
   else if constexpr (std::is_same<ty, TMyMySQL>::value) {
      TMyMySQL database{ "Geodaten", "root", "" };
      return database;
      }
   else if constexpr (std::is_same<ty, TMyOracle>::value) {
      TMyOracle database{ true, "XE.WORLD", "system", "" };
      // TMyOracle database { "localhost", 1521, "XE", "system", "" };
      return database;
      }
   }


void TProcess::connect_to_database(TMyForm&& dlg) {
   std::string strTheme = std::format("connecting to database {} / {}", db.GetDatabase(), db.ServerType());
   TMyWait wait;
   try {
      db = CreateTest<concrete_db_server>();
      auto [usr, pwd, isec] = Login(std::forward<TMyForm>(dlg), strTheme, db.Integrated(), db.User());
      db += TMyCredential { usr, pwd, db.HasIntegratedSecurity() && isec };
    
      db.Open();
      frm.InitCombobox("cbxDistrictsBbg", Districts_Brandenburg());
      frm.SetFirstComboBox("cbxDistrictsBbg");
      std::clog << db.Status() << std::endl;
      for (auto const& btn : vecButtons) frm.Enable<EMyFrameworkType::button>(btn, true);
      frm.Enable<EMyFrameworkType::button>("btnConnect", false);
      frm.SetCaption(std::format("application \"{}\" connected to {} ...", strApplication, db.GetInformations()));
      frm.Message(EMyMessageType::information, strTheme, "Connected successful to "s + db.GetInformations());
      }
   catch (TMy_InputError& ex) {
      HandleException(strTheme, ex);
      }
   catch (TMy_UserBreak& ex) {
      frm.Message(EMyMessageType::warning, strTheme, ex.what());
      std::clog << ex.what() << std::endl;
      }
   catch (TMy_Db_Exception& ex) {
      HandleException(strTheme, ex);
      }
   catch (std::exception& ex) {
      HandleException(strTheme, ex);
      }
   }

void TProcess::disconnect_from_database() {
   frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", Brandenburg_District_Township_Columns, true);
   db.Close();
   frm.SetCaption(std::format("application \"{}\" for {} disconnected from database ...", strApplication, concrete_db_server::ServerType()));
   std::clog << db.Status() << std::endl;
   for (auto const& btn : vecButtons) frm.Enable<EMyFrameworkType::button>(btn, false);
   frm.Enable<EMyFrameworkType::button>("btnConnect", true);
   return;
   }

void TProcess::Action(void) {
   if (choosen_action != nullptr) choosen_action(*this, frm);
   /*
   switch(choosen_list) {
      case show_variants::bdb_districts: std::cerr << "brandenburg districts\n"; break;
      case show_variants::bdb_townships: std::cerr << "brandenburg townships\n"; break;
      }
   */
   }

void TProcess::Changed_Selection() {
   if (choosen_select != nullptr) choosen_select(*this, frm);
   }

std::string TProcess::FormatExecutionTime(std::chrono::system_clock::time_point const& start, bool withMinutes) {
   auto end = std::chrono::system_clock::now();
   double seconds = std::chrono::duration<double, std::milli>{ end - start }.count() / 1000.0;
   if(seconds < 60.0 || !withMinutes) {
      int whole_seconds      = static_cast<int>(seconds);
      int fractional_seconds = static_cast<int>( (seconds - whole_seconds) * 1000);
      return std::format("{:d}.{:03d} sec", whole_seconds, fractional_seconds);
      }
   else {
      int minutes = static_cast<int>(seconds) / 60;
      seconds -= minutes * 60;
      int whole_seconds = static_cast<int>(seconds);
      int fractional_seconds = static_cast<int>((seconds - whole_seconds) * 1000);
      return std::format("{:d}:{:02d},{:03d} sec", minutes, whole_seconds, fractional_seconds);
      }
   }

// *************** Definition für Actions *********************

std::vector<TProcess::show_data> TProcess::ShowData {
   {  "show all data for countries"s,
      "SELECT ID, Land, Abkuerzung, Status, Hauptstadt, Laengengrad, Breitengrad\n"s +
      "FROM Deutschland\n"s +
      "ORDER BY Land"s,
      [](concrete_query& query, TMyForm& frm) {},
      [](concrete_query& query, std::ostream& out) {
         out << *query.Get<std::string>("Land", true) << "\t"
             << *query.Get<std::string>("Status", true) << "\t"
             << *query.Get<std::string>("Hauptstadt", true) << "\t"
             << *query.Get<std::string>("Abkuerzung", true) << "\t"
             << *query.Get<double>("Breitengrad", true) << "\t"
             << *query.Get<double>("Laengengrad", true) << "\t"
             << *query.Get<int>("ID", true) << "\n";
         },
      [](TProcess& proc, TMyForm&) {
         proc.choosen_list = TProcess::show_variants::all_countries;
         },
      [](TProcess& proc, TMyForm&) {
            },
      [](TProcess& proc, TMyForm&) {
            },
      [](TMyForm& frm) {
            frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", Country_Columns, true);
            frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", false);
            return true;
            },
      [](TMyForm& frm) {
            frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", true);
            }
   },
   //--------------------------------------------------------------------------------------------------------
   { "show districts for Berlin"s,
       "SELECT Stadtbezirk,Abkuerzung,Bezirk_ID,Rathaus,Rathaus_PLZ,Rathaus_Ort,Rathaus_Strasse,"s +
              "Rathaus_Nummer,Rathaus_Breite,Rathaus_Laenge\n"s +
       "FROM Berliner_Stadtbezirke"s,
       [](concrete_query& query, TMyForm& frm) {
          },
       [](concrete_query& query, std::ostream& out) {
          auto nummer = query.Get<std::string>("Rathaus_Nummer", true);
          out << *query.Get<std::string>("Stadtbezirk", true) << "\t"
              << *query.Get<std::string>("Abkuerzung") << "\t"
              << *query.Get<int>("Bezirk_ID") << "\t"
              << *query.Get<std::string>("Rathaus") << "\t"
              << *query.Get<std::string>("Rathaus_PLZ") << "\t"
              << *query.Get<std::string>("Rathaus_Ort") << "\t"
              << (*query.Get<std::string>("Rathaus_Strasse") + (nummer ? " "s + *nummer : ""s)) << "\t"
              << *query.Get<double>("Rathaus_Breite", true) << "\t"
              << *query.Get<double>("Rathaus_Laenge", true) << std::endl;
          },
       [](TProcess& proc, TMyForm&) {
             proc.choosen_list = TProcess::show_variants::bln_districts;
             },
       [](TProcess& proc, TMyForm&) {
             },
       [](TProcess& proc, TMyForm& frm) {
             auto rows = frm.GetSelectedRows<EMyFrameworkType::listview>("tblOutput");
             if (rows.size() > 0) {
                auto distr = frm.GetValue<EMyFrameworkType::listview, std::string>("tblOutput", rows[0], 0);
                frm.Message(EMyMessageType::information, "Selected district", distr.value_or("unknown"s));
                }
             },
       [](TMyForm& frm) {
             frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", Berlin_Districts_Columns, true);
             frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", false);
             return true;
             },
       [](TMyForm& frm) {
             frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", true);
             }
   },
   //--------------------------------------------------------------------------------------------------
   {  "Display all districts and independent cities in Brandenburg."s, // theme
      "SELECT Kreis,Kreisstadt,Status,Abkuerzung,Land_ID,Kreis_ID,Breitengrad,Laengengrad\n"s +
      "FROM Brandenburg_Kreise\n"s +
      "ORDER BY Kreis"s, 
      [](concrete_query& query, TMyForm& frm) {
              }, 
      [](concrete_query& query, std::ostream& out) {
              out << *query.Get<std::string>("Kreis", true) << "\t"
                  << query.Get<std::string>("Kreisstadt").value_or("") << "\t"
                  << *query.Get<std::string>("Status", true) << "\t"
                  << query.Get<std::string>("Abkuerzung").value_or(""s) << "\t"
                  << *query.Get<int>        ("Land_ID", true) << "\t"
                  << *query.Get<int>        ("Kreis_ID", true) << "\t"
                  << query.Get<double>("Breitengrad").value_or(0.0) << "\t"
                  << query.Get<double>("Laengengrad").value_or(0.0) << std::endl;
              }, // show
      [](TProcess& proc, TMyForm&) {
              }, // confirm after
      [](TProcess& proc, TMyForm& frm) {
             auto rows = frm.GetSelectedRows<EMyFrameworkType::listview>("tblOutput");
             if (rows.size() > 0) {
                std::optional<int> distr = frm.GetValue<EMyFrameworkType::listview, int>("tblOutput", rows[0], 5);
                frm.Set<EMyFrameworkType::combobox>("cbxDistrictsBbg", distr);
                }
             }, // action for select in list
      [](TProcess& proc, TMyForm&) {
             proc.show(TProcess::show_variants::bdb_townships);
             }, // action for double clicked in list
      [](TMyForm& frm) { 
            frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", Brandenburg_Districts_Columns, true);
            frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", false);
            return true; 
            }, // prepare
      [](TMyForm& frm) {
            frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", true);
            }                
   },
   //-------------------------------------------------------------------------------------------------
   { "show districts and townships for Brandenburg"s,
      "SELECT Kreis, Gemeinde, Ort, Count(*) AS Anzahl\n"s
      "FROM Brandenburg\n"s +
      "WHERE Kreis_ID = :Kreis_ID and Land_ID = :Land_ID\n"s +
      "GROUP BY Kreis, Gemeinde, Ort\n"s +
      "ORDER BY Kreis, Gemeinde, ORT"s,
      [](concrete_query& query, TMyForm& frm) {
         query.Set("Kreis_ID", *frm.Get<EMyFrameworkType::combobox, int>("cbxDistrictsBbg"), true);
         query.Set("Land_ID", 12, true);
         },
      [](concrete_query& query, std::ostream& out) {
         out << *query.Get<std::string>("Kreis") << "\t"
             << *query.Get<std::string>("Gemeinde") << "\t"
             << *query.Get<std::string>("Ort") << "\t"
             << *query.Get<int>("Anzahl", true) << std::endl;
         },
      [](TProcess& proc, TMyForm&) {
         proc.choosen_list = TProcess::show_variants::bdb_townships;
         },
      [](TProcess& proc, TMyForm&) {
         },
      [](TProcess& proc, TMyForm&) {
            },
      [](TMyForm& frm) {
            frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", Brandenburg_District_Township_Columns, true);
            frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", false);
            return true;
            },
      [](TMyForm& frm) {
            frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", true);
            }
   },
   //------------------------------------------------------------------------------------------------------------
   {  "show cities in Brandenburg"s, // theme
      "SELECT Stadt, Stadt_sorbisch, Kreis, Abkuerzung_Kreis, Status, Breite, Laenge, Land_ID, Kreis_ID, Gemeinde_ID,\n"s +
      "       Rathaus, Rathaus_PLZ, Rathaus_Ort, Rathaus_Strasse, Rathaus_Nummer, Rathaus_Breite, Rathaus_Laenge\n"s +
      "FROM Brandenburg_Staedte"s, // query
      [](concrete_query& query, TMyForm& frm) {}, // set for query
      [](concrete_query& query, std::ostream& out) {}, // show
      [](TProcess& proc, TMyForm&) {}, // confirm after
      [](TProcess& proc, TMyForm&) {}, // action for select in list
      [](TProcess& proc, TMyForm&) {}, // action for double clicked in list
      [](TMyForm& frm) { return true; }, // prepare
      [](TMyForm& frm) {}               // finish
   },
   //----------------------------------------------------------------------------------------------------------------
   {  ""s, // theme
      ""s, // query
      [](concrete_query& query, TMyForm& frm) { }, // set for query
      [](concrete_query& query, std::ostream& out) { }, // show
      [](TProcess& proc, TMyForm&) { }, // confirm after
      [](TProcess& proc, TMyForm&) { }, // action for select in list
      [](TProcess& proc, TMyForm&) { }, // action for double clicked in list
      [](TMyForm& frm) { return true; }, // prepare
      [](TMyForm& frm) { }               // finish
   }
   };

/*

*/

void TProcess::call_query(TProcess::show_data const& data) {
   static constexpr auto col_val = [](show_data_columns col) { return static_cast<int>(col); };
   TMyWait wait;
   if(std::get<col_val(show_data_columns::prepare)>(data) == nullptr ? true : std::get<col_val(show_data_columns::prepare)>(data)(frm)) {
      auto start = std::chrono::system_clock::now();
      auto query = db.CreateQuery();
      try {
         query.SetSQL(std::get<col_val(show_data_columns::query)>(data));
         std::get<col_val(show_data_columns::set)>(data)(query, frm);
         query.Execute();
         for (query.First(); query.IsEof(); query.Next()) std::get<col_val(show_data_columns::show)>(data)(query, std::cout);
         if (std::get<col_val(show_data_columns::confirm)>(data)) std::get<col_val(show_data_columns::confirm)>(data)(*this, frm);
         choosen_action = std::get<col_val(show_data_columns::action)>(data);
         choosen_select = std::get<col_val(show_data_columns::select)>(data);
         if (std::get<col_val(show_data_columns::finish)>(data)) std::get<col_val(show_data_columns::finish)>(data)(frm);
         std::clog << std::format("{} in {} ...\n", std::get<col_val(show_data_columns::theme)>(data), FormatExecutionTime(start));
         }
      catch (TMy_Db_Exception& ex) {
         if (std::get<col_val(show_data_columns::finish)>(data)) std::get<col_val(show_data_columns::finish)>(data)(frm);
         HandleException(std::get<col_val(show_data_columns::theme)>(data), ex);
         }
      catch (std::exception& ex) {
         if (std::get<col_val(show_data_columns::finish)>(data)) std::get<col_val(show_data_columns::finish)>(data)(frm);
         HandleException(std::get<col_val(show_data_columns::theme)>(data), ex);
         }
      }
   else {
      ; // generate a message std::get<0>(data)
      }
   }

void TProcess::show(show_variants variant) {
   call_query(ShowData[static_cast<int>(variant)]);
   }

void TProcess::show_bln_districts_database(void) {
   call_query(ShowData[2]);
   }

void TProcess::show_countries_database() {
   //frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", Country_Columns, true);
   call_query(ShowData[0]);
   }
/*
   static std::string strQuery {
         "SELECT ID, Land, Abkuerzung, Status, Hauptstadt, Laengengrad, Breitengrad\n"s
         "FROM Deutschland\n"s
         "ORDER BY Land"};

   TMyWait wait;
   auto start = std::chrono::system_clock::now();
   auto query = db.CreateQuery();
   try {
      query.SetSQL(strQuery);
      frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", Country_Columns, true);
      if (query.Execute()) {
         BeginUpdate("tblOutput");
         for (query.First(); query.IsEof(); query.Next()) {
            std::cout << *query.Get<std::string>("Land", true) << "\t"
                      << *query.Get<std::string>("Status", true) << "\t"
                      << *query.Get<std::string>("Hauptstadt", true) << "\t"
                      << *query.Get<std::string>("Abkuerzung", true) << "\t"
                      << *query.Get<double>("Breitengrad", true) << "\t"
                      << *query.Get<double>("Laengengrad", true) << "\t"
                      << *query.Get<int>("ID", true) << "\n";
            }
         EndUpdate("tblOutput");
         std::clog << std::format("{} in {} ...\n", "show all countries"s, FormatExecutionTime(start));
         }
      }
   catch (TMy_Db_Exception& ex) {
      HandleException("show countries"s, ex);;
      }
   catch (std::exception& ex) {
      HandleException("show countries"s, ex);;
      }
   }
*/


std::vector<tplRepVal> TProcess::Districts_Brandenburg(void) {
   static std::string strQuery { "SELECT DISTINCT Kreis, Kreis_ID\n"s
                                 "FROM Brandenburg\n"s
                                 "ORDER BY Kreis"};
   auto query = db.CreateQuery();
   std::vector<tplRepVal> retval;
   query.SetSQL(strQuery);
   query.Execute();
   for (query.First(); query.IsEof(); query.Next()) {
      auto field = query.Get<std::string>("Kreis");
      auto id = query.Get<int>("Kreis_ID");
      if (!field || !id) {
         throw TMy_Db_Exception("read Districts_Brandenburg", "required field is empty.", db.GetInformations(), strQuery);
         }
      retval.emplace_back(tplRepVal{ *field, *id });
      }
   return retval;
   }


void TProcess::show_bdb_districts_townships_database() {
   //frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", District_Township_Columns, true);
   call_query(ShowData[1]);
   }

/*
   static const std::string strTheme { "show districts and townships for Brandenburg"s };
   static std::string strQuery {
         "SELECT Kreis, Gemeinde, Ort, Count(*) AS Anzahl\n"s
         "FROM Brandenburg\n"s +
         "WHERE Kreis_ID = :Kreis_ID and Land_ID = :Land_ID\n"s +
         "GROUP BY Kreis, Gemeinde, Ort\n"s +
         "ORDER BY Kreis, Gemeinde, ORT"s };
   TMyWait wait;
   auto start = std::chrono::system_clock::now();
   auto query = db.CreateQuery();
   try {
      query.SetSQL(strQuery);

      std::tuple<_val<int>, _val<int>> params;
      std::get<0>(params) = _val<int> { "Kreis_ID"s,* frm.Get<EMyFrameworkType::combobox, int>("cbxDistrictsBbg"), true};
      std::get<1>(params) = _val<int> { "Land_ID"s, 12, true };
      CallSetValue(query, params);
      //query.Set("Kreis_ID", *frm.Get<EMyFrameworkType::combobox, int>("cbxDistrictsBbg"), true);
      //query.Set("Land_ID", 12, true);

      std::clog << strTheme << std::endl;
      frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", District_Township_Columns, true);

      if (query.Execute()) {
         BeginUpdate("tblOutput");
         //size_t cnt = 0;
         for (query.First(); query.IsEof(); query.Next()) {
            std::cout << *query.Get<std::string>("Kreis") << "\t"
                      << *query.Get<std::string>("Gemeinde") << "\t"
                      << *query.Get<std::string>("Ort") << "\t"
                      << *query.Get<int>("Anzahl", true) << std::endl;
            // if (cnt++ / 2000 == 0) refresh();
            }
         EndUpdate("tblOutput");
         std::clog << std::format("{} in {} ...\n", strTheme, FormatExecutionTime(start, true));
         }
      }
   catch (TMy_Db_Exception& ex) {
      HandleException(strTheme, ex);;
      }
   catch (std::exception& ex) {
      HandleException(strTheme, ex);;
      }
   }
*/

std::vector<TProcess::migrate_data> TProcess::MigrationControl {
   // Berliner Rohdaten
   { "inserting data for Berlin"s, "d:\\test\\Adressen_-_Berlin.csv"s, ",",
     "DELETE FROM Berlin"s, 
     "INSERT INTO Berlin (Land_ID, Bezirk_ID, Ortsteil_ID, Strasse_ID, Land, Bezirk, Ortsteil, Strasse, PLZ, HNR, ADZ, Latitude, Longitude)\n"s
     "VALUES(:Land_ID, :Bezirk_ID, :Ortsteil_ID, :Strasse_ID, :Land, :Bezirk, :Ortsteil, :Strasse, :PLZ, :HNR, :ADZ, :Latitude, :Longitude)"s,
     [](concrete_query& query, std::vector<std::string_view> const& data) {
         query.Set("Land_ID", 11);
         query.Set("Bezirk_ID", string_to_int<int>(data[10]));
         query.Set("Ortsteil_ID", string_to_int<int>(data[12]));
         query.Set("Strasse_ID", string_to_int<int>(data[6]));
         query.Set("Land", data[21]);
         query.Set("Bezirk", data[9]);
         query.Set("Ortsteil", data[11]);
         query.Set("Strasse", data[7]);
         query.Set("PLZ", data[8]);
         query.Set("HNR", string_to_int<int>(data[4]));
         query.Set("ADZ", data[5]);
         myMercatorETRS89<double> loc { string_to_float<double>(data[0]), string_to_float<double>(data[1]) };
         auto position = Location<double>::ConvertMercatorETRS89ToWGS84(loc);
         query.Set("Latitude", position.first);
         query.Set("Longitude", position.second);
         return true;
         }
    },
   // Brandenburger Rohdaten
   {  "inserting data for Brandenburg"s, "d:\\test\\Adressen_-_Brandenburg.csv"s, ",",
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
   // zusätzliche Daten zur Verwaltungen
   { "inserting data for administrations"s, "d:\\test\\Verwaltungen.txt"s, ";",
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
   { "inserting keys for Thüringen"s, "d:\\test\\schluessel-th.txt"s, ";",
     "DELETE FROM Thueringen_Schluessel"s,
     "INSERT INTO Thueringen_Schluessel (Satzart, Land_ID, Region_ID, Kreis_ID, Gemeinde_ID, Ortsteil_ID, Bezeichnung)\n"s +
     "VALUES(:Satzart, :Land_ID, :Region_ID, :Kreis_ID, :Gemeinde_ID, :Ortsteil_ID, :Bezeichnung)"s,
   [](concrete_query& query, std::vector<std::string_view> const& data) {
         static std::optional<int> null_value = { };   // concept
         //static int null_value = 0;
         switch(data[0][0]) {
         case 'L':
            query.Set("Satzart", "Land");
            query.Set("Land_ID", std::make_optional(string_to_int<int>(data[1])));
            query.Set("Region_ID",   null_value);
            query.Set("Kreis_ID",    null_value);
            query.Set("Gemeinde_ID", null_value);
            query.Set("Ortsteil_ID", null_value);
            query.Set("Bezeichnung", data[2]);
            break;
         case 'R': return false;
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
            query.Set("Land_ID", string_to_int<int>(data[1]));
            query.Set("Region_ID", string_to_int<int>(data[2]));
            query.Set("Kreis_ID",    string_to_int<int>(data[3]));
            query.Set("Gemeinde_ID", string_to_int<int>(data[4]));
            query.Set("Ortsteil_ID", null_value);
            query.Set("Bezeichnung", data[5]);
            break;
         default:
            throw TMy_RuntimeError("Unexpected Content for Data: "s + std::string { data[0].begin(), data[0].end() } );
         }
         return true;
      }
   },
   {  "inserting data for Thüringen"s, "d:\\test\\Adressen_-_Thueringen.csv"s, ",",
      "DELETE FROM Thueringen"s,
      "INSERT INTO Thueringen (Land_ID,Region_ID,Kreis_ID,Gemeinde_ID,Ortsteil_ID,Strasse_ID,Strasse,HNR,ADZ,PLZ,Laengengrad,Breitengrad)\n"s +
      "VALUES(:Land_ID,:Region_ID,:Kreis_ID,:Gemeinde_ID,:Ortsteil_ID,:Strasse_ID,:Strasse,:HNR,:ADZ,:PLZ,:Laengengrad,:Breitengrad)"s,
      [](concrete_query& query, std::vector<std::string_view> const& data) {
         query.Set("Land_ID", string_to_int<int>(data[6]));
         query.Set("Region_ID", string_to_int<int>(data[7]));
         query.Set("Kreis_ID", string_to_int<int>(data[8]));
         query.Set("Gemeinde_ID", string_to_int<int>(data[9]));
         query.Set("Ortsteil_ID", string_to_int<int>(data[10]));
         query.Set("Strasse_ID", string_to_int<int>(data[11]));
         query.Set("Strasse", data[16]);
         query.Set("HNR",  string_to_int<int>(data[12]));
         query.Set("ADZ", data[13]);
         query.Set("PLZ", "");
         myMercatorETRS89<double> loc { string_to_float<double>(data[0]), string_to_float<double>(data[1]) };
         auto position = Location<double>::ConvertMercatorETRS89ToWGS84(loc);
         query.Set("Laengengrad", position.first);
         query.Set("Breitengrad", position.second);
         return true;
         }
   }
};


void TProcess::insert_into_database(std::vector<migrate_variants> kinds) {
   std::string strBuffer;
   bool boDeleteBeforeInsert = false;
   std::string strMessage = ""s;
   std::ostringstream os;
   for (size_t i { 0 };  auto const& kind : kinds) {
      TProcess::migrate_data const& contrl = MigrationControl[static_cast<int>(kind)];
      os << (i++ > 0 ? "\n" : "") << std::get<0>(contrl);
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
         strMessage = std::get<0>(contrl);
         if(boDeleteBeforeInsert == true) {
            auto del_query = db.CreateQuery();
            del_query.SetSQL(std::get<3>(contrl));
            del_query.Execute();
            }

         auto start = std::chrono::system_clock::now();
         auto query = db.CreateQuery();
         query.SetSQL(std::get<4>(contrl));
         std::cerr << std::format("{}: {} started ...\n", get_current_time_and_date(), std::get<0>(contrl));
         std::clog << std::get<0>(contrl) << std::endl;
         TMyForm::ProcessEvents();
         int linecnt = 0;
         for ( auto const& line : my_lines{ GetContent(std::get<1>(contrl), strBuffer) }) {
            auto test = std::string_view{ line.begin(), line.end() } | std::views::split(std::get<2>(contrl))
                          | std::views::transform([](auto d) { return std::string_view{ d.begin(), d.end() }; })
                          | std::ranges::to<std::vector>();

            if(std::get<5>(contrl)(query, test)) query.Execute();
            if (++linecnt % 50000 == 0) {
               std::clog << std::get<0>(contrl) << " -> " << linecnt << " rows inserted" << std::endl;
               TMyForm::ProcessEvents();
               }
            }
         std::string strEndMessage = std::format("{}, {} rows inserted in {}\n", std::get<0>(contrl), linecnt, FormatExecutionTime(start));
         std::cerr << std::format("{}: {}", get_current_time_and_date(), strEndMessage);
         std::clog << strEndMessage;
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

/*
void TProcess::insert_berlin_into_database() {
   static auto to_string = [](std::string_view const& val) { return std::string { val.begin(), val.end() }; };

   std::string strBuffer;
   static const std::string strTheme { "inserting data for Berlin"s };
   static constexpr std::string_view delim{ "," };
   static std::string strQueryDelete { "DELETE FROM Berlin" };
   static std::string strQueryInsert {
      "INSERT INTO Berlin (Land_ID, Bezirk_ID, Ortsteil_ID, Strasse_ID, Land, Bezirk, Ortsteil, Strasse, PLZ, HNR, ADZ, Latitude, Longitude)\n"s
         "VALUES(:Land_ID, :Bezirk_ID, :Ortsteil_ID, :Strasse_ID, :Land, :Bezirk, :Ortsteil, :Strasse, :PLZ, :HNR, :ADZ, :Latitude, :Longitude)" };      

   try {
      switch (auto ret = frm.Message(EMyMessageType::question, strTheme, "Want you delete the existing data?"); ret) {
         case EMyRetResults::ok:
            {
            auto del_query = db.CreateQuery();
            del_query.SetSQL(strQueryDelete);
            del_query.Execute();
            }
            break;
         case EMyRetResults::no: break;
         case EMyRetResults::cancel: throw TMy_UserBreak(strTheme + " canceled by user.");
         default: throw TMy_RuntimeError(strTheme + ", unexpected answer for Message for delete existig data.");
         }

      TMyWait wait;
      auto start = std::chrono::system_clock::now();
      auto query = db.CreateQuery();
      query.SetSQL(strQueryInsert);
      std::cerr << std::format("{}: {} started ...\n", get_current_time_and_date(), strTheme);
      std::clog << strTheme << std::endl;
      TMyForm::ProcessEvents();
      for (int linecnt = 0; auto const& line : my_lines{ GetContent("d:\\test\\Adressen_-_Berlin.csv", strBuffer) }) {
         auto test = std::string_view{ line.begin(), line.end() } | std::views::split(delim)
                        | std::views::transform([](auto d) { return std::string_view{ d.begin(), d.end() }; })
                        | std::ranges::to<std::vector>();

         query.Set("Land_ID",     11);
         query.Set("Bezirk_ID",   string_to_int<int>(test[10]));
         query.Set("Ortsteil_ID", string_to_int<int>(test[12]));
         query.Set("Strasse_ID",  string_to_int<int>(test[6]));
         query.Set("Land",        to_string(test[21]));
         query.Set("Bezirk",      to_string(test[9]));
         query.Set("Ortsteil",    to_string(test[11]));
         query.Set("Strasse",     to_string(test[7]));
         query.Set("PLZ",         to_string(test[8]));
         query.Set("HNR",         string_to_int<int>(test[4]));
         query.Set("ADZ",         to_string(test[5]));

         myMercatorETRS89<double> loc { string_to_float<double>(test[0]),
                                        string_to_float<double>(test[1]) };
         auto position = Location<double>::ConvertMercatorETRS89ToWGS84(loc);
         query.Set("Latitude", position.first);
         query.Set("Longitude", position.second);

         query.Execute();
         if (++linecnt % 50000 == 0) {
            std::clog << strTheme << " -> " << linecnt << " rows inserted" << std::endl;
            TMyForm::ProcessEvents();
            }
         }

      std::string strMessage = std::format("{}, done in {}\\n", strTheme, FormatExecutionTime(start));
      std::cerr << std::format("{}: {}\n", get_current_time_and_date(), strMessage);
      std::clog << strMessage;

      std::cerr << get_current_time_and_date() << ": " << strTheme << " finished.\n";
      }
   catch (TMy_Db_Exception& ex) {
      HandleException("inserting data for Berlin"s, ex);;
      }
   catch (std::exception& ex) {
      HandleException("inserting data for Berlin"s, ex);;
      }
   }
*/

/*
void TProcess::insert_brandenburg_into_database() {
   std::string strBuffer;
   static const std::string strTheme { "inserting data for Brandenburg"s };
   static constexpr std::string_view delim{ "," };
   static std::string strQueryDelete { "DELETE FROM Brandenburg" };
   static std::string strQueryInsert {
      "INSERT INTO Brandenburg (Land_ID, Region_ID,Kreis_ID,Gemeinde_ID,Ortsteil_ID,Strasse_ID,\n"
      "                         HNR,ADZ,Land,Kreis,Amt,Gemeinde,Ort,Strasse,PLZ,Latitude,Longitude)\n"
      "VALUES (:Land_ID, :Region_ID, :Kreis_ID, :Gemeinde_ID, :Ortsteil_ID, :Strasse_ID,\n"
      "        :HNR, :ADZ, :Land, :Kreis, :Amt, :Gemeinde, :Ort, :Strasse, :PLZ, :X, :Y)" };

   try {
      switch(auto ret = frm.Message(EMyMessageType::question, strTheme, "Want you delete the existing data?");ret) {
         case EMyRetResults::ok:
            {
            auto del_query = db.CreateQuery();
            del_query.SetSQL(strQueryDelete);
            del_query.Execute();
            }
            break;
         case EMyRetResults::no: break;
         case EMyRetResults::cancel: throw TMy_UserBreak(strTheme + " canceled by user.");
         default: throw TMy_RuntimeError(strTheme + ", unexpected answer for Message for delete existig data.");

         }

      TMyWait wait;
      auto start = std::chrono::system_clock::now();
      auto query = db.CreateQuery();
      query.SetSQL(strQueryInsert);
      std::cerr << std::format("{}: {} started ...\n", get_current_time_and_date(), strTheme);
      std::clog << strTheme << std::endl;
      TMyForm::ProcessEvents();
      for (int linecnt = 0; auto const& line : my_lines{ GetContent("d:\\test\\Adressen_-_Brandenburg.csv", strBuffer) }) {
         auto test = std::string_view{ line.begin(), line.end() } | std::views::split(delim)
            | std::views::transform([](auto d) { return std::string_view{ d.begin(), d.end() }; })
            | std::ranges::to<std::vector>();

         query.Set("Land_ID", string_to_int<int>(test[5]));
         query.Set("Region_ID", string_to_int<int>(test[6]));
         query.Set("Kreis_ID", string_to_int<int>(test[7]));
         query.Set("Gemeinde_ID", string_to_int<int>(test[8]));
         query.Set("Ortsteil_ID", string_to_int<int>(test[9]));
         query.Set("Strasse_ID", string_to_int<int>(test[10]));
         query.Set("HNR", string_to_int<int>(test[13]));
         query.Set("ADZ", std::string{ test[14].begin(), test[14].end() });
         query.Set("Land", std::string{ test[16].begin(), test[16].end() });
         query.Set("Kreis", std::string{ test[17].begin(), test[17].end() });
         query.Set("Amt", std::string{ test[18].begin(), test[18].end() });
         query.Set("Gemeinde", std::string{ test[19].begin(), test[19].end() });
         query.Set("Ort", std::string{ test[20].begin(), test[20].end() });
         query.Set("Strasse", std::string{ test[21].begin(), test[21].end() });
         query.Set("PLZ", std::string{ test[22].begin(), test[22].end() });

         myMercatorETRS89<double> loc { string_to_float<double>(test[0]),
                                        string_to_float<double>(test[1]) };
         auto position = Location<double>::ConvertMercatorETRS89ToWGS84(loc);
         query.Set("X", position.first);
         query.Set("Y", position.second);

         query.Execute();
         if (++linecnt % 50000 == 0) {
            std::clog << strTheme << " -> " << linecnt << " rows inserted" << std::endl;
            TMyForm::ProcessEvents();
            }
         }

      std::string strMessage = std::format("{}, done in {}\\n", strTheme, FormatExecutionTime(start));
      std::cerr << std::format("{}: {}\n", get_current_time_and_date(), strMessage );
      std::clog << strMessage;
      
      std::cerr << get_current_time_and_date() << ": " << strTheme << " finished.\n";
      }
   catch(TMy_UserBreak& ex) {
      HandleException(strTheme, ex);
      }
   catch (TMy_Db_Exception& ex) {
      HandleException(strTheme, ex);
      }
   catch (std::exception& ex) {
      HandleException(strTheme, ex);
      }
   }
*/

/*
void TProcess::insert_administrations_into_database() {
   std::string strBuffer;
   static const std::string strTheme { "inserting data for administrations"s };
   static constexpr std::string_view delim{ ";" };
   std::string strQueryDelete { "DELETE FROM Verwaltungen"s };
   std::string strQuery { "INSERT INTO Verwaltungen (Schluessel,Kategorie,Bezug,Bezeichnung,"s
                                                    "Strasse, Strasse_Nummer, PLZ, Stadt,"s
                                                    "Breitengrad, Laengengrad)\n"s
                          "VALUES(:Schluessel,:Kategorie,:Bezug,:Bezeichnung,:Strasse,"s
                                 ":Strasse_Nummer,:PLZ,:Stadt,:Breitengrad,:Laengengrad)"s };

   try {
      switch (auto ret = frm.Message(EMyMessageType::question, strTheme, "Want you delete the existing data?"); ret) {
         case EMyRetResults::ok:
            {
            auto del_query = db.CreateQuery();
            del_query.SetSQL(strQueryDelete);
            del_query.Execute();
            }
            break;
         case EMyRetResults::no: break;
         case EMyRetResults::cancel: throw TMy_UserBreak(strTheme + " canceled by user.");
         default: throw TMy_RuntimeError(strTheme + ", unexpected answer for Message for delete existig data.");
         }
      TMyWait wait;
      frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", Administrations_Columns, true);
      auto start = std::chrono::system_clock::now();
      auto query = db.CreateQuery();
      query.SetSQL(strQuery);
      std::cerr << std::format("{}: {} started ...\n", get_current_time_and_date(), strTheme);
      std::clog << strTheme << std::endl;
      TMyForm::ProcessEvents();
      static auto to_string = [](std::string_view const& val) { return std::string { val.begin(), val.end() }; };
      for (int linecnt = 0; auto const& line : my_lines{ GetContent("d:\\test\\Verwaltungen.txt", strBuffer) }) {
         auto test = std::string_view{ line.begin(), line.end() } | std::views::split(delim)
            | std::views::transform([](auto d) { return std::string_view{ d.begin(), d.end() }; })
            | std::ranges::to<std::vector>();

         if(test.size() != 10) {
            std::ostringstream os;
            os << "corrupted data found: "s
               << to_string(test[0]) << " / "
               << std::string{ test[1].begin(), test[1].end() } << " / "
               << std::string{ test[2].begin(), test[2].end() } << ".\n";
            throw std::runtime_error(os.str());
            }

         query.Set("Schluessel",     to_string(test[0]));
         query.Set("Kategorie",      to_string(test[1]));
         query.Set("Bezug",          to_string(test[2]));
         query.Set("Bezeichnung",    to_string(test[3]));
         query.Set("Strasse",        to_string(test[4]));
         query.Set("Strasse_Nummer", to_string(test[5]));
         query.Set("PLZ",            to_string(test[6]));
         query.Set("Stadt",          to_string(test[7]));
         query.Set("Breitengrad",    string_to_float<double>(test[8]));
         query.Set("Laengengrad",    string_to_float<double>(test[9]));

         query.Execute();

         std::cout << to_string(test[0]) << '\t'
                   << std::string{ test[1].begin(), test[1].end() } << '\t'
                   << std::string{ test[2].begin(), test[2].end() } << '\t'
                   << std::string{ test[3].begin(), test[3].end() } << '\t'
                   << std::string{ test[4].begin(), test[4].end() } << '\t'
                   << std::string{ test[5].begin(), test[5].end() } << '\t'
                   << std::string{ test[6].begin(), test[6].end() } << '\t'
                   << std::string{ test[7].begin(), test[7].end() } << '\t'
                   << string_to_float<double>(test[8]) << '\t'
                   << string_to_float<double>(test[9]) << '\n';

         }
      std::string strMessage = std::format("{}, done in {}\\n", strTheme, FormatExecutionTime(start));
      std::cerr << std::format("{}: {}\n", get_current_time_and_date(), strMessage);
      std::clog << strMessage;

      std::cerr << get_current_time_and_date() << ": " << strTheme << " finished.\n";
      }
   catch (TMy_UserBreak& ex) {
      HandleException(strTheme, ex);
      }
   catch (TMy_Db_Exception& ex) {
      HandleException(strTheme, ex);
      }
   catch (std::exception& ex) {
      HandleException(strTheme, ex);
      }
   }
*/
