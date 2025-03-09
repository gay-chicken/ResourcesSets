import QtQuick

Item {
    Canvas {
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d")

            /*设置画笔*/
            ctx.lineWidth = 4
            ctx.strokeStyle = "green"
            ctx.fillStyle = "gray"

            ctx.beginPath()

            /*绘制边框*/
            ctx.moveTo(50, 50)
            ctx.lineTo(150, 50)
            ctx.lineTo(150, 150)
            ctx.lineTo(50, 150)

            /*填充内部*/
            ctx.fill()

            ctx.closePath()

            /*进行绘制*/
            ctx.stroke()

            /*使用函数*/
            ctx.fillStyle = "yellow"
            ctx.fillRect(30, 30, 60, 60)
            ctx.clearRect(70, 70, 90, 90)
            ctx.strokeRect(200, 200, 260, 250)

            /*绘制渐变*/
            var gradient = ctx.createLinearGradient(300, 0, 0, 300)
            gradient.addColorStop(0, "blue")
            gradient.addColorStop(0.5, "lightsteelblue")
            ctx.fillStyle = gradient
            ctx.fillRect(150, 0, 100, 100)

            /*几何变换*/
            ctx.translate(width/2, height/2)
            ctx.strokeStyle = "lightblue"
            ctx.beginPath()
            ctx.rect(-20, -20, 40, 40)
            ctx.stroke()
            ctx.rotate(Math.PI/4)
            ctx.strokeStyle = "pink"
            ctx.beginPath()
            ctx.rect(-20, -20, 40, 40)
            ctx.stroke()

            /*合成模式*/
            ctx.globalCompositeOperation = "qt-difference"
            ctx.beginPath()
            ctx.arc(100, 100, 50, 0, 2 * Math.PI)
            ctx.closePath()
            ctx.fill()
            ctx.beginPath()
            ctx.arc(150, 100, 50, 0, 2 * Math.PI)
            ctx.closePath()
            ctx.fill()
        }
    }
}
