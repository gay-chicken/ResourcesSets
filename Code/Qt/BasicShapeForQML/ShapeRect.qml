import QtQuick
import QtQuick.Shapes

Rectangle {
    /*Shape自定义图案*/
    Shape {
        ShapePath {
            property real tick: 0.0

            id: shapePath
            strokeWidth: 3
            strokeColor: "darkGray"
            fillColor: "lightGray"

            startX: -40; startY: 200
            PathArc { x: 40; y: 200; radiusX: 200; radiusY: 200; useLargeArc: true; }
            PathLine { x: 40; y: 120; }
            PathArc { x: -40; y: 120; radiusX: 120; radiusY: 120; useLargeArc: true; direction: PathArc.Counterclockwise }
            PathLine { x: -40; y: 200; }

            PathMove { x: -20+(1-shapePath.tick)*20; y: 80 + shapePath.tick*50; }
            PathArc { x: 20-(1-shapePath.tick)*20; y: 80 + shapePath.tick*50; radiusX: 20 * shapePath.tick; radiusY: 20 * shapePath.tick; }
            PathArc { x: -20+(1-shapePath.tick)*20; y: 80 + shapePath.tick*50; radiusX: 20 * shapePath.tick; radiusY: 20 * shapePath.tick; }

            PathMove { x: -20; y: 130 + shapePath.tick*50; }
            PathArc { x: 20; y: 130 + shapePath.tick*50; radiusX: 20; radiusY: 20; }
            PathArc { x: -20; y: 130 + shapePath.tick*50; radiusX: 20; radiusY: 20; }

            PathMove { x: -20; y: 180 + shapePath.tick*50; }
            PathArc { x: 20; y: 180 + shapePath.tick*50; radiusX: 20; radiusY: 20; }
            PathArc { x: -20; y: 180 + shapePath.tick*50; radiusX: 20; radiusY: 20; }

            PathMove { x: -20 + shapePath.tick*20; y: 230 + shapePath.tick*50; }
            PathArc { x: 20 - shapePath.tick*20; y: 230 + shapePath.tick*50; radiusX: 20 * (1-shapePath.tick); radiusY: 20 * (1-shapePath.tick); }
            PathArc { x: -20 + shapePath.tick*20; y: 230 + shapePath.tick*50; radiusX: 20 * (1-shapePath.tick); radiusY: 20 * (1-shapePath.tick); }

            NumberAnimation on tick {
                from: 0.0
                to: 1.0
                duration: 500
                loops: Animation.Infinite
            }
        }
    }

    /*Shape路径*/
    Shape {
        visible: false

        ShapePath {
            strokeColor: "red"
            strokeWidth: 3
            startX: 20
            startY: 70

            /*线段*/
            PathLine {
                x: 180
                y: 130
            }

            /*折线*/
            PathPolyline {
                path: [
                    Qt.point(220, 100),
                    Qt.point(260, 70),
                    Qt.point(300, 170),
                    Qt.point(340, 60),
                    Qt.point(380, 100),
                ]
            }

            /*曲线*/
            PathMove{ x: 250; y: 200; }
            PathArc {
                x: 100
                y: 200
                radiusX: 30
                radiusY: 60
            }

            /*二次曲线*/
            PathMove { x: 300; y: 200; }
            PathQuad {
                x: 400
                y: 200
                controlX: 200
                controlY: 400
            }

            /*三次曲线*/
            PathMove { x: 100; y: 400; }
            PathCubic {
                x: 200
                y: 400
                control1X: 100
                control1Y: 100
                control2X: 400
                control2Y: 400
            }

            /*曲线段*/
            PathMove { x: 250; y: 400; }
            PathCurve { x: 300; y: 450; }
            PathCurve { x: 350; y: 300; }
            PathCurve { x: 200; y: 500; }

        }
    }
}
