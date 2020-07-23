
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "debug.hpp"

// By default, display warning or higher
static uint8_t DEBUG_LEVEL = QtDebugMsg;

void setDebugLevel(uint8_t level)
{
    DEBUG_LEVEL = level;
}


void customDebugHandler(QtMsgType msgType, const QMessageLogContext &context, const QString &msg)
{
    // Quickly decide if we are going to display the message or not
    if (DEBUG_LEVEL > msgType)
    {
        return;
    }

    QByteArray message = msg.toLocal8Bit();

    const char *file = context.file ? context.file : "";
    const char *func = context.function ? context.function : "";

    QString prefix;

    QTime t = QTime::currentTime();

    QString time = t.toString() + "." + QString::number(t.msec());

    switch (msgType)
    {
    default:
        break;
    case QtFatalMsg:
        prefix = "Fatal:";
        break;
    case QtCriticalMsg:
        prefix = "Critical:";
        break;
    case QtWarningMsg:
        prefix = "Warning:";
        break;
    case QtInfoMsg:
        prefix = "Info:";
        break;
    case QtDebugMsg:
        prefix = "Debug:";
        break;
    }

    if (!prefix.isEmpty())
    {
        QString out = time + QString(" ") + prefix + QString(" ") + QString(message);

        std::cout << out.toStdString() << std::endl;

        // TODO - Print file and function information if it exists
        Q_UNUSED(file);
        Q_UNUSED(func);
    }
}
