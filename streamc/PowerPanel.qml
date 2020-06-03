import QtQuick 2.0
import com.robot.gradiente 1.0
import "commons.js" as GData

Rectangle {
    width: 730
    height: 400
    color: "#000000"

    ZEnergyBar {
        id: robotCapacity
        x: 123
        y: 75
        units: "%"
        objectName: "robotCapacity"
        warningThreshold: 1
        numLeds: 10
        label: "Capacity"
        resolution: 1
        maxValue: 100
    }


    ZEnergyBar {
        id: voltage
        objectName: "voltage"
        x: 123
        y: 149
        numLeds: 10
        warningThreshold: 1
        label: "Voltage"
        maxValue: 17
        resolution: 1
        units: "V"
    }

    ZEnergyBar {
        id: current
        numLeds: 10
        objectName: "current"
        x: 123
        y: 221
        maxValue: 3700
        minValue: 0
        label: "Current"
        resolution: 1
        units: "mA"
    }

    ZEnergyBar {
        id: power
        numLeds: 10
        objectName: "power"
        x: 123
        y: 293
        maxValue: 60
        label: "Power"
        resolution: 1
        units: "W"
    }

    Text {
        id: element
        x: 104
        y: 14
        width: 168
        height: 36
        color: "#ffffff"
        text: qsTr("Robot Battery")
        font.pixelSize: 24
    }

    Gradiente {
        x             : 340
        y             : 0
        width         : 1
        height        : parent.height
        colores       : ["#4f4f4fFF", "#ffffffFF", "#4f4f4fFF"]
        puntos        : [0.0 , 0.5, 1.0]
        puntoInicial.x: 0.5
        puntoInicial.y: 0.0
        puntoFinal.x  : 0.5
        puntoFinal.y  : 1.0
    }

    Text {
        id: element1
        x: 468
        y: 14
        width: 198
        height: 36
        color: "#ffffff"
        text: qsTr("Gamepad Battery")
        font.pixelSize: 24
    }

    Text {
        x: 391
        y: 200
        width: 82
        height: 36
        color: "#ffffff"
        text: qsTr("Status :")
        font.bold       : true
        font.pixelSize  : GData.TEXT_SIZE
        style           : Text.Outline
    }

    ZEnergyBar {
        id: capacity
        numLeds: 10
        objectName: "capacity"
        x: 494
        y: 75
        warningThreshold: 1
        dangerThreshold: 0.9
        units: "%"
        maxValue: 100.0
        minValue: 0
        label: "Capacity"
        resolution: 1
    }


    Text {
        id: status
        objectName: "status"
        x: 484
        y: 200
        width: 82
        height: 36
        color: "#ffffff"
        text: qsTr("n/a")
        font.bold       : true
        font.pixelSize  : GData.TEXT_SIZE
        style           : Text.Outline
    }


}
