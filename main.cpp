

#include <QApplication>

#include "tabdialog.h"
#include "dialog.h"


int main(int argc, char *argv[])
{


    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("imageformats");
    paths.append("platforms");
    paths.append("sqldrivers");
    paths.append("printsupport");
    QCoreApplication::setLibraryPaths(paths);

    QApplication app(argc, argv);
    QString fileName;

    if (argc >= 2)
        fileName = argv[1];
    else
        fileName = ".";

    TabDialog tabdialog;



#ifdef Q_OS_SYMBIAN
    tabdialog.showMaximized();
#else
    tabdialog.showMaximized();
#endif

    return app.exec();
}
