import QtQuick
import Qt5Compat.GraphicalEffects

Item {
    signal playChanged()

    id: root
    opacity: 0.5

    Rectangle {
        id: toolbar
        width: parent.width
        height: parent.height
        gradient: Gradient {
            GradientStop { position: 0.0; color: "darkGray" }
            GradientStop { position: 1.0; color: "gray" }
        }
    }

    NumberAnimation {
        target: toolbar
        property: "height"
        from: root.height
        to: 0
        duration: 500
        easing.type: Easing.InExpo
    }
}
