#pragma once

#include "Processes.h"

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include "ui_DataApp.h"

class DataApp : public QMainWindow
{
    Q_OBJECT

public:
    DataApp(QWidget *parent = nullptr);
    ~DataApp();

private:
    Ui::DataAppClass ui;

    TProcess proc;
    QLabel* statusLabel;

};
