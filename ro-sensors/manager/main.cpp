#include <QCoreApplication>
#include <qabstractanimation.h>

#include "rosensors_manager.h"

int main(int argc, char *argv[])
{
    rosensorsManager manager (argc, argv);
    return manager.exec();
}
