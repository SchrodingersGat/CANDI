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

private:
    CANDI_Interface();

public:
    CANDI_Interface(CANDI_Interface const&) = delete;
    CANDI_Interface& operator=(CANDI_Interface const&) = delete;

    // Singleton design pattern to only allow a single instance of the interface class
    static std::shared_ptr<CANDI_Interface> instance()
    {
        static std::shared_ptr<CANDI_Interface> s{new CANDI_Interface};
        return s;
    }

    virtual ~CANDI_Interface();

    static QStringList GetAvailablePlugins();
    static QStringList GetAvailableDevices(const QString pluginName, QString *errorMsg = nullptr);

    void loadSettings(QSettings &settings);
    void saveSettings(QSettings &settings);

public slots:

    // Connection controls
    bool isConnected(void);
    bool connect(QString pluginName = QString(), QString deviceName = QString(), QString *errMsg = nullptr);
    void disconnect(void);

    // Logging controls
    bool isLogging(void);
    void startLogging(void);
    void stopLogging(void);

protected:
    // Mutexes
    QMutex canMutex;
    QMutex logMutex;

    // Frame counters
    uint64_t txCount = 0;
    uint64_t rxCount = 0;

    // Pending data to be written to log file
    QList<QStringList> pendingLogData;

    // Name of the most recently used CAN plugin
    QString mostRecentPlugin;

    // Name of the most recently used CAN device
    QString mostRecentDevice;
};

#endif // CANDI_INTERFACE_HPP
