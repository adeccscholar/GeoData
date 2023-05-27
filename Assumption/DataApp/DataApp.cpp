#include "DataApp.h"


#include <adecc_Scholar/MyStream.h>
#include <adecc_Scholar/MyForm.h>
#include "MyDatabase.h"

#include <iostream>
#include <vector>

using namespace std::literals;

TStreamWrapper<Narrow> old_cout(std::cout);
TStreamWrapper<Narrow> old_cerr(std::cerr);
TStreamWrapper<Narrow> old_clog(std::clog);

std::vector<tplList<Latin>> Columns{
    tplList<Latin> { "city",   300, EMyAlignmentType::left },
    tplList<Latin> { "street", 350, EMyAlignmentType::left },
    tplList<Latin> { "id",     150, EMyAlignmentType::right }
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
    frm.Enable<EMyFrameworkType::button>("btnInsert", false);

    for (auto s : { &std::cout, &std::cerr, &std::clog }) s->setf(std::ios::fixed);
    std::clog << "ready" << std::endl;

    connect(ui.btnConnect, &QPushButton::clicked, this, [this]() {
       try {
          TMyDatabase<TMyQtDb, TMyMSSQL> data;
          data += TMyMSSQL { "TrainingNeu1" };
          data.Open();
          }
       catch(TMy_Db_Exception& ex) {
          std::cerr << ex.information() << std::endl;
          }
       catch(std::exception& ex) {
          std::cerr << ex.what() << std::endl;
          }

       /*
       db = QSqlDatabase::addDatabase("QODBC");
       db.setDatabaseName("DRIVER={SQL Server Native Client 11.0};SERVER=(local);DATABASE=TrainingNeu;Trusted_Connection=yes;");
       
       TMyWait wait;
       if(!db.open()) {
          std::cerr << "Fehler bei der Verbindung: " << db.lastError().text().toStdString() << std::endl;
          }
       else [[likely]] {
          std::clog << "connected successful" << std::endl;
          }
        */
       /*
          //QString queryText = "SELECT * FROM PErson WHERE Firstname = :firstName";
          QString queryText = "SELECT * FROM Person";
          QSqlQuery query(db);
          if(!query.prepare(queryText)) {
             std::cerr << "Fehler bei der Abfrage: " << db.lastError().text().toStdString() << std::endl;
             }
          else {
             //query.bindValue(":firstName", "Sabine");
             
             if(query.exec()) {
                for(query.first();query.isValid(); query.next()) {
                   std::cout << query.value("name").toString().toStdString() << "\t" << query.value("Firstname").toString().toStdString()
                             << "\t" << query.value("ID").toInt() << std::endl;
                   }
                }
             }

          }
          */
       });

   }

DataApp::~DataApp() {
   //delete statusLabel;
}
