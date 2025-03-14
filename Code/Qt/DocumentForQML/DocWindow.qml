import QtQuick
import QtQuick.Controls
import Qt.labs.platform as Platform

ApplicationWindow {
    property string fileName
    property bool isDirty: true
    property bool tryingClose: false

    id: root
    width: 640
    height: 360
    visible: true
    title: (fileName.length==0?"Document":fileName)+(isDirty?"*":"")

    menuBar: MenuBar {
        Menu {
            title: "File"

            MenuItem {
                text: "New"
                onTriggered: root.createDocument()
            }
            MenuItem {
                text: "Open"
                onTriggered: root.openDocument()
            }
            MenuItem {
                text: "Save"
                onTriggered: root.saveDocument()
            }
            MenuItem {
                text: "Exit"
                onTriggered: console.log("Exit")
            }
        }
    }

    Platform.FileDialog {
        id: fileDialog
        onAccepted: {
            var win = root.constructDocument()
            win.fileName = fileDialog.file
            win.show()
        }
    }

    function constructDocument() {
        var component = Qt.createComponent("qrc:/qml/DocWindow.qml")
        if (component === null) console.error("Component is null!")
        else return component.createObject(/*root*/)
    }

    function createDocument() {
        var win = constructDocument()
        win.show()
    }

    function openDocument() {
        fileDialog.open()
    }
}
