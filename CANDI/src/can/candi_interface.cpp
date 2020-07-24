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
