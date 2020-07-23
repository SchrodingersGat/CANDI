#include "candi_version.h"


QString getCandiVersion()
{
    QString version;

    version += QString::number(CANDI_VERSION_MAJ);
    version += ".";

    version += QString::number(CANDI_VERSION_MIN);
    version += ".";

    version += QString::number(CANDI_VERSION_SUB);

    return version;
}
