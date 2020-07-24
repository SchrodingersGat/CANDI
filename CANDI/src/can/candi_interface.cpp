#include "candi_interface.hpp"

#include <qcanbusframe.h>

#include "debug.hpp"


CANDI_Interface::CANDI_Interface(QObject *parent) : QThread(parent)
{
    DEBUG << "CANDI_Inferface() created";
}


CANDI_Interface::~CANDI_Interface()
{
    // TODO - Disconnect adapter

    // TODO - Close log file

    DEBUG << "~CANDI_Interface() destroyed";
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
