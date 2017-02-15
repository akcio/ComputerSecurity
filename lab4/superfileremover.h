#ifndef SUPERFILEREMOVER_H
#define SUPERFILEREMOVER_H
#include <QString>

class SuperFileRemover
{
public:
    SuperFileRemover();
    SuperFileRemover(unsigned int randomSeed);
    void RemoveFile(QString fileName);
};

#endif // SUPERFILEREMOVER_H
