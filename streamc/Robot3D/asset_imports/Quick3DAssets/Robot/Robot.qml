import QtQuick
import QtQuick3D

Node {
    // Materials
    // end of Materials

    Node {
        id: robot_obj
        Model {
            id: cube
            source: "meshes/cube.mesh"
            materials: [
                material_material
            ]
        }
        Model {
            id: obj_0
            source: "meshes/obj_0.mesh"
            materials: [
                color_40919_material,
                color_2829873_material,
                color_3888547_material,
                color_4634441_material,
                color_6383466_material,
                color_10988977_material,
                color_11107152_material,
                color_12568524_material,
                color_15277357_material,
                color_16089887_material,
                color_16768282_material
            ]
        }
    }

    Node {
        id: __materialLibrary__
        DefaultMaterial {
            id: defaultMaterial_material
            diffuseColor: "#999999"
            objectName: "defaultMaterial_material"
        }

        DefaultMaterial {
            id: material_material
            diffuseColor: "#cccccc"
            objectName: "material_material"
        }

        DefaultMaterial {
            id: color_10988977_material
            diffuseColor: "#a7adb1"
            objectName: "color_10988977_material"
        }

        DefaultMaterial {
            id: color_11107152_material
            diffuseColor: "#a97b50"
            objectName: "color_11107152_material"
        }

        DefaultMaterial {
            id: color_12568524_material
            diffuseColor: "#bfc7cc"
            objectName: "color_12568524_material"
        }

        DefaultMaterial {
            id: color_15277357_material
            diffuseColor: "#e91d2d"
            objectName: "color_15277357_material"
        }

        DefaultMaterial {
            id: color_16089887_material
            diffuseColor: "#f5831f"
            objectName: "color_16089887_material"
        }

        DefaultMaterial {
            id: color_16768282_material
            diffuseColor: "#ffdd1a"
            objectName: "color_16768282_material"
        }

        DefaultMaterial {
            id: color_2829873_material
            diffuseColor: "#2b2e31"
            objectName: "color_2829873_material"
        }

        DefaultMaterial {
            id: color_3888547_material
            diffuseColor: "#3b55a3"
            objectName: "color_3888547_material"
        }

        DefaultMaterial {
            id: color_40919_material
            diffuseColor: "#009fd7"
            objectName: "color_40919_material"
        }

        DefaultMaterial {
            id: color_4634441_material
            diffuseColor: "#aaaaaa"
            objectName: "color_4634441_material"
        }

        DefaultMaterial {
            id: color_6383466_material
            diffuseColor: "#00676a"
            objectName: "color_6383466_material"
        }
    }
}
