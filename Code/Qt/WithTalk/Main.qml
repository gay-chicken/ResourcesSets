import QtQuick
import QtQuick.Controls

Window {
    property real w: 550
    property real h: 640
    property real dpi: 1

    id: root
    width: root.w * root.dpi
    height: root.h * root.dpi
    visible: true
    flags: Qt.Window | Qt.FramelessWindowHint | Qt.WindowDropShadowHint
    color: "transparent"

    /*修改光标*/
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.NoButton
        cursorShape: {
            const pos = Qt.point(mouseX, mouseY)
            const bound = 2
            if (pos.x < bound && pos.y < bound) return Qt.SizeFDiagCursor;
            if (pos.x >= width - bound && pos.y >= height - bound) return Qt.SizeFDiagCursor;
            if (pos.x >= width - bound && pos.y < bound) return Qt.SizeBDiagCursor;
            if (pos.x < bound && pos.y >= height - bound) return Qt.SizeBDiagCursor;
            if (pos.x < bound || pos.x >= width - bound) return Qt.SizeHorCursor;
            if (pos.y < bound || pos.y >= height - bound) return Qt.SizeVerCursor;
            return Qt.ArrowCursor;
        }
    }

    DragHandler {
        id: resizeHandler
        grabPermissions: TapHandler.TakeOverForbidden
        target: null
        onActiveChanged: if (active) {
            const pos = resizeHandler.centroid.position;
            const bound = 2
            let edges = 0;
            if (pos.x < bound) { edges |= Qt.LeftEdge }
            if (pos.x >= width - bound) { edges |= Qt.RightEdge }
            if (pos.y < bound) { edges |= Qt.TopEdge }
            if (pos.y >= height - bound) { edges |= Qt.BottomEdge }
            root.startSystemResize(edges);
        }
    }

    Rectangle {
        property bool isFill: false
        property bool isTop: false

        id: background
        anchors.fill: parent
        color: "white"
        radius: 3
        border.color: "#cdcdcd"
        border.width: 1

        /*背景图标*/
        Image {
            width: 100
            height: 100
            source: "qrc:/image/chat.png"
            anchors.bottom: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Item {
            width: parent.width - 32 * 4 * root.dpi
            height: 25
            anchors.top: parent.top
            anchors.left: parent.left

            TapHandler {
                onTapped: if (tapCount === 2) toggleVisibility()
                gesturePolicy: TapHandler.DragThreshold
            }

            DragHandler {
                grabPermissions: TapHandler.CanTakeOverFromAnything
                onActiveChanged: if (active) root.startSystemMove()
            }
        }

        /*窗口控件*/
        Row {
            width: parent.width
            height: 25
            layoutDirection: Qt.RightToLeft
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.topMargin: 1
            anchors.rightMargin: 1

            Rectangle {
                width: 32 * root.dpi
                height: parent.height
                radius: [0, 5, 0, 0]   // FIX: 右上角圆角失败

                Image {
                    width: 16
                    height: 16
                    source: "qrc:/image/close.png"
                    anchors.centerIn: parent
                }

                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: parent.color = "#fb7373"
                    onExited: parent.color = "white"
                    onClicked: Qt.quit()
                }
            }

            Rectangle {
                width: 32 * root.dpi
                height: parent.height
                Image {
                    width: 16
                    height: 16
                    source: background.isFill ? "qrc:/image/windowing.png" : "qrc:/image/fill_screen.png"
                    anchors.centerIn: parent
                }

                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: parent.color = "#f3f3f3"
                    onExited: parent.color = "white"
                    onClicked: toggleVisibility()
                }
            }

            Rectangle {
                width: 32 * root.dpi
                height: parent.height
                Image {
                    width: 16
                    height: 16
                    source: "qrc:/image/minimumed.png"
                    anchors.centerIn: parent
                }

                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: parent.color = "#f3f3f3"
                    onExited: parent.color = "white"
                    onClicked: root.visibility = Window.Minimized
                }
            }

            Rectangle {
                width: 32 * root.dpi
                height: parent.height
                Image {
                    width: 16
                    height: 16
                    source: background.isTop ? "qrc:/image/fixed.png" : "qrc:/image/fix.png"
                    anchors.centerIn: parent
                }

                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: parent.color = "#f3f3f3"
                    onExited: parent.color = "white"
                    onClicked: {
                        background.isTop = !background.isTop
                        if (background.isTop) root.flags |= Qt.WindowStaysOnTopHint
                        else root.flags &= ~Qt.WindowStaysOnTopHint
                    }
                }
            }

        }
    }



    function toggleVisibility() {
        background.isFill = !background.isFill
        if (background.isFill) root.visibility = Window.Maximized
        else root.visibility = Window.Windowed
    }
}
