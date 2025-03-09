import QtQuick

Item {
    Canvas {
        property real lastX
        property real lastY

        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d")

            ctx.lineWidth = 1.5
            ctx.strokeStyle = "blue"

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
