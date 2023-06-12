#include "Processes.h"

#include "MyLocation.h"



std::vector<std::string> TProcess::vecButtons { "btnDisconnect"s,  
                                                "btnShowCountries"s, 
                                                "btnShowDistrictsBbg"s ,"btnShow"s,
                                                "btnShowBlnDistricts"s,
                                                "btnInsertBbg"s, "btnInsertBln"s, 
                                                "btnInsertTh", "btnInsertSn", 
                                                "btnInsertAdm"s,
                                                "btnMigrateBln"s };


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
   /*
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
   */
   double x = 15;
   x = x * std::numbers::pi_v<double> / 180.0;
   std::cerr << x << std::endl;
   double y = 2.699;
   double r = y / std::tan(x);
   std::cerr << r << std::endl;
}


void TProcess::init_mainform(TMyForm&& form) {
   swap(frm, form);
   try {
      std::ios_base::sync_with_stdio(false);
      myLoc = std::locale(std::locale("de_DE"), &newNumPunct);
      std::locale::global(myLoc);

      frm.SetCaption(std::format("application \"{}\" for {} not connected ...", strApplication, concrete_db_server::ServerType()));
      frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", get_columns(show_variants::all_countries));
      frm.GetAsStream<Narrow, EMyFrameworkType::memo>(old_cerr, "txtError");
      frm.GetAsStream<Narrow, EMyFrameworkType::statusbar>(old_clog, "sbMain");

      frm.Set<EMyFrameworkType::checkbox, std::string>("chbShowMigrate"s,      "Show Action for Migration");
      frm.Set<EMyFrameworkType::checkbox, bool>       ("chbShowMigrate"s,      false);
      frm.Set<EMyFrameworkType::button,   std::string>("btnConnect"s,          "login ...");
      frm.Set<EMyFrameworkType::button,   std::string>("btnDisconnect"s,       "disconnect");
      frm.Set<EMyFrameworkType::button,   std::string>("btnBack"s,             "letzte Aktion");
      frm.Set<EMyFrameworkType::button,   std::string>("btnShowCountries"s,    "show all countries");
      frm.Set<EMyFrameworkType::button,   std::string>("btnShowBlnDistricts"s, "show districts for Berlin");
      frm.Set<EMyFrameworkType::button,   std::string>("btnShowDistrictsBbg"s, "show districts for Brandenburg");
      frm.Set<EMyFrameworkType::button,   std::string>("btnShow"s,             "show district/township");
      frm.Set<EMyFrameworkType::button,   std::string>("btnInsertBbg"s,        "migrate Brandenburg"s);
      frm.Set<EMyFrameworkType::button,   std::string>("btnInsertBln"s,        "migrate Berlin"s);
      frm.Set<EMyFrameworkType::button,   std::string>("btnInsertTh"s,         "migrate Thuringia"s);
      frm.Set<EMyFrameworkType::button,   std::string>("btnInsertSn"s,         "migrate Saxony"s);
      frm.Set<EMyFrameworkType::button,   std::string>("btnInsertAdm"s,        "migrate Administrations"s);
      frm.Set<EMyFrameworkType::button,   std::string>("btnMigrateBln"s,       "new Model for Berlin"s);
      frm.Set<EMyFrameworkType::button,   std::string>("btnTest"s,             "Test");
      frm.Set<EMyFrameworkType::button,   std::string>("btnClose"s,            "close");

      frm.Enable<EMyFrameworkType::button>("btnConnect"s, true);
      frm.Enable<EMyFrameworkType::button>("btnBack"s, false);

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

template <my_db_credentials ty>
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
   else if constexpr (std::is_same<ty, TMyInterbase>::value) {
      TMyInterbase database{ "d:\\test\\Datenbank\\GEODATEN.GDB", "sysdba", "" };
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

      for (auto const& view : db.GetViewNames("")) {
         std::cerr << view << std::endl;
         }

      for(auto const& table : db.GetTableNames("")) {
         std::cerr << table << std::endl;
         }
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
   frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", get_columns(show_variants::bdb_townships), true);
   db.Close();
   clear_history();
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





void TProcess::show_bln_districts_database(void) {
   //call_query(ShowData[2], {});
   }

void TProcess::show_countries_database() {
 
   static std::string strQuery {
         "SELECT ID, Land, Abkuerzung, Status, Hauptstadt, Laengengrad, Breitengrad\n"s
         "FROM Deutschland\n"s
         "ORDER BY Land"};

   TMyWait wait;
   auto start = std::chrono::system_clock::now();
   auto query = db.CreateQuery();
   try {
      query.SetSQL(strQuery);
      frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", get_columns(show_variants::all_countries), true);
      if (query.Execute()) {
         BeginUpdate("tblOutput");
         for (query.First(); !query.IsEof(); query.Next()) {
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


std::vector<tplRepVal> TProcess::Districts_Brandenburg(void) {
   static std::string strQuery { "SELECT DISTINCT Kreis, Kreis_ID\n"s
                                 "FROM Brandenburg\n"s
                                 "ORDER BY Kreis"};
   auto query = db.CreateQuery();
   std::vector<tplRepVal> retval;
   query.SetSQL(strQuery);
   query.Execute();
   for (query.First(); !query.IsEof(); query.Next()) {
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
   frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", get_columns(show_variants::bdb_townships), true);

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

      query.Set("Kreis_ID", *frm.Get<EMyFrameworkType::combobox, int>("cbxDistrictsBbg"), true);
      query.Set("Land_ID", 12, true);

      std::clog << strTheme << std::endl;
      frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", get_columns(show_variants::bdb_townships), true);

      if (query.Execute()) {
         BeginUpdate("tblOutput");
         //size_t cnt = 0;
         for (query.First(); !query.IsEof(); query.Next()) {
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



