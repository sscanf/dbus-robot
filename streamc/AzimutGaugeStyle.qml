import QtQuick 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

CircularGaugeStyle{

    property bool halfGauge     : false;
    property real xCenter       : outerRadius
    property real yCenter       : outerRadius
    property int minimumWarning : 0
    property int maximumWarning : 150
    property string strUnids    : "rpm"

    tickmarkInset       : toPixels (0.04);
    minorTickmarkInset  : tickmarkInset
    labelStepSize       : 5
    labelInset          : toPixels(0.23)
    minimumValueAngle   : 0
    maximumValueAngle   : 360

    function toPixels(percentage) {
        return percentage * outerRadius;
    }

    function degToRad(degrees) {
        return degrees * (Math.PI / 180);
    }

    function radToDeg(radians) {
        return radians * (180 / Math.PI);
    }


    function paintBackground(ctx) {
        if (halfGauge) {
            ctx.beginPath();
            ctx.rect(0, 0, ctx.canvas.width, ctx.canvas.height / 2);
            ctx.clip();
        }
        ctx.beginPath();
        ctx.fillStyle = "black";
        ctx.ellipse(0, 0, ctx.canvas.width, ctx.canvas.height);
        ctx.fill();

        ctx.beginPath();
        ctx.lineWidth = tickmarkInset;
        ctx.strokeStyle = "black";
        ctx.arc(xCenter, yCenter, outerRadius - ctx.lineWidth / 2, outerRadius - ctx.lineWidth / 2, 0, Math.PI * 2);
        ctx.stroke();

        ctx.beginPath();
        ctx.lineWidth = tickmarkInset / 2;
        ctx.strokeStyle = "#222";
        ctx.arc(xCenter, yCenter, outerRadius - ctx.lineWidth / 2, outerRadius - ctx.lineWidth / 2, 0, Math.PI * 2);
        ctx.stroke();

        ctx.beginPath();
        var gradient = ctx.createRadialGradient(xCenter, yCenter, outerRadius * 0.8, xCenter, yCenter, outerRadius);
        gradient.addColorStop(0, Qt.rgba(1, 1, 1, 0));
        gradient.addColorStop(0.7, Qt.rgba(1, 1, 1, 0.13));
        gradient.addColorStop(1, Qt.rgba(1, 1, 1, 1));
        ctx.fillStyle = gradient;
        ctx.arc(xCenter, yCenter, outerRadius - tickmarkInset, outerRadius - tickmarkInset, 0, Math.PI * 2);
        ctx.fill();


    }

    tickmark            : Rectangle {
        implicitWidth   : toPixels(0.03)
        antialiasing    : true
        implicitHeight  : toPixels(0.08)
        color           : styleData.value < minimumWarning  ? Qt.rgba (0, 0, 0.5, 1) :
                          styleData.value > maximumWarning ? Qt.rgba (0.5, 0, 0, 1) :
                          "#c8c8c8"
    }


    minorTickmark       : Rectangle {
        implicitWidth   : toPixels(0.01)
        antialiasing    : true
        implicitHeight  : toPixels(0.04)

        color           : styleData.value < minimumWarning  ? Qt.rgba (0, 0, 0.5, 1) :
                          styleData.value > maximumWarning ? Qt.rgba (0.5, 0, 0, 1) :
                          "#c8c8c8"
    }

    background: Canvas {
        onPaint : {
            var ctx = getContext ("2d");
            ctx.reset();
            paintBackground(ctx);
        }

        Text {
            id                      : speedText
            font.pixelSize          : toPixels(0.3)
            text                    : value.toFixed(2)
            color                   : "#efb139"
            horizontalAlignment     : Text.AlignRight
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top             : parent.verticalCenter
            anchors.topMargin       : toPixels(0.2)

//            readonly property real kphInt: control.value
        }

        Text {
            id                      : unidsText
            horizontalAlignment     : Text.AlignRight
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top             : parent.top
            anchors.topMargin       : toPixels(0.4);
            color                   : "#0b903e"
            text                    : qsTr(strUnids)
        }
/*
        Text {
            id                      : scaleText
            horizontalAlignment     : Text.AlignRight
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top             : parent.top
            anchors.topMargin       : toPixels(0.6);
            color                   : "#0b903e"
            text                    : qsTr("x10")
        }*/
    }
}

/*
Text {
    id: text2
    x: 87
    y: 68
    color: "#0b903e"
    text: qsTr("x10")
    anchors.horizontalCenter: parent.horizontalCenter
    font.bold: true
    font.pixelSize: 14
}
*/
