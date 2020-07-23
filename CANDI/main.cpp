#include <QApplication>
#include <qcommandlineparser.h>

#include "mainwindow.h"

#include "candi_version.h"
#include "debug.hpp"

int main(int argc, char *argv[])
{
    qInstallMessageHandler(customDebugHandler);

    QApplication a(argc, argv);

    a.setOrganizationName("CANDI");
    a.setApplicationName("CANDI");
    a.setApplicationDisplayName("CANDI viewer");
    a.setApplicationVersion(getCandiVersion());

    QCommandLineParser parser;

    parser.addHelpOption();
    parser.addVersionOption();
    parser.setApplicationDescription("CANDI viewer");

    QCommandLineOption debugLevel(QStringList() << "d" << "debug", "Set the debug level", "2");

    parser.addOption(debugLevel);

    parser.process(a);

    bool ok = false;

    int debugValue = parser.value(debugLevel).toInt(&ok);

    if (ok)
    {
        setDebugLevel(debugValue);
    }

    MainWindow w;
    w.show();

    return a.exec();
}
