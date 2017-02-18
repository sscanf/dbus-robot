#include "robotviewer_plugin.h"
#include "robotviewer.h"

#include <qqml.h>

void RobotViewerPlugin::registerTypes(const char *uri)
{
    // @uri com.robot.qmlcomponents
    qmlRegisterType<RobotViewer>(uri, 1, 0, "RobotViewer");
}

