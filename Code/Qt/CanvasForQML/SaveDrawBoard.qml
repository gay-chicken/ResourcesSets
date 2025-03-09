import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    ColumnLayout {
        anchors.fill: parent

        Row {
            id: row
            spacing: 10
            Layout.alignment: Qt.AlignCenter

            Button {
                text: "Save"
                onClicked: {
                    canvas.save("D:\\Desktop\\ResourcesSets\\Image\\paint.png")
                    console.log("Canvas data has been written to D:\\Desktop\\ResourcesSets\\Image\\paint.png")
                }
            }
            Button {
                text: "Clear"
                onClicked: {
                    canvas.ctx.clearRect(0, 0, canvas.width, canvas.height)
                    canvas.requestPaint()
                }
            }
        }

        Canvas {
            property var ctx
            property real lastX
            property real lastY

            id: canvas
            Layout.fillHeight: true
            Layout.fillWidth: true
            onPaint: {
                ctx = getContext("2d")
                ctx.strokeStyle = "blue"
                ctx.lineWidth = 1.5

                ctx.beginPath()
                ctx.moveTo(lastX, lastY)
                lastX = area.mouseX
                lastY = area.mouseY
                ctx.lineTo(lastX, lastY)
                ctx.stroke()
            }

            MouseArea {
                id: area
                anchors.fill: parent
                onPressed: {
                    canvas.lastX = mouseX
                    canvas.lastY = mouseY
                }
                onPositionChanged: canvas.requestPaint()
            }
        }
    }
}
