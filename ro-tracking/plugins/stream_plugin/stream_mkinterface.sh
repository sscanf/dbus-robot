#/bin/bash

if [ "$1" == "clean" ]; then
	rm streammanager_interface.*
	rm streammanager_proxy.*
	rm com.zitro.zone.streammanager.xml
	exit 0
fi

qdbuscpp2xml stream_manager.h -o com.zitro.zone.stream_manager.xml 
qdbusxml2cpp -N -c streamManagerInterface -a streammanager_interface.h:streammanager_interface.cpp com.zitro.zone.stream_manager.xml
qdbusxml2cpp -N com.zitro.zone.stream_manager.xml -p streammanager_proxy.h:streammanager_proxy.cpp

exit 0
