#include <QCoreApplication>

#include "pwm_manager.h"

int main(int argc, char *argv[])
{
    pwmManager manager (argc, argv);
    return manager.exec();
}
