#include "candi_interface.hpp"

#include <qcanbusframe.h>

#include "debug.hpp"


CANDI_Interface::CANDI_Interface() : QThread()
{
    DEBUG << "CANDI_Inferface() created";
}


CANDI_Interface::~CANDI_Interface()
{
    // TODO - Disconnect adapter

    // TODO - Close log file

    // TODO - Stop thread

    DEBUG << "~CANDI_Interface() destroyed";
}


void CANDI_Interface::run()
{
    running = true;

    DEBUG << "CANDI_Interface::run started";

    while (running)
    {
        // TODO

        msleep(500);
    }

    DEBUG << "CANDI_Interface::run complete";
}


void CANDI_Interface::stop()
{
    DEBUG << "CANDI_Interface::stop";

    running = false;
    wait();
}


/**
 * @brief CANDI_Interface::GetAvailablePlugins - Generate a list of available QCanBus plugins
 */
QStringList CANDI_Interface::GetAvailablePlugins()
{
    return QCanBus::instance()->plugins();
}


/**
 * @brief CANDI_Interface::GetAvailableDevices - Generate a list of available (connected) devices for a given plugin
 * @param pluginName - The name of the QCanBus plugin
 * @param errorMsg - Pointer to store potential error message
 * @return - List of connected devices
 */
QStringList CANDI_Interface::GetAvailableDevices(const QString pluginName, QString *errorMsg)
{
    auto available = QCanBus::instance()->availableDevices(pluginName, errorMsg);

    QStringList devices;

    for (auto dev : available)
    {
        // Ignore virtual devices
        if (dev.isVirtual()) continue;

        devices.append(dev.name());
    }

    return devices;
}


void CANDI_Interface::saveSettings(QSettings &settings)
{
    settings.beginGroup("can");

    settings.setValue("plugin", mostRecentPlugin);
    settings.setValue("device", mostRecentDevice);

    settings.endGroup();
}


void CANDI_Interface::loadSettings(QSettings &settings)
{
    settings.beginGroup("can");

    mostRecentPlugin = settings.value("plugin", QString()).toString();
    mostRecentDevice = settings.value("device", QString()).toString();

    settings.endGroup();
}


bool CANDI_Interface::isConnected()
{
    canMutex.lock();

    bool connected = (adapter != nullptr) && (adapter->state() == QCanBusDevice::ConnectedState);

    canMutex.unlock();

    return connected;
}

/**
 * @brief CANDI_Interface::openConnection - Attempt to connect to a CAN device
 * @param pluginName - Name of the CAN plugin to use (optional)
 * @param deviceName - Name of the CAN device to use (optional)
 * @param errMsg - Pointer to store any error messages
 * @return - True if the connection succeeded
 */
bool CANDI_Interface::openConnection(QString pluginName, QString deviceName, QString *errMsg)
{
    if (isConnected())
    {
        if (errMsg)
        {
            *errMsg = "CAN Interface already connected";
        }

        return false;
    }

    canMutex.lock();

    bool found = false;

    QStringList plugins = QCanBus::instance()->plugins();

    for (QString plugin : plugins)
    {
        if (!pluginName.isEmpty() && (pluginName.toLower() != plugin.toLower()))
        {
            continue;
        }

        QStringList devices = GetAvailableDevices(plugin, errMsg);

        /*
         * Iterate through each device provided by the interface.
         * If we are requesting a specific device string, look for a match.
         * Otherwise, try to connect to the first device we see.
         */

        for (QString device : devices)
        {
            if (!deviceName.isEmpty() && (deviceName.toLower() != device.toLower()))
            {
                continue;
            }

            DEBUG << "Attempting to open CAN device ->" << plugin << ":" << device;

            adapter = QCanBus::instance()->createDevice(plugin, device, errMsg);

            if (adapter)
            {
                configureInterface();

                if (adapter->connectDevice())
                {
                    INFO << "Connected to device";
                    connect(adapter, SIGNAL(framesReceived()), this, SLOT(onFramesReceived()));

                    found = true;
                }
                else
                {
                    DEBUG << "Could not connect to device";

                    delete adapter;
                    adapter = nullptr;
                }
            }

            if (found)
            {
                break;
            }
        }

        if (found)
        {
            break;
        }
    }

    canMutex.unlock();

    if (found)
    {
        DEBUG << "Successfully opened CAN device";

        resetCounters();

        return true;
    }
    else
    {
        adapter = nullptr;

        DEBUG << "Could not find appropriate CAN interface";

        return false;
    }
}


void CANDI_Interface::configureInterface()
{
    // TODO - Load interface settings
}


bool CANDI_Interface::writeFrame(QCanBusFrame &frame)
{
    if (!isConnected() || !adapter) return false;

    if (!canMutex.tryLock(25))
    {
        WARNING << "Could not secure lock for writeFrame";
        return false;
    }

    bool result = adapter->writeFrame(frame);

    canMutex.unlock();

    if (result)
    {
        // TODO - Add the transmitted frame to the logger
    }

    return result;
}


void CANDI_Interface::onFramesReceived()
{
    canMutex.lock();

    QVector<QCanBusFrame> frames;

    if (adapter)
    {
        if (adapter->framesAvailable() > 0)
        {
            frames = adapter->readAllFrames();
        }
    }

    canMutex.unlock();

    // TODO - Process the read frames
}


void CANDI_Interface::closeConnection()
{
    canMutex.lock();

    if (adapter != nullptr)
    {
        if (adapter->state() == QCanBusDevice::ConnectedState)
        {
            disconnect(adapter, SIGNAL(framesReceived()), this, SLOT(onFramesReceived()));
            adapter->disconnectDevice();
        }

        delete adapter;
    }

    adapter = nullptr;

    stopLogging();

    canMutex.unlock();
}


void CANDI_Interface::resetCounters()
{
    canMutex.lock();

    rxCount = 0;
    txCount = 0;

    canMutex.unlock();
}


bool CANDI_Interface::isLogging()
{
    // TODO

    return false;
}


void CANDI_Interface::startLogging()
{
    // TODO
}


void CANDI_Interface::stopLogging()
{
    // TODO
}
