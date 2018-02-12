

#include <QApplication>
#include <QFile>
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


    QFile file(":/qss/default.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);
    QPalette p = qApp->palette();
    p.setColor(QPalette::Window, QColor(53,53,53));
    p.setColor(QPalette::Button, QColor(53,53,53));
    p.setColor(QPalette::Highlight, QColor(175,0,0));
    p.setColor(QPalette::ButtonText, QColor(255,255,255));
    p.setColor(QPalette::WindowText, QColor(255,255,255));
  //  qApp->setPalette(p);

    TabDialog tabdialog;



#ifdef Q_OS_SYMBIAN
    tabdialog.showMaximized();
#else
    tabdialog.showMaximized();
#endif

    return app.exec();
}
