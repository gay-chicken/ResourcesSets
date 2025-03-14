import QtQuick

Loader {
    property real speed: 0

    id: loader
    onLoaded: { binded.target = loader.item }

    Binding {
        id: binded
        property: "speed"
        value: loader.speed
    }

    states: [
        State {
            name: "text"
            PropertyChanges {
                target: loader
                source: "qrc:/qml/TextShow.qml"
            }
        },
        State {
            name: "draw"
            PropertyChanges {
                target: loader
                source: "qrc:/qml/DrawShow.qml"
            }
        }

    ]
}


