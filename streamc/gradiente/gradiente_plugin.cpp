#include "gradiente_plugin.h"
#include "gradiente.h"

#include <qqml.h>

void GradientePlugin::registerTypes(const char *uri)
{
    // @uri com.robot.gradiente
    qmlRegisterType<Gradiente>(uri, 1, 0, "Gradiente");
}
