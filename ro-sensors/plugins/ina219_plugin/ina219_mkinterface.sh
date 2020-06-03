#/bin/bash

if [ "$1" == "clean" ]; then
	rm ina219manager_interface.*
	rm ina219manager_proxy.*
	rm com.robot.ina219manager.xml
	exit 0
fi

qdbuscpp2xml ina219_manager.h -o com.robot.ina219_manager.xml 
qdbusxml2cpp -N -c ina219ManagerInterface -a ina219manager_interface.h:ina219manager_interface.cpp com.robot.ina219_manager.xml
qdbusxml2cpp -N com.robot.ina219_manager.xml -p ina219manager_proxy.h:ina219manager_proxy.cpp

exit 0
