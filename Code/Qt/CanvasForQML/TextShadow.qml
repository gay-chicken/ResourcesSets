import QtQuick

Item {
    Canvas {
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d")

            ctx.shadowColor = "#12a75d"
            ctx.shadowOffsetX = 2
            ctx.shadowOffsetY = 2
            ctx.shadowBlue = 10

            ctx.fillStyle = "#38cd7f"
            ctx.font = "bold 60px sans-serif"
            ctx.fillText("Canvas!", 30, 180)
        }
    }
}
