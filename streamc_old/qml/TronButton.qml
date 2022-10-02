import QtQuick 2.10
import QtGraphicalEffects 1.0

Item {
    id: boton
    signal clicked();
    property alias text: text1.text

    Image {
        id: image
        x: 0
        y: 0
        width: 337
        height: 109
        source: "qrc://boton.png"
        fillMode: Image.PreserveAspectFit

        Text {
            id: text1
            x: 42
            y: 35
            width: 215
            height: 37
            color: "#5ee5fe"
            font.pixelSize: 30
            font.bold: true

            layer {
                 enabled: mouseArea.containsMouse
                 effect: Glow {
                     radius: 10
                     samples: 17
                     color: "green"
                 }
            }
            MouseArea {
                id: mouseArea
                hoverEnabled: true
                anchors.fill: parent
            }
        }

        Image {
            id: ledOff
            x: 263
            y: 36
            opacity: 1
            source: "ledgreen_off.svg"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: ledOn
            x: 263
            y: 36
            opacity: 0
            source: "ledgreen_on.svg"
            fillMode: Image.PreserveAspectFit
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            boton.clicked();
        }
    }

    states: [
        State {
            name: "LedOn"
            PropertyChanges { target: ledOff; opacity: 0 }
            PropertyChanges { target: ledOn;  opacity: 1 }
        }
    ]

    transitions: [
        Transition {
            from: ""
            to: "LedOn"
            OpacityAnimator{ target: ledOff; duration: 1000}
        }
    ]
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:1.100000023841858;height:480;width:640}
}
##^##*/
