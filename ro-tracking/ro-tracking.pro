DEFINES += QT_DEPRECATED_WARNINGS
TEMPLATE = subdirs
SUBDIRS += $$PWD/manager/rotracking.pro\
           plugins/balltracker_plugin  \
           plugins/irtracker_plugin    \

#plugins/stream_plugin  \
