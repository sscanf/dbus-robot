import QtQuick 2.0
import com.robot.gradiente 1.0
import QtQuick.Controls 1.0

Rectangle {
    property int maxSpeed
    signal setPressed()

    id: panel
    color: "black"
    radius: 10
    width: 600
    height: 400

        SpeedGauge {
            id: leftMotor
            width: 300
            height: 300
            objectName: "leftMotor"
            maxWarning: 149
            minWarning: 0
            maxValue:170
            labelStep: 10
        }

        SpeedGauge {
            width: 300
            height:300
            id: rightMotor
            x: 300
            y: 0
            objectName: "rightMotor"
            maxWarning: 149
            minWarning: 0
            maxValue:170
            labelStep: 10
        }

    Text {
        id: element1
        x: 101
        y: 302
        color: "white"
        text: qsTr("Left Motor")
        font.pixelSize: 20
    }

    Text {
        id: element2
        x: 401
        y: 302
        color: "white"
        text: qsTr("Right Motor")
        font.pixelSize: 20
    }

    Gradiente {
            x             : 0
            y             : 340
            width         : parent.width
            height        : 1
            colores       : ["#4f4f4fFF", "#ffffffFF", "#4f4f4fFF"]
            puntos        : [0.0 , 0.5, 1.0]
            puntoInicial.x: 0.0
            puntoInicial.y: 0.5
            puntoFinal.x  : 1.0
            puntoFinal.y  : 0.5
    }

    TextInput {
        id: maximumSpeed
        objectName: "maximumSpeed"
        x: 162
        y: 366
        color: "white"
        anchors.verticalCenterOffset: 172
        anchors.horizontalCenterOffset: -113
        selectionColor: "green"
        font.pixelSize: 15
        font.bold: true
        width: 50
        height: 20
        maximumLength: 15
        anchors.centerIn: parent
        focus: true
        text: "50"
    }

    Text {
        id: element3
        x: 41
        y: 362
        color: "white"
        text: qsTr("Maximum speed:")
        font.pixelSize: 15
    }

    ROButton {
        x: 202
        y: 358
        text: "Set"
        onPressed: {
            maxSpeed = maximumSpeed.text
            panel.setPressed()
        }
    }

}
