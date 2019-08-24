#include <QCoreApplication>
#include "robotworker.h"
int main(int argc, char *argv[])
{
    robotWorker worker (argc, argv);
    return worker.exec();
}
