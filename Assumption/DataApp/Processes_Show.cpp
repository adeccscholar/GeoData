#include "Processes.h"

// *************** Definition für Actions *********************


TProcess::show_countries TProcess::ShowCountries = { { "Berlin"s,      { { TProcess::show_variants::bln_districts } } },
                                                     { "Brandenburg"s, { { TProcess::show_variants::bdb_districts } } }
                                                   };

std::vector<tplList<Narrow>> TProcess::Administrations_Columns {
   tplList<Narrow> { "owner", 150, EMyAlignmentType::left  },
      tplList<Narrow> { "category", 90, EMyAlignmentType::left  },
      tplList<Narrow> { "key", 190, EMyAlignmentType::left  },
      tplList<Narrow> { "designation", 180, EMyAlignmentType::left  },
      tplList<Narrow> { "street", 180, EMyAlignmentType::left  },
      tplList<Narrow> { "number", 80, EMyAlignmentType::left  },
      tplList<Narrow> { "zipcode", 70, EMyAlignmentType::right },
      tplList<Narrow> { "city", 180, EMyAlignmentType::left  },
      tplList<Narrow> { "latitude", 80, EMyAlignmentType::right },
      tplList<Narrow> { "longitude", 80, EMyAlignmentType::right }
};
/*
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
      tplList<Narrow> { "district",      200, EMyAlignmentType::left   },
      tplList<Narrow> { "township",      200, EMyAlignmentType::left   },
      tplList<Narrow> { "city",          200, EMyAlignmentType::left   },
      tplList<Narrow> { "country#",        0, EMyAlignmentType::right  },
      tplList<Narrow> { "district#",       0, EMyAlignmentType::right  },
      tplList<Narrow> { "Township#",       0, EMyAlignmentType::right  },
      tplList<Narrow> { "count",         100, EMyAlignmentType::right  }
   };

std::vector<tplList<Narrow>> TProcess::Brandenburg_Cities {
   };

std::vector<tplList<Narrow>> TProcess::Country_Columns {
      tplList<Narrow> { "country",       190, EMyAlignmentType::left   },
      tplList<Narrow> { "kind",          160, EMyAlignmentType::left   },
      tplList<Narrow> { "capital",       170, EMyAlignmentType::left   },
      tplList<Narrow> { "abbr",          110, EMyAlignmentType::center },
      tplList<Narrow> { "latitude",      130, EMyAlignmentType::right  },
      tplList<Narrow> { "longitude",     130, EMyAlignmentType::right  },
      tplList<Narrow> { "code",           90, EMyAlignmentType::right  }
   };


std::vector<tplList<Narrow>> TProcess::Berlin_Districts_Columns {
      tplList<Narrow> { "District", 190, EMyAlignmentType::left   },
      tplList<Narrow> { "Abbr.", 60, EMyAlignmentType::left   },
      tplList<Narrow> { "Code", 70, EMyAlignmentType::center },
      tplList<Narrow> { "City hall", 210, EMyAlignmentType::left   },
      tplList<Narrow> { "Zipcode", 70, EMyAlignmentType::left   },
      tplList<Narrow> { "City", 150, EMyAlignmentType::left   },
      tplList<Narrow> { "Street", 180, EMyAlignmentType::left   },
      tplList<Narrow> { "latitude", 80, EMyAlignmentType::right  },
      tplList<Narrow> { "longitude", 80, EMyAlignmentType::right  }
   };

std::vector<tplList<Narrow>> TProcess::Berlin_District_Neighborhoods_Columns {
      tplList<Narrow> { "District", 200, EMyAlignmentType::left   },
      tplList<Narrow> { "Abbr.", 80, EMyAlignmentType::left   },
      tplList<Narrow> { "Neighborhood", 200, EMyAlignmentType::left   },
      tplList<Narrow> { "state#", 80, EMyAlignmentType::center },
      tplList<Narrow> { "district#", 80, EMyAlignmentType::center },
      tplList<Narrow> { "latitude", 80, EMyAlignmentType::right  },
      tplList<Narrow> { "longitude", 80, EMyAlignmentType::right  }
   };
*/
/*
TProcess::show_variants::bdb_cities,
*/
std::map<TProcess::show_variants, TProcess::show_data> TProcess::ShowData {
   { TProcess::show_variants::all_countries, { "show all data for countries in Germany"s,
      "SELECT ID, Land, Abkuerzung, Status, Hauptstadt, Laengengrad, Breitengrad\n"s +
      "FROM Deutschland\n"s +
      "ORDER BY Land"s,
      [](TProcess& proc, TMyForm& frm) { my_db_params params{ };  return params; },
      {   myCaption { "country",       190, EMyAlignmentType::left   },
          myCaption { "kind",          160, EMyAlignmentType::left   },
          myCaption { "capital",       170, EMyAlignmentType::left   },
          myCaption { "abbr",          110, EMyAlignmentType::center },
          myCaption { "latitude",      130, EMyAlignmentType::right  },
          myCaption { "longitude",     130, EMyAlignmentType::right  },
          myCaption { "code",           90, EMyAlignmentType::right  } },
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
      [](TMyForm& frm, myCaptions const& columns) {
            frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", columns, true);
            frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", false);
            return true;
            },
      [](TMyForm& frm) {
            frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", true);
            }
   } },
      //--------------------------------------------------------------------------------------------------------
   { TProcess::show_variants::bln_districts, { "show districts for Berlin"s,
       "SELECT Stadtbezirk,Abkuerzung,Bezirk_ID,Rathaus,Rathaus_PLZ,Rathaus_Ort,Rathaus_Strasse,"s +
              "Rathaus_Nummer,Rathaus_Breite,Rathaus_Laenge\n"s +
       "FROM Berliner_Stadtbezirke"s,
       [](TProcess& proc, TMyForm& frm) { my_db_params params{ };  return params; },
       {  myCaption { "District",  190, EMyAlignmentType::left   },
          myCaption { "Abbr.",      60, EMyAlignmentType::left   },
          myCaption { "Code",       70, EMyAlignmentType::center },
          myCaption { "City hall", 210, EMyAlignmentType::left   },
          myCaption { "Zipcode",    70, EMyAlignmentType::left   },
          myCaption { "City",      150, EMyAlignmentType::left   },
          myCaption { "Street",    180, EMyAlignmentType::left   },
          myCaption { "latitude",   80, EMyAlignmentType::right  },
          myCaption { "longitude",  80, EMyAlignmentType::right  } },
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
       [](TMyForm& frm, myCaptions const& columns) {
             frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", columns, true);
             frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", false);
             return true;
             },
       [](TMyForm& frm) {
             frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", true);
             }
   } },
      //--------------------------------------------------------------------------------------------------
   { TProcess::show_variants::bdb_districts, { "Display all districts and independent cities in Brandenburg."s, // theme
      "SELECT Kreis,Kreisstadt,Status,Abkuerzung,Land_ID,Kreis_ID,Breite,Laenge\n"s +
      "FROM Brandenburg_Kreise\n"s +
      "ORDER BY Kreis"s,
      [](TProcess& proc, TMyForm& frm) { my_db_params params{ };  return params; },
      {   myCaption { "district",      200, EMyAlignmentType::left   },
          myCaption { "district town", 200, EMyAlignmentType::left   },
          myCaption { "category",      150, EMyAlignmentType::center },
          myCaption { "abbr",          100, EMyAlignmentType::center },
          myCaption { "country#",        0, EMyAlignmentType::right  },
          myCaption { "district#",       0, EMyAlignmentType::right  },
          myCaption { "latitude",      130, EMyAlignmentType::right  },
          myCaption { "longitude",         130, EMyAlignmentType::right  } },
      [](concrete_query& query, std::ostream& out) {
              out << *query.Get<std::string>("Kreis", true) << "\t"
                  << query.Get<std::string>("Kreisstadt").value_or("") << "\t"
                  << *query.Get<std::string>("Status", true) << "\t"
                  << query.Get<std::string>("Abkuerzung").value_or(""s) << "\t"
                  << *query.Get<int>("Land_ID", true) << "\t"
                  << *query.Get<int>("Kreis_ID", true) << "\t"
                  << query.Get<double>("Breite").value_or(0.0) << "\t"
                  << query.Get<double>("Laenge").value_or(0.0) << std::endl;
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
      [](TProcess& proc, TMyForm& frm) {
             auto rows = frm.GetSelectedRows<EMyFrameworkType::listview>("tblOutput");
             if (rows.size() > 0) {
               std::optional<int> cntry = frm.GetValue<EMyFrameworkType::listview, int>("tblOutput", rows[0], 4);
               std::optional<int> distr = frm.GetValue<EMyFrameworkType::listview, int>("tblOutput", rows[0], 5);
               if (cntry && distr)
                  proc.show(TProcess::show_variants::bdb_townships, true, { {"Kreis_ID"s, *distr, true},
                                                                            {"Land_ID"s, *cntry, true } });
                }
             }, // action for double clicked in list
      [](TMyForm& frm, myCaptions const& columns) {
            frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", columns, true);
            frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", false);
            return true;
            }, // prepare
      [](TMyForm& frm) {
            frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", true);
            }
   } },
      //-------------------------------------------------------------------------------------------------
   { TProcess::show_variants::bdb_townships, { "show districts and townships for Brandenburg"s,
      "SELECT Kreis, Gemeinde, Ort, Land_ID, Kreis_ID, Gemeinde_ID, Count(*) AS Anzahl\n"s
      "FROM Brandenburg\n"s +
      "WHERE Kreis_ID = :Kreis_ID and Land_ID = :Land_ID\n"s +
      "GROUP BY Kreis, Gemeinde, Ort, Land_ID, Kreis_ID, Gemeinde_ID\n"s +
      "ORDER BY Kreis, Gemeinde, ORT"s,
      [](TProcess& proc, TMyForm& frm) {
         my_db_params params {{"Kreis_ID"s, *frm.Get<EMyFrameworkType::combobox, int>("cbxDistrictsBbg"), true},
                              {"Land_ID"s, 12, true }};
         return params;
         },
      {   myCaption { "district",      200, EMyAlignmentType::left   },
          myCaption { "township",      200, EMyAlignmentType::left   },
          myCaption { "city",          200, EMyAlignmentType::left   },
          myCaption { "country#",        0, EMyAlignmentType::right  },
          myCaption { "district#",       0, EMyAlignmentType::right  },
          myCaption { "Township#",       0, EMyAlignmentType::right  },
          myCaption { "count",         100, EMyAlignmentType::right  } },
      [](concrete_query& query, std::ostream& out) {
         out << *query.Get<std::string>("Kreis") << "\t"
             << *query.Get<std::string>("Gemeinde") << "\t"
             << *query.Get<std::string>("Ort") << "\t"
             << *query.Get<int>("Land_ID", true) << "\t"
             << *query.Get<int>("Kreis_ID", true) << "\t"
             << *query.Get<int>("Gemeinde_ID", true) << "\t"
             << *query.Get<int>("Anzahl", true) << std::endl;
         },
      [](TProcess& proc, TMyForm&) {
         proc.choosen_list = TProcess::show_variants::bdb_townships;
         },
      [](TProcess& proc, TMyForm&) {
         },
      [](TProcess& proc, TMyForm& frm) {
         auto rows = frm.GetSelectedRows<EMyFrameworkType::listview>("tblOutput");
         if (rows.size() > 0) {
            std::optional<int> cntry = frm.GetValue<EMyFrameworkType::listview, int>("tblOutput", rows[0], 3);
            std::optional<int> distr = frm.GetValue<EMyFrameworkType::listview, int>("tblOutput", rows[0], 4);
            if (cntry && distr)
               proc.show(TProcess::show_variants::bdb_cities, true, { {"Kreis_ID"s, *distr, true},
                                                                      {"Land_ID"s, *cntry, true } });
            }
         },
      [](TMyForm& frm, myCaptions const& columns) {
         frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", columns, true);
         frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", false);
         return true;
         },
      [](TMyForm& frm) {
         frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", true);
         }
   } },
      //------------------------------------------------------------------------------------------------------------
   { TProcess::show_variants::bdb_cities, { "show cities in Brandenburg"s, // theme
      "SELECT Stadt, Stadt_sorbisch, Kreis, Abkuerzung_Kreis, Status, Breite, Laenge, Land_ID, Kreis_ID, Gemeinde_ID,\n"s +
      "       Rathaus, Rathaus_PLZ, Rathaus_Ort, Rathaus_Strasse, Rathaus_Nummer, Rathaus_Breite, Rathaus_Laenge\n"s +
      "FROM Brandenburg_Staedte\n"s +
      "WHERE Land_ID = :Land_ID AND Kreis_ID = :Kreis_ID"s, // query
      [](TProcess& proc, TMyForm& frm) { /* Parameter for Query */ my_db_params params{ };  return params;  }, 
      {  myCaption { "name of city",      180, EMyAlignmentType::left   },
         myCaption { "name in Sorbian",   180, EMyAlignmentType::left   },
         myCaption { "district",          180, EMyAlignmentType::left   },
         myCaption { "status",            120, EMyAlignmentType::left   },
         myCaption { "longitude",         120, EMyAlignmentType::right  },
         myCaption { "latitude",          120, EMyAlignmentType::right  } },
      [](concrete_query& query, std::ostream& out) {
         out << query.Get<std::string>("Stadt").value_or("-") << "\t"
             << query.Get<std::string>("Stadt_sorbisch").value_or("-") << "\t"
             << query.Get<std::string>("Kreis").value_or("<undefiniert>") << "\t"
             << query.Get<std::string>("Status").value_or("") << "\t"
             << query.Get<double>("Breite").value_or(0.0) << "\t"
             << query.Get<double>("Laenge").value_or(0.0) << "\n";
         }, // show
      [](TProcess& proc, TMyForm&) { /* confirm after */ },
      [](TProcess& proc, TMyForm&) { /* action for select in list */ },
      [](TProcess& proc, TMyForm&) { /* action for double clicked in list */ },
      [](TMyForm& frm, myCaptions const& columns) { /* prepare */  
         frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", columns, true);
         frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", false);
         return true;
         },
      [](TMyForm& frm) { 
         frm.EnableUpdates<EMyFrameworkType::listview>("tblOutput", true); 
         }
   } },
      //----------------------------------------------------------------------------------------------------------------
   { TProcess::show_variants::blank, { ""s, // theme
      ""s, // query
      [](TProcess& proc, TMyForm& frm) { my_db_params params{ };  return params;  }, // set for query
      { },
      [](concrete_query& query, std::ostream& out) {}, // show
      [](TProcess& proc, TMyForm&) {}, // confirm after
      [](TProcess& proc, TMyForm&) {}, // action for select in list
      [](TProcess& proc, TMyForm&) {}, // action for double clicked in list
      [](TMyForm& frm, myCaptions const& columns) { return true; }, // prepare
      [](TMyForm& frm) {}               // finish
   } }
};

/*

*/

TProcess::myCaptions const& TProcess::get_columns(show_variants variant) {
   static constexpr auto col_val = [](show_data_columns col) { return static_cast<int>(col); };

   auto action = ShowData.find(variant);
   if (action == ShowData.end())
      throw TMy_RuntimeError("unknown variant to show");
   else [[likely]] {
      return std::get<col_val(show_data_columns::columns)>(action->second);
      }
   }

void TProcess::show(show_variants variant, bool boHistory, my_db_params const& extern_params) {
   static constexpr auto col_val = [](show_data_columns col) { return static_cast<int>(col); };

   auto action = ShowData.find(variant);
   if (action == ShowData.end())
      throw TMy_RuntimeError("unknown variant to show");
   else [[likely]] {
      show_data const& data = action->second;
      TMyWait wait;

      auto start = std::chrono::system_clock::now();
      auto& prepare = std::get<col_val(show_data_columns::prepare)>(data);
      if(!prepare || prepare(frm, std::get<col_val(show_data_columns::columns)>(data))) {
         auto query = db.CreateQuery();
         try {
            query.SetSQL(std::get<col_val(show_data_columns::query)>(data));
            if (extern_params.size() == 0) {
               auto params = std::get<col_val(show_data_columns::set)>(data)(*this, frm);
               query.Set(params);
               if (boHistory) history.emplace(std::make_pair(variant, params));
            }
            else {
               query.Set(extern_params);
               if (boHistory) {
                  history.emplace(std::make_pair(variant, extern_params));
               }
            }

            if (history.size() > 1) frm.Enable<EMyFrameworkType::button>("btnBack", true);

            if (auto show = std::get<col_val(show_data_columns::show)>(data); show != nullptr) {
               for (query.Execute(), query.First(); !query.IsEof(); query.Next()) {
                  show(query, std::cout);
                  }
               }

            if (auto confirm = std::get<col_val(show_data_columns::confirm)>(data); confirm != nullptr) {
               confirm(*this, frm);
               }

            choosen_action = std::get<col_val(show_data_columns::action)>(data);
            choosen_select = std::get<col_val(show_data_columns::select)>(data);

            if (auto finish = std::get<col_val(show_data_columns::finish)>(data); finish != nullptr) {
               finish(frm);
               }

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
   }

void TProcess::clear_history() {
   while (!history.empty()) history.pop();
   frm.Enable<EMyFrameworkType::button>("btnBack", false);
   }

void TProcess::show_last() {
   if (!history.empty()) {
      auto const& [variant, params] = history.top();
      show(variant, false, params);
      }
   }

void TProcess::show_precursor() {
   if (history.size() > 1) {
      history.pop();
      auto const& [variant, params] = history.top();
      show(variant, false, params);
      if (history.size() < 2) frm.Enable<EMyFrameworkType::button>("btnBack", false);
      }
   }

