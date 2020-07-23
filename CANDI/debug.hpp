/**

Custom debug handlers for re-directing debug output messages.

**/

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <qdatetime.h>
#include <qdebug.h>

// Pre-processor defines
#define DEBUG qDebug()
#define INFO qInfo()
#define WARNING qWarning()
#define CRITICAL qCritical()
#define FATAL qFatal()

void setDebugLevel(uint8_t level);
void customDebugHandler(QtMsgType msgType, const QMessageLogContext &context, const QString &msg);

#endif // DEBUG_HPP
