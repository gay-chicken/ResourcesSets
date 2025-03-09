import QtQuick

Item {


    Rectangle {
        id: box1
        x: 50
        y: 50
        width: 50
        height: 50
        color: "red"
    }

    Rectangle {
        id: box2
        x: 150
        y: 150
        width: 50
        height: 50
        color: "green"
    }

    states: [
        State {
            name: "toRD"
            PropertyChanges {
                target: box1
                x: box1.x += 5
                y: box1.y += 5
                color: "blue"
            }
        },
        State {
            name: "toRU"
            PropertyChanges {
                target: box2
                x: x += 5
                y: y -= 5
                color: "blue"
            }
        }
    ]
}
