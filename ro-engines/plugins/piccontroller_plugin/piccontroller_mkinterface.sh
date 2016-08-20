#/bin/bash

if [ "$1" == "clean" ]; then
	rm piccontrollermanager_interface.*
	rm piccontrollermanager_proxy.*
	rm com.zitro.zone.piccontrollermanager.xml
	exit 0
fi

qdbuscpp2xml piccontroller_manager.h -o com.zitro.zone.piccontroller_manager.xml 
qdbusxml2cpp -N -c piccontrollerManagerInterface -a piccontrollermanager_interface.h:piccontrollermanager_interface.cpp com.zitro.zone.piccontroller_manager.xml
qdbusxml2cpp -N com.zitro.zone.piccontroller_manager.xml -p piccontrollermanager_proxy.h:piccontrollermanager_proxy.cpp

exit 0
