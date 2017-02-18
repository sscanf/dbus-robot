import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import com.robot.qmlcomponents 1.0
import org.jemc.qml.Sockets 1.0

Item {
    property int highH: 100
    property int lowH : 0
    property int highS: 255
    property int lowS : 92
    property int highV: 255
    property int lowV : 105

    id    : item1
    width : 900
    height: 759

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin       : 20
        anchors.top             : parent.top

        RobotViewer {
            id    : robot
            width : 640
            height: 480
        }
    }

    RowLayout {
        x: 241
        y: 506
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 30
        opacity: 1

        ColumnLayout {
            Text {
                text: qsTr("Low H")
                font.pixelSize: 12
            }
            Slider {
                id          : sliderLowH
                stepSize    : 1
                maximumValue: 255
                Layout.preferredHeight: 192
                Layout.preferredWidth: 40
                orientation: Qt.Vertical
                value: lowH;
                onValueChanged: {
                    robot.lowH= sliderLowH.value
                }
            }
            Text {
                id: sliderLowhValu
                text:  sliderLowH.value
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
               font.pixelSize: 12
            }
        }
        ColumnLayout {
            Text {
                text: qsTr ("High H")
                font.pixelSize: 12
            }
            Slider {
                id: sliderHighH
                stepSize: 1
                maximumValue: 255
                Layout.preferredHeight: 192
                Layout.preferredWidth: 40
                orientation: Qt.Vertical
                value: highH
                onValueChanged: {
                    robot.highH= sliderHighH.value
                }
            }
            Text {
                id: sliderHighHValue
                text: sliderHighH.value
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 12
            }
        }
        ColumnLayout {
            Text {
                text: qsTr ("Low S")
                font.pixelSize: 12
            }
            Slider {
                id:  sliderLowS
                maximumValue: 255
                stepSize: 1
                Layout.preferredHeight: 192
                Layout.preferredWidth: 40
                orientation: Qt.Vertical
                value: lowS
                onValueChanged: {
                    robot.lowS= sliderLowS.value
                }
            }
            Text {
                id  : sliderLowSValue
                text: sliderLowS.value
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }
        }
        ColumnLayout {
            Text {
                text: qsTr ("High S")
                font.pixelSize: 12
            }
            Slider {
                id: sliderHighS
                stepSize: 1
                maximumValue: 255
                Layout.preferredHeight: 192
                Layout.preferredWidth: 40
                orientation: Qt.Vertical
                value: highS
                onValueChanged: {
                    robot.highS= sliderHighS.value
                }
            }
            Text {
                id: sliderHighSValue
                text: sliderHighS.value
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 12
            }
        }
        ColumnLayout {
            Text {
                text: qsTr ("Low V")
                font.pixelSize: 12
            }
            Slider {
                id: sliderLowV
                stepSize: 1
                maximumValue: 255
                Layout.preferredHeight: 192
                Layout.preferredWidth: 40
                orientation: Qt.Vertical
                value: lowV
                onValueChanged: {
                    robot.lowV= sliderLowV.value
                }
            }
            Text {
                id: slidwrLowVValue
                text: sliderLowV.value
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 12
            }
        }
        ColumnLayout {
            Text {
                text: qsTr ("High V")
                font.pixelSize: 12
            }
            Slider {
                id: sliderHighV
                stepSize: 1
                maximumValue: 255
                Layout.preferredHeight: 192
                Layout.preferredWidth: 40
                orientation: Qt.Vertical
                value: highV
                onValueChanged: {
                    robot.highV= sliderHighV.value
                }
            }
            Text {
                id: sliderHighVValue
                text: sliderHighV.value
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 12
            }
        }
    }
}
