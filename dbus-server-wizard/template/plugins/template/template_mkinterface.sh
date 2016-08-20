#/bin/bash

if [ "$1" == "clean" ]; then
	rm @@name@@manager_interface.*
	rm @@name@@manager_proxy.*
	rm com.zitro.zone.@@name@@manager.xml
	exit 0
fi

qdbuscpp2xml @@name@@_manager.h -o com.zitro.zone.@@name@@_manager.xml 
qdbusxml2cpp -N -c @@name@@ManagerInterface -a @@name@@manager_interface.h:@@name@@manager_interface.cpp com.zitro.zone.@@name@@_manager.xml
qdbusxml2cpp -N com.zitro.zone.@@name@@_manager.xml -p @@name@@manager_proxy.h:@@name@@manager_proxy.cpp

exit 0
