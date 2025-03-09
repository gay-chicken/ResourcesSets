import QtQuick

Item {
    id: root
    width: 250
    height: 250

    Row {
        spacing: 10

        Rectangle {
            id: rect1
            width: 100
            height: 100
            color: "black"
        }

        Rectangle {
            id: rect2
            width: 100
            height: 100
            color: "black"
        }
    }

    /*鼠标事件处理*/
    MouseArea {
        anchors.fill: parent
        onPressed: root.state = "press"
        onReleased: root.state = "release"
    }

    /*状态转换*/
    states: [
        State {
            name: "press"
            PropertyChanges {
                target: rect1
                color: "red"
            }
            PropertyChanges {
                target: rect2
                color: "blue"
            }
        },
        State {
            name: "release"
            PropertyChanges {
                target: rect1
                color: "green"
            }
            PropertyChanges {
                target: rect2
                color: "orange"
            }
        }
    ]

    /*过渡效果*/
    transitions: [
        Transition {
            from: "press"
            to: "release"

            ColorAnimation {
                targets: [rect1, rect2]
                properties: "color"
                duration: 200
            }
        },

        Transition {
            from: "release"
            to: "press"

            ColorAnimation {
                targets: [rect1, rect2]
                properties: "color"
                duration: 200
            }
        }
    ]
}
