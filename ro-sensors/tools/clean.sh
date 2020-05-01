#!/bin/bash
find /home/oscar/trabajo/z-one-zitro/DBus/zoinput_server -type f -name "*.xml" -exec rm {} \;
find /home/oscar/trabajo/z-one-zitro/DBus/zoinput_server -type d -name "proxy" -exec rm {} -rfv \;
find /home/oscar/trabajo/z-one-zitro/DBus/zoinput_server -type f -name "*_interface.*" -exec rm {} -rfv \;

