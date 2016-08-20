# dbus-robot
Modules to control a hardware robot.

Each module is a micro-service written with Qt.
Communication between modules is via D-Bus.

Each module has a role, such as controlling the engines, or tracking objects via opencv.
The names of the modules have the following format: ro-<role>
All names begins with ro (robot) following a '-' and the name of the role, for exemple,
if a module controls the engines, the name is: ro-engines

Modules structure:

Each module is composed of a manager and plugins. The manager is the service itself (core)
and its function is to load all available plugins.

In /etc/robot/ there is a XML configuration file in which all modules are defined to be loaded 
along with its parameters. The name of this file have the following format:
<name-of-service>-config.xml

Normally all plugins are installed in /usr/lib/





