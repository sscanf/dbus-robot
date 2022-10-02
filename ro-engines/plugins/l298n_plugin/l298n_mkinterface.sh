#/bin/bash

if [ "$1" == "clean" ]; then
	rm l298nmanager_interface.*
	rm l298nmanager_proxy.*
	rm com.zitro.zone.l298nmanager.xml
	exit 0
fi

qdbuscpp2xml l298n_manager.h -o com.zitro.zone.l298n_manager.xml 
qdbusxml2cpp -N -c l298nManagerInterface -a l298nmanager_interface.h:l298nmanager_interface.cpp com.zitro.zone.l298n_manager.xml
qdbusxml2cpp -N com.zitro.zone.l298n_manager.xml -p l298nmanager_proxy.h:l298nmanager_proxy.cpp

exit 0
