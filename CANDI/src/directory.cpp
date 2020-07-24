#include "directory.hpp"
#include "debug.hpp"

#include <qdir.h>

// Escape a path correctly
QString escapePath(QString path)
{
   path = path.replace("/", QDir::separator());
   path = path.replace("\\", QDir::separator());

   return path;
}

namespace CANDI {

QString userDir()
{
    QString path = QDir::homePath();

    path += QDir::separator();

    path += ".candi";

    return escapePath(path);
}


QString logsDir()
{
    QString path = userDir();

    path += QDir::separator();

    path += "logs";

    return escapePath(path);
}


QString workspaceDir()
{
    QString path = userDir();

    path += QDir::separator();

    path += "workspaces";

    return escapePath(path);
}


QString defaultWorkspaceFile()
{
    QString path = userDir();

    path += QDir::separator();

    path += "default.candi_wks";

    return escapePath(path);
}


QString globalSettingsFile()
{
    QString path = userDir();

    path += QDir::separator();

    path += "settings.candi_set";

    return escapePath(path);
}


bool createSettingsDirectories()
{
    QStringList dirs;

    // List of directories to create
    dirs << userDir();
    dirs << logsDir();
    dirs << workspaceDir();

    for (QString dir : dirs)
    {
        if (QDir(dir).exists()) continue;

        bool result = QDir().mkdir(dir);

        if (result)
        {
            INFO << "Created directory" << dir;
        }
        else
        {
            WARNING << "Could not create directory" << dir;
            return false;
        }
    }

    // All done!
    return true;
}

}
