/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -N -c roenginesInterface -a roengines_interface.h:roengines_interface.cpp com.robot.roengines.xml
 *
 * qdbusxml2cpp is Copyright (C) 2020 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef ROENGINES_INTERFACE_H
#define ROENGINES_INTERFACE_H

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE

/*
 * Adaptor class for interface com.robot.roengines
 */
class roenginesInterface: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.robot.roengines")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"com.robot.roengines\">\n"
"    <method name=\"getVersion\">\n"
"      <arg direction=\"out\" type=\"s\"/>\n"
"    </method>\n"
"    <method name=\"getObjects\">\n"
"      <arg direction=\"out\" type=\"as\"/>\n"
"    </method>\n"
"    <method name=\"getObjectsByType\">\n"
"      <arg direction=\"out\" type=\"as\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"strType\"/>\n"
"    </method>\n"
"    <method name=\"getObjectsByName\">\n"
"      <arg direction=\"out\" type=\"as\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"strName\"/>\n"
"    </method>\n"
"  </interface>\n"
        "")
public:
    roenginesInterface(QObject *parent);
    virtual ~roenginesInterface();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    QStringList getObjects();
    QStringList getObjectsByName(const QString &strName);
    QStringList getObjectsByType(const QString &strType);
    QString getVersion();
Q_SIGNALS: // SIGNALS
};

#endif