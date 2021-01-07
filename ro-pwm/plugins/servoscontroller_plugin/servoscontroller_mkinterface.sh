#/bin/bash

if [ "$1" == "clean" ]; then
	rm servoscontrollermanager_interface.*
	rm servoscontrollermanager_proxy.*
	rm com.robot.servoscontrollermanager.xml
	exit 0
fi

qdbuscpp2xml servoscontroller_manager.h -o com.robot.servoscontroller_manager.xml 
qdbusxml2cpp -N -c servoscontrollerManagerInterface -a servoscontrollermanager_interface.h:servoscontrollermanager_interface.cpp com.robot.servoscontroller_manager.xml
qdbusxml2cpp -N com.robot.servoscontroller_manager.xml -p servoscontrollermanager_proxy.h:servoscontrollermanager_proxy.cpp

exit 0
