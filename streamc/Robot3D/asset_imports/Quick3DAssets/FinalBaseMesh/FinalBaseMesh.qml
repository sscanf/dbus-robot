import QtQuick
import QtQuick3D

Node {
    // Materials
    // end of Materials

    Node {
        id: finalBaseMesh_obj
        Model {
            id: group1
            source: "meshes/group1.mesh"
            materials: [
                default_material
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
            id: default_material
            diffuseColor: "#999999"
            objectName: "default_material"
        }
    }
}
