#/bin/bash

if [ "$1" == "clean" ]; then
	rm facetrackermanager_interface.*
	rm facetrackermanager_proxy.*
	rm com.zitro.zone.facetrackermanager.xml
	exit 0
fi

qdbuscpp2xml facetracker_manager.h -o com.zitro.zone.facetracker_manager.xml 
qdbusxml2cpp -N -c facetrackerManagerInterface -a facetrackermanager_interface.h:facetrackermanager_interface.cpp com.zitro.zone.facetracker_manager.xml
qdbusxml2cpp -N com.zitro.zone.facetracker_manager.xml -p facetrackermanager_proxy.h:facetrackermanager_proxy.cpp

exit 0
