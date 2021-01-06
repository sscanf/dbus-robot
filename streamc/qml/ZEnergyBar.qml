import QtQuick 2.0
import "commons.js" as GData

Rectangle {
    id          : energyBar
    height      : 60
    width       : 200
    radius      : 4
    color       : "transparent"
    border.color: "gray"
    border.width: 2
    state       : "init"

    property string orientation     : "horizontal"
    property string labelColor      : "white"
    property string valueColor      : "white"
    property real   currentValue                   //The current value used to calculate the "power on" LEDs
    property real   barValue        : currentValue //The value to show in white characters on the LED bar (by default, same than currentValue)
    property int    resolution                     //Number of decimal positions to show in the bar value (even if they are equal to 0)
    property string units                          //The units (if any) to be shown in the LED bar, together with barValue (examples: "GB, "%", "ms"...)
    property string label                          //The descriptive label to be shown next to the LED bar.
    property int    numLeds         : 20           //Minimum value for number of LEDs must be 10
    property real   maxValue                       //Maximum value that the LED bar can represent
    property real   minValue        : 0            //Minimum value that the LED bar can represent (0 by default)
    property real   percentValue                   //% of LED bar that shaould be "power on"
    property int    separation      : border.width //Separation among LED items in pixels
    property real   warningThreshold: 0.60         //Point where green LEDs turn yellow LEDs. Value must be relative between 0 and 1
    property real   dangerThreshold : 0.90         //Point where yelow LEDs turn red LEDs. Value must be relative between 0 and 1
    property bool   showValue       : true
    property real   maxMarker       : -1
    property int    altura: (energyBar.height- (2*separation) - ((numLeds+1)*separation)) / numLeds

    signal clicked()

    onCurrentValueChanged: { percentValue = (currentValue / (maxValue - minValue)).toFixed(2) }

    MouseArea {
        anchors.fill: parent
        onClicked   : { energyBar.clicked(); }
    }

    Rectangle {
        id                    : labelRect
        height                : parent.height
        width                 : labelText.width
        color                 : Qt.rgba(0, 0, 0, 0)
        visible               : label !== "" ? true : false
        anchors.right         : energyBar.left
        anchors.rightMargin   : 20
        anchors.verticalCenter: parent.verticalCenter

        Text {
            id              : labelText
            color           : labelColor
            text            : label !== "" ? (label + ":") : ""
            font.bold       : true
            font.pixelSize  : GData.TEXT_SIZE
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id      : marker
        color   : "yellow"
        width   : parent.width-4 //energyBar.width- 4 * energyBar.border.width
        height  : altura*0.15
        anchors.horizontalCenter: parent.horizontalCenter
        x       : (orientation=="horizontal") ? parent.width - (maxMarker*numLeds+1)*width  : rect.x
        y       : (orientation=="vertical")   ? parent.height - ((maxMarker*numLeds+1)*altura) : altura*separation
    }

    onPercentValueChanged: {
        if (percentValue > maxMarker) {
            maxMarker=percentValue;
            anim.restart();
        }
    }

    Row {
        spacing           : separation
        anchors.fill      : parent
        anchors.leftMargin: separation*2
        Repeater {
            model      : numLeds
            delegate   : Rectangle {
                visible: orientation == "horizontal" ? true : false
                y      : separation*2
                height : energyBar.height - 4 * energyBar.border.width
                width  : (energyBar.width - (2*separation) - ((numLeds+1)*separation)) / numLeds
                color  : (index/numLeds) < warningThreshold ? (index/numLeds) < percentValue ? Qt.rgba(0, 0.7, 0, 0.8) : Qt.rgba(0, 0.4, 0, 0.25) :
                         (index/numLeds) < dangerThreshold ? (index/numLeds) < percentValue ? Qt.rgba(0.9, 0.9, 0, 0.8) : Qt.rgba(0.5, 0.5, 0, 0.25) :
                         (index/numLeds) < percentValue ? Qt.rgba(0.8, 0, 0, 0.8) : Qt.rgba(0.5, 0, 0, 0.25)
            }
        }
    }

    Column {
        anchors.fill  : parent
//        anchors.bottom: separation*2
        spacing       : separation
        rotation      : 180
        Repeater {
            id      : rect
            model   : numLeds
            delegate: Rectangle {
                visible : orientation == "vertical" ? true : false
                x       : separation*2
                width   : parent.width-4 //energyBar.width- 4 * energyBar.border.width
                height  : (energyBar.height- (2*separation) - ((numLeds+1)*separation)) / numLeds
                color   : (index/numLeds) < warningThreshold ? (index/numLeds) < percentValue ? Qt.rgba(0, 0.7, 0, 1)   : Qt.rgba(0, 0.4, 0, 0.25) :
                          (index/numLeds) < dangerThreshold  ? (index/numLeds) < percentValue ? Qt.rgba(0.9, 0.9, 0, 1) : Qt.rgba(0.5, 0.5, 0, 0.25) :
                          (index/numLeds) < percentValue     ? Qt.rgba(0.8, 0, 0, 1) : Qt.rgba(0.5, 0, 0, 0.25)
            }
        }
    }

    Rectangle {
        height          : parent.height * 0.75
        width           : parent.width
        color           : "transparent"
        anchors.centerIn: parent
        visible         : showValue

        Text {
            id              : barText
            text            : barValue.toFixed(resolution) + " " + units
            color           : valueColor
            height          : parent.height
            style           : Text.Outline
            styleColor      : "black"
            font.bold       : true
            font.pixelSize  : GData.TEXT_SIZE
            anchors.centerIn: parent
        }
    }

    SequentialAnimation {
        id            : anim
        running       : false
        alwaysRunToEnd: true
        PauseAnimation  { duration: 500 }
        NumberAnimation { target: marker;    property: "y"; from: (orientation=="vertical") ? parent.height - ((maxMarker*numLeds+1)*altura) : altura*separation; to: parent.height; duration: 500 }
        PropertyAction  { target: energyBar; property: "maxMarker"; value: -1 }
    }
}

/*##^##
Designer {
    D{i:0;height:60;width:200}
}
##^##*/
