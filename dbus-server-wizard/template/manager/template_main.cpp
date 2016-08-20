#include <QCoreApplication>
#include <qabstractanimation.h>

#include "@@name@@_manager.h"

int main(int argc, char *argv[])
{
    @@name@@Manager manager (argc, argv);
    return manager.exec();
}
