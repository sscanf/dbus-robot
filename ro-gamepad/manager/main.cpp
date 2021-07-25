#include <QCoreApplication>
#include <qabstractanimation.h>
#include "gamepad_manager.h"

int main(int argc, char *argv[])
{
    setenv("QT_GAMEPAD", "sdl2",1);
    gamepadManager manager (argc, argv);
    return manager.exec();
}
