#include <QCoreApplication>
#include <qabstractanimation.h>

#include "rosensors_manager.h"

int main(int argc, char *argv[])
{
    setenv("QT_GAMEPAD", "sdl2",1);
    rosensorsManager manager (argc, argv);
    return manager.exec();
}
