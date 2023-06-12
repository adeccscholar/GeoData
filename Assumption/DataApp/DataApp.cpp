#include "DataApp.h"

#include "UserDlg.h"

#include <adecc_Scholar/MyStream.h>
#include <adecc_Scholar/MyForm.h>

#include <iostream>
#include <vector>
#include <ranges>

using namespace std::literals;

DataApp::DataApp(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    ui.statusBar->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
    statusLabel = new QLabel(this);
    statusLabel->setObjectName("sbMain");
    statusLabel->setText("sbMain");
    ui.statusBar->addPermanentWidget(statusLabel);

    /*
    QList<int> sizes;
    sizes << 3 << 1;
    ui.mainSplitter->setSizes(sizes);
    */
    ui.tblOutput->setAlternatingRowColors(true);
    ui.tblOutput->setStyleSheet("alternate-background-color: lightgray;selection-background-color: red;");

    QHeaderView* header = ui.tblOutput->verticalHeader();
    header->setDefaultSectionSize(12); // 20 px height
    header->sectionResizeMode(QHeaderView::Fixed);

    TMyForm tmp { this, false };
    ui.chbShowMigrate->setChecked(false);
    ui.frmMigrate->setVisible(false);

    connect(ui.chbShowMigrate, &QCheckBox::stateChanged, this, [this](int state) {
       if (state == Qt::Checked) {
          ui.frmMigrate->setVisible(true);
          
          }
       else {
          ui.frmMigrate->setVisible(false);
          }
       });

    connect(ui.btnClose, &QPushButton::clicked, this, [this]() { close(); });
    connect(ui.btnTest, &QPushButton::clicked, this, [this]() { proc.test_function(); });

    connect(ui.btnConnect, &QPushButton::clicked, this, [this]() {
       TMyForm dlg(new UserDlg(this), true);
       proc.connect_to_database(std::move(dlg));
       });

    connect(ui.btnDisconnect, &QPushButton::clicked, this, [this]() {
       proc.disconnect_from_database();
       });

    connect(ui.btnShowCountries, &QPushButton::clicked, this, [this]() {
       proc.clear_history();
       proc.show(TProcess::show_variants::all_countries, true);
       });

    connect(ui.btnShowBlnDistricts, &QPushButton::clicked, this, [this]() {
       proc.clear_history();
       proc.show(TProcess::show_variants::bln_districts, true);
       });

    connect(ui.btnShowDistrictsBbg, &QPushButton::clicked, this, [this]() {
       proc.clear_history();
       proc.show(TProcess::show_variants::bdb_districts, true);
       });

    connect(ui.btnShow, &QPushButton::clicked, this, [this]() {
       proc.show(TProcess::show_variants::bdb_townships, true);
       });

    connect(ui.btnBack, &QPushButton::clicked, this, [this]() {
       proc.show_precursor();
       });


    connect(ui.btnInsertBbg, &QPushButton::clicked, this, [this]() {
       proc.insert_into_database({ TProcess::migrate_variants::bdb_opendata } );
       });

    connect(ui.btnInsertBln, &QPushButton::clicked, this, [this]() {
       proc.insert_into_database({ TProcess::migrate_variants::bln_opendata });
       });

    connect(ui.btnInsertTh, &QPushButton::clicked, this, [this]() {
       proc.insert_into_database({ TProcess::migrate_variants::th_opendata_keys,TProcess::migrate_variants::th_opendata } );
       });
    
    connect(ui.btnInsertSn, &QPushButton::clicked, this, [this]() {
       proc.insert_into_database({ TProcess::migrate_variants::sn_opendata_keys,TProcess::migrate_variants::sn_opendata });
       });

    connect(ui.btnInsertAdm, &QPushButton::clicked, this, [this]() {
       proc.insert_into_database({ TProcess::migrate_variants::administrations });
       });

    connect(ui.btnMigrateBln, &QPushButton::clicked, this, [this]() {
       proc.migrate_neues_Model();
       //proc.print_migrate_Berlin(std::cerr);
       });

    connect(ui.tblOutput, &QTableWidget::itemDoubleClicked, this, [this](QTableWidgetItem*) {
       proc.Action();
       });

    connect(ui.tblOutput, &QTableWidget::itemSelectionChanged, this, [this]() { 
       proc.Changed_Selection();
       });

    proc.init_mainform(std::forward<TMyForm>(tmp));
   }

DataApp::~DataApp() {
   //delete statusLabel;
   }

