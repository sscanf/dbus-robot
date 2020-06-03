import QtQuick 2.0

Rectangle {
    property alias text: labelText.text
    signal pressed()

    id: robutton
    width: 77
    height: 26
    color: "#323232"
    radius: 5
    border.color: "#dddddd"

    Text {
        id: labelText
        x: 19
        y: 6
        color: "#dddddd"
        text: qsTr("Set")
        font.bold: true
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 12
    }
    MouseArea {
        anchors.fill: parent
        onPressed: {
            robutton.state="pressed";
        }
        onReleased: {
            robutton.state=""
            robutton.pressed()
        }
    }

    states: [
        State {
            name: "pressed"

            PropertyChanges {
                target: robutton
                color: "#f8f6f6"
            }

            PropertyChanges {
                target: labelText
                color: "#0d0c0c"
            }
        }
    ]

}
