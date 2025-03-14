import QtQuick
import QtQuick3D

Window {
    width: 640
    height: 480
    visible: true

    View3D {
        anchors.fill: parent
        environment: SceneEnvironment {
            clearColor: "gray"
            backgroundMode: SceneEnvironment.Color
        }

        /*模型*/
        Model {
            position: Qt.vector3d(0, 0, 0)
            source: "#Cone"
            materials: [
                DefaultMaterial {
                    diffuseColor: "yellow"
                    specularTint: "red" /*镜面光*/
                    specularAmount: 0.7 /*反射量*/
                    specularRoughness: 0.4 /*反射粗糙度*/
                }
            ]
        }
        Model {
            position: Qt.vector3d(100, 50, -100)
            source: "#Sphere"
            materials: [
                PrincipledMaterial{
                    baseColor: "green"
                    metalness: 0.8 /*金属质感*/
                    roughness: 0.3 /*粗糙度*/
                }
            ]
        }
        Model {
            position: Qt.vector3d(0, -50, 0)
            eulerRotation: Qt.vector3d(-90, 0, 0)
            scale: Qt.vector3d(3, 3, 3)
            source: "#Rectangle"
            materials: [PrincipledMaterial{baseColor: "white"}]
        }

        /*视角*/
        PerspectiveCamera {
            position: Qt.vector3d(0, 200, 300)
            clipNear: 0.1
            clipFar: 500
            Component.onCompleted: lookAt(Qt.vector3d(0, 0, 0))
        }

        /*灯光*/
        DirectionalLight {
            position: Qt.vector3d(0, 300, 0)
            eulerRotation: Qt.vector3d(0, 0, 0)
            castsShadow: true
        }
        PointLight {
            position: Qt.vector3d(100, 100, 100)
            castsShadow: true
        }
        SpotLight {
            position: Qt.vector3d(200, 200, 300)
            brightness: 5
            ambientColor: Qt.rgba(0.25, 0, 0, 0.9)
            castsShadow: true
        }
    }
}
