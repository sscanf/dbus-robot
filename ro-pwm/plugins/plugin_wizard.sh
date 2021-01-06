#!/bin/bash

 . ../common/vars.inc

echo -n "Enter the plugin name: "
read name
echo -n "Enter the target path: $target "
read targetpath

if [ "$targetpath" ]; then
	target=$targetpath
fi

echo -n "Enter D-Bus Service Name [$name]: "
read servicename
if [ "$servicename" == "" ]; then
   servicename=$name
fi

uppername=`echo "$name" | tr '[:lower:]' '[:upper:]'`
lowername=`echo "$name" | tr '[:upper:]' '[:lower:]'`

result_path="$lowername"_plugin
mkdir -p $result_path
mkdir -p $result_path/proxy

for i in `ls template/template*`
do
	if [ "$i" != "$0" ] 
	then
		echo "Parsing file:  $basename $i"
		file=`echo $(basename $i) |sed -e s/template/$lowername/g`; 
		cat $i | sed -s s/@@@NAME@@@/$uppername/g > $result_path/"$file"_tmp1
		cat $result_path/"$file"_tmp1 | sed -s s/@@NAME@@/$name/g > $result_path/"$file"_tmp2
		cat $result_path/"$file"_tmp2 | sed -s s/@@manager_name@@/$manager_name/g > $result_path/"$file"_tmp8
		cat $result_path/"$file"_tmp8 | sed -s s/@@media@@/$manager_service/g > $result_path/"$file"_tmp9
		cat $result_path/"$file"_tmp9 | sed -s s/@@name@@/$lowername/g > $result_path/"$file"_tmp3
		cat $result_path/"$file"_tmp3 | sed -e "s|@@TARGET_PATH@@|$target|g" > $result_path/"$file"_tmp4
		cat $result_path/"$file"_tmp4 | sed -e "s|@@DBUS_SERVICENAME@@|$servicename|g" > $result_path/"$file"_tmp5
		mv $result_path/"$file"_tmp5 $result_path/$file
	fi
done 
	rm -f $result_path/*_tmp?

for i in `ls ../*.pro`
do
        echo "Found file : $basename $i"
        echo "plugins/$result_path  \\" >> $i
done
ln -s ../tools tools
