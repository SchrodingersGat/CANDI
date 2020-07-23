#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <qstring.h>

namespace CANDI {

// Path to current user's local directory
QString userDir();

// Path to logs directory
QString logsDir();

// Pathspace to workspace file directory
QString workspaceDir();

// Paths to various hard-coded settings files
QString defaultWorkspaceFile();
QString globalSettingsFile();
}

#endif // DIRECTORY_HPP
