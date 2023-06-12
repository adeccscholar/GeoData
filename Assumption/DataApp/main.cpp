#include "DataApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::addLibraryPath("");
    DataApp w;
    w.show();
    return a.exec();
}
