import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    property string strMessage

    id     : mainWindow
    color  : "black"
    visible: true
    width  : 1280
    height : 480

    //A background decorative image with a MouseArea that closes the file list on clicked
    Image {
        id: background
        source: "background.jpg"
        anchors.centerIn: parent

        SequentialAnimation on scale {
            loops: Animation.Infinite
            PropertyAnimation { from: 1;   to: 1.3; duration: 10000; easing.type: "InOutQuad" }
            PropertyAnimation { from: 1.3; to: 1;   duration: 10000; easing.type: "InOutQuad" }
        }

        MouseArea {
            anchors.fill: background
            onClicked: {
                rectMessage.state = "folded";
            }
        }
    }

    //The container for the title of the error message
    Rectangle {
        id: rectTitle
        x: 0
        y : 7
        width : 1280
        height: 72
        color : "#d88c0000"

        Text {
            id: textTitle
            x : 521
            y : 17
            color: "#fdfdfd"
            text: "ROBOT FIRMWARE UPDATER"
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter  : parent.verticalCenter
            }
            font {
                weight: Font.Bold
                pixelSize: 34
            }
        }

        Rectangle {
            id: blackRectange
            x: 8
            y: 259
            width: 1272
            height: 82
            color: "#000000"

            Text {
                id: textTitle1
                x: 515
                y: 18
                color: "#00ff0b"
                text: strMessage
                anchors.centerIn: parent
                font.pixelSize: 34
                font.weight: Font.Bold
            }
        }
    }

    function setText (text) {
        strMessage = text;
    }
}
