import QtQuick.Scene3D 2.15

import qt3d.core 2.14
import Qt3D.Render 2.14
import Qt3D.Extras 2.14
import Qt3D.Input 2.12
import QtQuick 2.14


//source: "file:///media/psf/Projects-1/dbus-robot/streamc/3d/Chasis_Robot/tinker.obj"
Rectangle{
    visible: true
    id: scene
    color: "black"
    width: 1280
    height: 1024

    Scene3D {
        anchors.fill: parent
        compositingMode: Scene3D.FBO

        aspects: ["input", "logic", "render"]
        cameraAspectRatioMode: Scene3D.AutomaticAspectRatio

        Entity {
            id: sceneRoot
            components: [
                RenderSettings {
                    activeFrameGraph: ForwardRenderer {
                        clearColor: Qt.rgba(0, 0.5, 1, 1)
                        camera: camera
                    }
                }
            ]
            Camera {
                id: camera
                projectionType: CameraLens.PerspectiveProjection
                fieldOfView: 30
                aspectRatio: 16/9
                position   : Qt.vector3d( 0.0, 0.0, 5.0 )
                viewCenter : Qt.vector3d( 0.0, 0.0, 0.0 )
            }
//            OrbitCameraController {
//                   camera: camera
//               }

            Entity {
                id: myObject
                property real aspectRatio: 1.0

                components: [
                    SceneLoader {
                        id: sceneLoader
                        //source: "file:///media/psf/Projects-1/dbus-robot/streamc/qml/3d/tinker.obj"
                        source: "qrc:///tinker.obj"
                        ObjectPicker {
                            id: picker
                            onClicked: {
                               console.log("Picked")
                           }
                        }
                        Transform {
                            id: faceTransform
                            translation: Qt.vector3d(0, 0, 30)
                        }
                        onStatusChanged: {
                            console.log (status)
                            if (status == SceneLoader.Ready) {
                                camera.viewAll()
                                //camera.position.z = 100
                            }
                            if (status == SceneLoader.Error) {
                                console.log (Error)
                            }
                        }
                    }
                ]
            }
            Entity {
                 id: spotLight
                 components: [
                     Transform {
                         id: spotLightTransform
                         translation: camera.position
                     },

                     SpotLight {
                         id: mainLight
                         parent: camera
                         enabled: true
                         intensity: 100
                         localDirection: Qt.vector3d(0,0,0)
                     }
                 ]
             }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
