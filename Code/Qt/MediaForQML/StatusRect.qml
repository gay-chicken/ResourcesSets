import QtQuick
import QtQuick.Shapes

Item {
    width: 120
    height: 120
    opacity: 0.5
    Rectangle {
        anchors.fill: parent
        radius: width / 2
        gradient: Gradient {
            GradientStop { position: 0.0; color: "darkGray" }
            GradientStop { position: 1.0; color: "gray" }
        }

        Shape {


            ShapePath {
                fillColor: "black"
                strokeWidth: 0

                PathMove { x: 40; y: 30; }
                PathPolyline {
                    path: [
                        Qt.point(40, 30),
                        Qt.point(40, 90),
                        Qt.point(45, 90),
                        Qt.point(45, 30),
                        Qt.point(40, 30),
                    ]
                }
            }
            ShapePath {
                fillColor: "black"
                strokeWidth: 0

                PathMove { x: 80; y: 30; }
                PathPolyline {
                    path: [
                        Qt.point(80, 30),
                        Qt.point(80, 90),
                        Qt.point(75, 90),
                        Qt.point(75, 30),
                        Qt.point(80, 30),
                    ]
                }
            }
        }
    }
}
