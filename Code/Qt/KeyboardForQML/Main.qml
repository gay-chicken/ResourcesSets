import QtQuick

Window {
    width: 640
    height: 480

    Rectangle {
        focus: true
        Keys.onLeftPressed: cube.x -= 5
        Keys.onRightPressed: cube.x += 5
        Keys.onUpPressed: cube.y -= 5
        Keys.onDownPressed: cube.y += 5
        Keys.onPressed: (event) => {
                            switch (event.key) {
                                case Qt.Key_Plus: cube.scale += 0.1; break
                                case Qt.Key_Minus: cube.scale -= 0.1; break
                            }
                        }

        Rectangle {
            id: cube
            width: 50
            height: 50
            color: "red"
        }
    }
}
