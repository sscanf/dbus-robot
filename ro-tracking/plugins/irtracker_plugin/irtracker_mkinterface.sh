#/bin/bash

if [ "$1" == "clean" ]; then
	rm balltrackermanager_interface.*
	rm balltrackermanager_proxy.*
	rm com.zitro.zone.balltrackermanager.xml
	exit 0
fi

qdbuscpp2xml balltracker_manager.h -o com.zitro.zone.balltracker_manager.xml 
qdbusxml2cpp -N -c balltrackerManagerInterface -a balltrackermanager_interface.h:balltrackermanager_interface.cpp com.zitro.zone.balltracker_manager.xml
qdbusxml2cpp -N com.zitro.zone.balltracker_manager.xml -p balltrackermanager_proxy.h:balltrackermanager_proxy.cpp

exit 0
