import QtQuick 2.0

Rectangle {

    id: button
    color:  Qt.rgba(0, 0, 0,1)
    signal pressed()
    width: 171

    Image {
        id: image1
        z: 2
        anchors.fill: parent
        visible: true
        source: "svgtoggle/square/berylsquare_off"
    }

    Image {
        id: image2
        anchors.fill: parent
        visible: false
        source: "svgtoggle/square/berylsquare_on"
    }

    MouseArea {
        id: mouseArea1
        enabled: true
        z: 1
        anchors.fill: parent

        onPressed: {
            if (button.state === "pressed") {
                button.state=""
            }else {
                button.state = "pressed"
                button.pressed()
            }
        }
    }

    states: [
        State {
            name: "pressed"

            PropertyChanges {
                target: image1
                visible: false
            }

            PropertyChanges {
                target: image2
                z: 3
                visible: true
            }

            PropertyChanges {
                target: mouseArea1
                z: 4
            }
        }
    ]

}
