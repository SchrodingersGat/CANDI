#ifndef CANDI_INTERFACE_HPP
#define CANDI_INTERFACE_HPP

#include <qthread.h>
#include <qcanbus.h>
#include <qmutex.h>
#include <qpluginloader.h>

#include <qsettings.h>

#include <memory>


class CANDI_Interface : public QThread
{
    Q_OBJECT

public:
    CANDI_Interface(QObject *parent = nullptr);
    virtual ~CANDI_Interface();

    static QStringList GetAvailablePlugins();
    static QStringList GetAvailableDevices(const QString pluginName, QString *errorMsg = nullptr);

protected:
    // Mutexes
    QMutex canMutex;
    QMutex logMutex;

    // Frame counters
    uint64_t txCount = 0;
    uint64_t rxCount = 0;

    // Pending data to be written to log file
    QList<QStringList> pendingLogData;
};

#endif // CANDI_INTERFACE_HPP
