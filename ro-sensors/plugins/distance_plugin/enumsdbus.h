#ifndef _ENUM_DBUS_HPP
#define _ENUM_DBUS_HPP

#include <QtDBus/QDBusArgument>

#define DECLARE_ENUM_DATATYPE(ENUM_TYPE_DBUS)\
     QDBusArgument &operator<<(QDBusArgument &argument, ENUM_TYPE_DBUS value);\
     const QDBusArgument &operator>>(const QDBusArgument &argument, ENUM_TYPE_DBUS &val);


#define CREATE_ENUM_DATATYPE(ENUM_TYPE_DBUS)\
     QDBusArgument &operator<<(QDBusArgument &argument, ENUM_TYPE_DBUS value)\
     {\
         argument.beginStructure();\
         qlonglong newVal = (qlonglong)value;\
         argument << newVal;\
         argument.endStructure();\
         return argument;\
     }\
     const QDBusArgument &operator>>(const QDBusArgument &argument, ENUM_TYPE_DBUS &val)\
     {\
         argument.beginStructure();\
         qlonglong result = 0;\
         argument >> result;\
         val = (ENUM_TYPE_DBUS)result;\
         argument.endStructure();\
         return argument;\
     }

#endif
