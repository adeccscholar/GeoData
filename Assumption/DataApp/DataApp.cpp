#include "DataApp.h"


#include <adecc_Scholar/MyStream.h>
#include <adecc_Scholar/MyForm.h>
#include "MyDatabase.h"
#include "MyFileIterator.h"
#include "MyConvert.h"
#include "MyLocation.h"

#include <iostream>
#include <vector>
#include <ranges>

using namespace std::literals;

TStreamWrapper<Narrow> old_cout(std::cout);
TStreamWrapper<Narrow> old_cerr(std::cerr);
TStreamWrapper<Narrow> old_clog(std::clog);

std::vector<tplList<Latin>> Columns{
    tplList<Latin> { "name",      300, EMyAlignmentType::left },
    tplList<Latin> { "firstname", 350, EMyAlignmentType::left },
    tplList<Latin> { "id",        150, EMyAlignmentType::right }
};

DataApp::DataApp(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);

    ui.statusBar->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
    statusLabel = new QLabel(this);
    statusLabel->setObjectName("sbMain");
    statusLabel->setText("sbMain");
    ui.statusBar->addPermanentWidget(statusLabel);

    TMyForm frm(this);
    frm.SetCaption("database preparation ...");
    frm.GetAsStream<Narrow, EMyFrameworkType::listview>(old_cout, "tblOutput", Columns);
    frm.GetAsStream<Narrow, EMyFrameworkType::memo>(old_cerr, "txtError");
    frm.GetAsStream<Narrow, EMyFrameworkType::statusbar>(old_clog, "sbMain");
    frm.Set<EMyFrameworkType::button, std::string>("btnConnect", "Verbinden");
    frm.Set<EMyFrameworkType::button, std::string>("btnInsert",  "Einfügen"s);
    frm.Enable<EMyFrameworkType::button>("btnInsert", true);

    for (auto s : { &std::cout, &std::cerr, &std::clog }) s->setf(std::ios::fixed);
    std::clog << "ready" << std::endl;

    connect(ui.btnConnect, &QPushButton::clicked, this, [this]() {
       try {
          TMyDatabase<TMyQtDb, TMyMSSQL> data;
          data = TMyMSSQL{ "TrainingNeu" };
          if (!data.Open()) {
             std::cerr << "Fehler bei der Verbindung: " << static_cast<QSqlDatabase&>(data).lastError().text().toStdString() << std::endl;
          }
          else [[likely]] {
             std::clog << "connected successful" << std::endl;
             TMyWait wait;
             auto query = data.CreateQuery();
             query.SetSQL("SELECT * FROM Person WHERE FormOfAddress = :FormOfAddress");
             query.Set("FormOfAddress", 1);
             for (query.Execute(), query.First(); !query.IsEof(); query.Next()) {
                std::cout << query.Get<std::string>("name").value_or("-") << "\t"
                   << query.Get<std::string>("Firstname").value_or("-") << "\t"
                   << *query.Get<int>("ID", true) << std::endl;
                }
             }
          }
       catch (TMy_Db_Exception& ex) {
          std::cerr << ex.information() << std::endl;
          }
       catch (std::exception& ex) {
          std::cerr << ex.what() << std::endl;
          }
       });
    connect(ui.btnInsert, &QPushButton::clicked, this, [this]() {
       TMyDatabase<TMyQtDb, TMyMSSQL> data;
       try {
          data = TMyMSSQL{ "GeoDaten" };
          if (!data.Open()) {
             std::cerr << "Fehler bei der Verbindung: " << static_cast<QSqlDatabase&>(data).lastError().text().toStdString() << std::endl;
             }
          else [[likely]] {
             std::clog << "connected successful" << std::endl;
             TMyWait wait;
             std::string strBuffer;
             auto query1 = data.CreateQuery();
             query1.SetSQL("DELETE FROM Berlin");
             query1.Execute();

             auto query = data.CreateQuery();
             query.SetSQL("INSERT INTO Berlin (Land_ID, Bezirk_ID, Ortsteil_ID, Strasse_ID, Land, Bezirk, "s +
                                              "Ortsteil, Strasse, PLZ, HNR, ADZ, Latitude, Longitude)\n"s +
                          "VALUES(:Land_ID, :Bezirk_ID, :Ortsteil_ID, :Strasse_ID, :Land, :Bezirk, :Ortsteil, :Strasse, "s +
                                 ":PLZ, :HNR, :ADZ, :Latitude, :Longitude)"s);
             for(int linecnt = 0; auto const& line : my_lines { GetContent("d:\\test\\Adressen_-_Berlin.csv", strBuffer)}) {
                auto test = std::string_view { line.begin(), line.end() } | std::views::split(","sv)
                   | std::views::transform([](auto d) { return std::string_view { d.begin(), d.end() }; })
                   | std::ranges::to<std::vector>();

                query.Set("Land_ID", 11);
                query.Set("Bezirk_ID", string_to_int<int>(test[10]));
                query.Set("Ortsteil_ID", string_to_int<int>(test[12]));
                query.Set("Strasse_ID", string_to_int<int>(test[6]));
                query.Set("Land", test[21]);
                query.Set("Bezirk", test[9]);
                query.Set("Ortsteil", test[11]);
                query.Set("Strasse", test[7]);
                query.Set("PLZ", test[8]);
                query.Set("HNR", string_to_int<int>(test[4]));
                query.Set("ADZ", test[5]);

                myMercatorETRS89<double> loc { string_to_float<double>(test[0]),
                   string_to_float<double>(test[1]) };
                auto position = Location<double>::ConvertMercatorETRS89ToWGS84(loc);
                query.Set("Latitude", position.first);
                query.Set("Longitude", position.second);
                query.Execute();
                }
             }
          }
       catch (std::exception& ex) {
          std::cerr << ex.what() << std::endl;
          }

       });
}

DataApp::~DataApp() {
   //delete statusLabel;
}
