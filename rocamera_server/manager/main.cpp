#include <QCoreApplication>

#include "rocamera_manager.h"

int main(int argc, char *argv[])
{
    rocameraManager manager (argc, argv);
    return manager.exec();
}
