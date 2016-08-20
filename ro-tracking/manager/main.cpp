#include <QCoreApplication>
#include "rotracking_manager.h"

int main(int argc, char *argv[])
{
    rotrackingManager manager (argc, argv);
    return manager.exec();
}
