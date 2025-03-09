import QtQuick

Item {
    Canvas {
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d")


            ctx.save()
            ctx.strokeStyle = "red"
            ctx.lineWidth = 1.5

            ctx.beginPath()
            ctx.moveTo(150, 50)
            ctx.lineTo(350, 200)
            ctx.lineTo(200, 300)
            ctx.closePath()
            ctx.stroke()
            ctx.clip()
            ctx.drawImage("qrc:/image/image.png", 10, 10)
            ctx.restore()

            // ctx.drawImage("qrc:/image/image.png", 10, 10)

        }

        Component.onCompleted: {
            loadImage("qrc:/image/image.png")
        }
    }
}
