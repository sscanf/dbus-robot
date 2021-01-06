import QtQuick 2.0

Rectangle {
    id: mainMenu
    width: 900
    height: 563
    signal launch(app: string)

    Image {
        id: background
        source: "qml/tron_background_by_anarchyartistbuddy_d5gdvp8-fullview.jpg"
        fillMode: Image.PreserveAspectFit
    }

    Column {
        x: 286
        opacity: 1
        spacing: 0

        TronButton {
            id: speedButton
            width: 328
            height: 90
            text: "Speed Pannel"
            onClicked: {
                if (state == "")
                    state= "LedOn"
                else if (state=="LedOn")
                    state=""

                mainMenu.launch ("speedPannel")
            }
        }

        TronButton {
            id: cvButton
            text: "CV Pannel"
            width: 328
            height: 90
            onClicked: {
                if (state == "")
                    state= "LedOn"
                else if (state=="LedOn")
                    state=""
                mainMenu.launch ("cvPannel")
            }
        }

        TronButton {
            id: powerButton
            width: 328
            height: 90
            text: "Power Pannel"
            onClicked: {
                if (state == "")
                    state= "LedOn"
                else if (state=="LedOn")
                    state=""
                mainMenu.launch ("powerPannel")
            }
        }

        TronButton {
            id: irCameraButton
            width: 328
            height: 90
            text: "IR Camera"
            onClicked: {
                if (state == "")
                    state= "LedOn"
                else if (state=="LedOn")
                    state=""
                mainMenu.launch ("ircameraPannel")
            }
        }

    }
}
