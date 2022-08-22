import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.1
import com.robot.gradiente 1.0

Slider {
    id         : sliderVolume
    orientation: Qt.Vertical

    style: SliderStyle {
        handle: Image {
            x       : 5
            source  : "sliderbutton.svg"
            rotation: 90
            scale   : 1.5
        }

        groove: Rectangle {
            implicitWidth: 80
            implicitHeight: 15
            color : "black"
            Rectangle {
                y             : styleData.handlePosition
                color         : "gray"
                anchors.bottom: parent.bottom
                anchors.right : parent.right
                anchors.left  : parent.left
                height        : 1
            }

            Rectangle {
                width: styleData.handlePosition
                height: parent.height - 5
                anchors.verticalCenter: parent.verticalCenter
                gradient: Gradient {
                    GradientStop {
                        position: 0.07;
                        color: "#0593ff";
                    }
                    GradientStop {
                        position: 0.48;
                        color: "#ffffff";
                    }
                    GradientStop {
                        position: 1.00;
                        color: "#0593ff";
                    }
                }
                MouseArea {
                    anchors.fill: parent.fill
                    z: 99
                    onPressed : {
                        value = 0;
                    }
                }
            }
        }
    }
}
