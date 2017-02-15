#include "superfileremover.h"
#include <QString>
#include <QFileInfo>
#include <QTextStream>
#include <stdlib.h>

SuperFileRemover::SuperFileRemover()
{
    srand(NULL);
}

SuperFileRemover::SuperFileRemover(unsigned int randomSeed)
{
    srand(randomSeed);
}

void SuperFileRemover::RemoveFile(QString fileName)
{
    QFileInfo info(fileName);
    qint64 fileSize = info.size();
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QTextStream out(&file);
    for (qint64 i = 0; i<=fileSize; i++)
        out << (char)(char)(rand()%('z'-'a')+'a');
    file.close();
    QFile::remove(fileName);
}
