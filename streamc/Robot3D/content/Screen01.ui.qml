

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.3
import QtQuick.Controls 6.3
import QtQuick3D 6.3
import Robot3D
import Quick3DAssets.Robot 1.0

Rectangle {
    width: Constants.width
    height: Constants.height
    color: "#000000"
    layer.enabled: false

    View3D {
        id: view3D
        visible: true
        anchors.fill: parent
        transformOrigin: Item.Center
        camera: cameraOrthographic
        environment: sceneEnvironment

        SceneEnvironment {
            id: sceneEnvironment
            backgroundMode: SceneEnvironment.Transparent
            clearColor: "#000000"
            depthPrePassEnabled: false
            antialiasingMode: SceneEnvironment.MSAA
            antialiasingQuality: SceneEnvironment.High
        }

        Node {
            id: scene
            Robot {
                id: robot
                x: 0
                y: 0
                visible: true
                eulerRotation.z: -0
                eulerRotation.y: 0
                eulerRotation.x: -2.05406
                z: 0
            }

            DirectionalLight {
                x: -0.007
                y: 844.557
                color: "#ffffff"
                scope: robot
                eulerRotation.x: -90
                z: 13.75708
                brightness: 2
            }

            PerspectiveCamera {
                id: cameraOrthographic
                x: -17.749
                y: 255.88
                frustumCullingEnabled: false
                eulerRotation.z: -1.13887
                eulerRotation.y: -178.60245
                eulerRotation.x: -28.05433
                z: -298.73236
            }
        }
    }

    Item {
        id: __materialLibrary__
        DefaultMaterial {
            id: defaultMaterial
            objectName: "Default Material"
            diffuseColor: "#ffffff"
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.33}D{i:6}
}
##^##*/

