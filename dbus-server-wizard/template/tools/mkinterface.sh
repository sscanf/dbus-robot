#!/bin/bash
target=$1

echo "target = $target"

echo "========== TESTING <$target> =========="

STAT1=$(stat --format "%Y" $target.h 2>/dev/null)
STAT2=$(stat --format "%Y" com.zitro.zone.$target.xml 2>/dev/null)

let STAT1=STAT1+10
let STAT2=STAT2+10

(! test -e proxy/)    && mkdir proxy/ 2>/dev/null
(! test -e proxy/cpp) && mkdir proxy/cpp 2>/dev/null

( test -e "$target"_interface.h)
interface_exists=$?
( test -e "$target"_interface.cpp)
let interface_exists=$interface_exists+$?

( test -e proxy/"$target"_proxy.h)
proxy_exists=$?
( test -e proxy/"$target"_proxy.cpp)
let proxy_exists="$proxy"_exists+$?

echo "proxy_exists = $proxy_exists"
if [ $STAT1 -gt $STAT2 ] || [ $STAT1 -eq 10 ] || [ $STAT2 -eq 10 ] || [ $interface_exists -gt 0 ] || [ $proxy_exists -gt 0 ]; then
        echo "========== BUILDING PROXY FILES <$target> =========="
        qdbuscpp2xml $target.h -o com.zitro.zone.$target.xml
        qdbusxml2cpp -N -c "$target"Interface -a "$target"_interface.h:"$target"_interface.cpp com.zitro.zone.$target.xml
        qdbusxml2cpp -N -c "$target"Interface com.zitro.zone.$target.xml -p "$target"_proxy.h:"$target"_proxy.cpp
        mv *_proxy* ./proxy/

        dbusxx-xml2cpp com.zitro.zone.$target.xml --proxy=./proxy/cpp/"$target"_proxy.h
fi

echo "Done"
