import QtQuick 2.0

Rectangle {

    id: button
    color:  Qt.rgba(0, 0, 0,1)
    signal pressed()


    Image {
        id: image2
        visible: false
        anchors.fill: parent
        source: "svgbutton/square/svgbutton/BerylSquare/pressed.svg"
    }


    Image {
        id: image1
        visible: true
        anchors.fill: parent
        source: "svgbutton/square/svgbutton/BerylSquare/normal.svg"
    }


    states: [
        State {
            name: "pressed"

            PropertyChanges {
                target: image2
                visible: true
            }

            PropertyChanges {
                target: image1
                visible: false
            }
        }
    ]

    MouseArea {
        id: mouseArea1
        z: 1
        anchors.fill: parent

        onPressed: {
            button.state = "pressed"
            button.pressed()
        }
        onReleased: {
            button.state = ""
        }
    }
}
