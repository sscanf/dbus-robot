import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

Rectangle {

    property alias value      : elev.valuer
    property int   maxWarning : 1899
    property int   minWarning : 5
    property int   scaleVal   : 1
    property int   maxValue   : 2000
    property int   labelStep  : 100
    color: "#000000"

    id      : rectangle


    gradient: Gradient {
        GradientStop {
            position: 0.00;
            color: "#000000";
        }
        GradientStop {
            position: 1.00;
            color: "#262d2d";
        }
    }

    CircularGauge {

         property real valuer
         antialiasing: true

         id          : elev
         value       : valuer;
         minimumValue: 0
         maximumValue: maxValue*scale
         stepSize    : 1
         anchors.fill: parent

         style       : AzimutGaugeStyle {
             id                  : elveStyle
             minimumValueAngle   : -160
             maximumValueAngle   : 160
             minimumWarning      : minWarning
             maximumWarning      : maxWarning
             halfGauge           : false
             labelStepSize       : labelStep
             tickmarkStepSize    : labelStep

             tickmarkLabel       : Text {
                 color           : "green"
                 font.pixelSize  : toPixels(0.1)
                 text            : styleData.value
             }
             strUnids            : "rpm"
         }
     }

    Behavior on value {
        NumberAnimation {
            duration     : 1300
            easing.type  : Easing.OutSine
            easing.period: 1.5
            //easing.amplitude: Math.min(Math.max(-130, gauge3.value*2.2 - 130), 133)
        }
    }
 }
