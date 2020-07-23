#ifndef CANDI_VERSION_H
#define CANDI_VERSION_H

#include <qstring.h>

#define CANDI_VERSION_MAJ 0
#define CANDI_VERSION_MIN 0
#define CANDI_VERSION_SUB 1

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

#endif // CANDI_VERSION_H
