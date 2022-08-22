import QtQuick 2.0

Rectangle {
    width: 1024
    height: 768
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#000000"
        }

        GradientStop {
            position: 1
            color: "#003944"
        }
    }

    Image {
        property int xPos: 50;
        property int yPos: 50;
        x: 502
        y: 374

        id: target
        objectName: "target"
        source: "target.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        x: 8
        y: 8
        color: "#5ee5fe"
        text: "Target position"
        font.pixelSize: 36
        font.bold: true
    }

    Text {
        property string label: "0"
        objectName: "posXLabel"
        id: posXLabel
        x: 8
        y: 55
        color: "#5ee5fe"
        text: "X: "+label
        font.pixelSize: 36
    }

    Text {
        property string label: "0"
        objectName: "posYLabel"
        id: posYLabel
        x: 8
        y: 102
        color: "#5ee5fe"
        text: "Y: "+label
        font.pixelSize: 36
        styleColor: "#5ee5fe"
    }

    Text {
        x: 736
        y: 8
        color: "#5ee5fe"
        text: "Camera position"
        font.pixelSize: 36
        font.bold: true
    }

    Text {
        property string label: "0"
        objectName: "posAzimut"
        id: posAzimut
        x: 736
        y: 55
        color: "#5ee5fe"
        text: "Azimut: "+label
        font.pixelSize: 36
    }

    Text {
        property string label: "0"
        objectName: "posElevation"
        id: posElevation
        x: 736
        y: 102
        color: "#5ee5fe"
        text: "Elevation: "+label
        font.pixelSize: 36
        styleColor: "#5ee5fe"
    }

    Rectangle {
        id: rectangle
        x: 502
        y: 374
        width: 20
        height: 20
        color: "#000000"
        border.color: "#fc2525"
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:3}
}
##^##*/
