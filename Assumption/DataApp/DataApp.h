#pragma once

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QtSQL>
#include "ui_DataApp.h"

class DataApp : public QMainWindow
{
    Q_OBJECT

public:
    DataApp(QWidget *parent = nullptr);
    ~DataApp();

private:
    Ui::DataAppClass ui;

    QSqlDatabase db;
    QLabel* statusLabel;
};
