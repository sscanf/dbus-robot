# vim: set syntax=on:
#!/bin/bash

echo -n "Enter the server name: "
read name
echo -n "Enter project path: $(pwd): "
read project_path

echo -n "Enter the target path: /usr/lib/"
read target
target="/usr/lib/$name/$target"

echo -n "Enter D-Bus Service Name: "
read servicename

uppername=`echo "$name" | tr '[:lower:]' '[:upper:]'`
lowername=`echo "$name" | tr '[:upper:]' '[:lower:]'`
result_parent="$(echo $lowername)_server"
result_path="$result_parent/manager"
plugins_path="$result_parent/plugins"
common_path="$result_parent/common"

mkdir -p $result_path
mkdir -p $plugins_path
mkdir -p $common_path
#cp template/template.pro $result_parent
cp template/plugins/* $plugins_path -Rp
cp template/tools/ $result_parent -Rp
#cp template/common/ $common_path -Rp

mkdir -p $result_path/proxy
mkdir -p $result_path/services
mkdir -p $result_path/system.d

if [ -z "$project_path" ]; then
	project_path=$(pwd)
fi

for i in `ls template/manager/template* template/common/* template/template.pro template/manager/services/com.robot.servicename.service template/manager/system.d/com.robot.servicename.conf`
do
	if [ "$i" != "$0" ]; then 

		file=`echo $(basename $i) |sed -e s/template/$lowername/g |sed -e s/servicename/$servicename/g`;
		path=`dirname $i | sed -e s/template/$(echo $lowername)_server/g`
		
		echo "Parsing file:  $file"

		cat $i | sed -s s/@@NAME@@/$uppername/g > $path/$file
		sed -i "s|@@name@@|$lowername|g" $path/$file
		sed -i "s|@@TARGET_PATH@@|$target|g" $path/$file
		sed -i "s|@@DBUS_SERVICENAME@@|$servicename|g" $path/$file
		sed -i "s|@@project_path@@|$project_path|g" $path/$file
	fi
done 

mv $result_path/$(echo $lowername)_main.cpp $result_path/main.cpp
