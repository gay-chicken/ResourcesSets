import QtQuick
import QtQuick.Controls
import Qt.labs.platform as Platform
import "qrc:/state"

ApplicationWindow {
    width: 600
    height: 600
    visible: true
    title: qsTr("Desktop QML")
    background: Image {
        id: image
        anchors.fill: parent
        source: "qrc:/image/星球行走.jpg"
    }

    // SimpleState {} /*State and Transition*/

    menuBar: MenuBar {
        Menu {
            title: "文件(&F)"
            MenuItem {
                text: "打开(&O)"
                icon.source: "qrc:/image/file-open.png"
                onTriggered: fileDialog.open()
            }
        }

        Menu {
            title: "帮助(&H)"
            MenuItem {
                text: "关于(&A)"
                onTriggered: aboutDialog.open()
            }
        }
    }

    header: ToolBar {
        Flow {
            anchors.fill: parent

            ToolButton {
                text: "打开"
                icon.source: "qrc:/image/file-open.png"
                onClicked: fileDialog.open()
            }
        }
    }

    Platform.FileDialog {
        id: fileDialog
        title: "选择图片"
        nameFilters: [
            "Images files(*.png, *.jpg)", "All files(*.*)"
        ]
        onAccepted: {
            image.source = fileDialog.file
        }
    }

    Dialog {
        id: aboutDialog
        width: 300
        height: 150
        anchors.centerIn: parent
        title: "关于..."
        Label {
            anchors.fill: parent
            text: "    这是关于程序的相关介绍....\n经过换行操作的文字"
        }
        standardButtons: Platform.StandardButton.Ok
    }
}
