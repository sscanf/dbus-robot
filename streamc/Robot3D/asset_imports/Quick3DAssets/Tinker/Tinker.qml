import QtQuick
import QtQuick3D
import Quick3DAssets.Tinker 1.0
import Quick3DAssets.Robot 1.0

Node {
    // Materials
    // end of Materials

    Node {
        id: tinker_obj
        Model {
            id: group_0_40919
            source: "meshes/group_0_40919.mesh"
            materials: [
                color_40919_material
            ]
        }
        Model {
            id: group_0_2829873
            source: "meshes/group_0_2829873.mesh"
            materials: color_40919_material
        }
        Model {
            id: group_0_3888547
            source: "meshes/group_0_3888547.mesh"
            materials: [
                color_3888547_material
            ]
        }
        Model {
            id: group_0_4634441
            source: "meshes/group_0_4634441.mesh"
            materials: [
                color_4634441_material
            ]
        }
        Model {
            id: group_0_6383466
            source: "meshes/group_0_6383466.mesh"
            materials: [
                color_6383466_material
            ]
        }
        Model {
            id: group_0_10988977
            source: "meshes/group_0_10988977.mesh"
            materials: [
                color_10988977_material
            ]
        }
        Model {
            id: group_0_11107152
            source: "meshes/group_0_11107152.mesh"
            materials: [
                color_11107152_material
            ]
        }
        Model {
            id: group_0_12568524
            source: "meshes/group_0_12568524.mesh"
            materials: [
                color_12568524_material
            ]
        }
        Model {
            id: group_0_15277357
            source: "meshes/group_0_15277357.mesh"
            materials: [
                color_15277357_material
            ]
        }
        Model {
            id: group_0_16089887
            source: "meshes/group_0_16089887.mesh"
            materials: [
                color_16089887_material
            ]
        }
        Model {
            id: group_0_16768282
            source: "meshes/group_0_16768282.mesh"
            materials: [
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
            id: color_10988977_material
            lighting: DefaultMaterial.NoLighting
            diffuseColor: "#a7adb1"
            objectName: "color_10988977_material"
        }

        DefaultMaterial {
            id: color_40919_material
            lighting: DefaultMaterial.NoLighting
            diffuseColor: "#009fd7"
            objectName: "color_40919_material"
        }

        DefaultMaterial {
            id: color_2829873_material
            lighting: DefaultMaterial.NoLighting
            diffuseColor: "#2b2e31"
            objectName: "color_2829873_material"
        }

        DefaultMaterial {
            id: color_6383466_material
            lighting: DefaultMaterial.NoLighting
            diffuseColor: "#61676a"
            objectName: "color_6383466_material"
        }

        DefaultMaterial {
            id: color_16768282_material
            lighting: DefaultMaterial.NoLighting
            diffuseColor: "#ffdd1a"
            objectName: "color_16768282_material"
        }

        DefaultMaterial {
            id: color_16089887_material
            lighting: DefaultMaterial.NoLighting
            diffuseColor: "#f5831f"
            objectName: "color_16089887_material"
        }

        DefaultMaterial {
            id: color_4634441_material
            lighting: DefaultMaterial.NoLighting
            diffuseColor: "#46b749"
            objectName: "color_4634441_material"
        }

        DefaultMaterial {
            id: color_12568524_material
            lighting: DefaultMaterial.NoLighting
            diffuseColor: "#bfc7cc"
            objectName: "color_12568524_material"
        }

        DefaultMaterial {
            id: color_15277357_material
            lighting: DefaultMaterial.NoLighting
            diffuseColor: "#e91d2d"
            objectName: "color_15277357_material"
        }

        DefaultMaterial {
            id: color_3888547_material
            lighting: DefaultMaterial.NoLighting
            diffuseColor: "#3b55a3"
            objectName: "color_3888547_material"
        }

        DefaultMaterial {
            id: color_11107152_material
            lighting: DefaultMaterial.NoLighting
            diffuseColor: "#a97b50"
            objectName: "color_11107152_material"
        }
    }
}
