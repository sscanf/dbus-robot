#/bin/bash

if [ "$1" == "clean" ]; then
	rm dualshock4manager_interface.*
	rm dualshock4manager_proxy.*
	rm com.robot.dualshock4manager.xml
	exit 0
fi

qdbuscpp2xml dualshock4_manager.h -o com.robot.dualshock4_manager.xml 
qdbusxml2cpp -N -c dualshock4ManagerInterface -a dualshock4manager_interface.h:dualshock4manager_interface.cpp com.robot.dualshock4_manager.xml
qdbusxml2cpp -N com.robot.dualshock4_manager.xml -p dualshock4manager_proxy.h:dualshock4manager_proxy.cpp

exit 0
