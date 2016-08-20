#include <QCoreApplication>
#include <qabstractanimation.h>

#include "roengines.h"

int main(int argc, char *argv[])
{
    roenginesManager manager (argc, argv);
    return manager.exec();
}
