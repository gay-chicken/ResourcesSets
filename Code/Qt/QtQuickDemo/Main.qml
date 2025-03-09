import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Text {
        // (1) 声明id用于之后的引用
        id: textLabel

        // (2) 设置属性值
        x: 50
        y: 100

        // (3) 绑定动态属性值
        height: 2 * width

        // (4) 添加新属性
        // property <类型> <名称>: <值>
        property int times: 24

        // (5) 使用别名声明属性
        property alias anotherName: textLabel.times

        // (6) 基于动态属性更新文本
        text: "text: " + anotherName

        // (7) 对象属性的另一种赋值方式
        font{family: "Ubuntu"; pixelSize: 24}

        // (8) 快速切换焦点
        KeyNavigation.tab: spaceLabel

        // (9) 为属性提供处理程序，当属性更改后被调用。
        onHeightChanged: console.log("height: ", height)

        // (10) 动态切换属性值
        color: focus ? "red" : "black"
        focus: true
    }

    Text {
        id: spaceLabel
        text: "space: " + spaceTimes + " times"
        KeyNavigation.tab: textLabel
        property int spaceTimes: 0

        // (11) 调用JS函数进行处理
        Keys.onSpacePressed: { increment() }

        // (12) 直接执行函数
        onTextChanged: function(text) { console.log("text changed to: ", text) }
        // onTextChanged: (text) => {} /*另一种方式*/

        // (13) 一次性赋值，取消关联
        Keys.onEscapePressed: { spaceLabel.text = '' }

        // 一个JS函数
        function increment() {
            spaceTimes += 1
        }
    }

    /*渐变 + 点击事件*/
    Rectangle {
        id: rect
        width: 100;
        height: 100;
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        gradient: Gradient {
            GradientStop { position: 0.0; color: "lightblue" }
            GradientStop { position: 1.0; color: "gray" }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: image.visible = !image.visible
        }
    }

    /*文字*/
    Text {
        x: rect.x
        y: rect.y + rect.height + 20

        text: "一段文字"
        color: "white"
        style: Text.Sunken
        styleColor: "blue"

        font.family: "楷体"
        font.pixelSize: 30
    }

    /*图片*/
    Image {
        id: image
        width: 100
        height: 100
        source: "qrc:/circle.png"
    }

    /*布局*/
    Column {
        spacing: 10

        Button {
            text: "move to right"
            onClicked: x += 10
            color: "red"
        }

        Button {
            text: "clickwise rotation"
            onClicked: rotation += 5
            color: "green"
        }

        Button {
            text: "magnify"
            onClicked: scale += 0.01
            color: "yellow"
        }
    }

    /*锚定*/
    Rectangle {
        x: 100
        y: 100
        width: 300
        height: 300
        color: "green"

        Rectangle {
            id: sub_rect_1
            width: 100
            height: 40
            color: "red"
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 10
        }

        Rectangle {
            id: sub_rect_2
            width: 150
            height: 40
            color: "red"
            anchors.top: sub_rect_1.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 10
        }

        Rectangle {
            width: 50
            height: 50
            color: "blue"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -20
        }
    }

    TextInput {
        anchors.right: parent.right
        text: "input your account"
    }

    Column {
        spacing: 10

        Repeater {
            id: inputRepeater
            model: 5
            TextInput {
                required property int index
                text: "input " + index
                KeyNavigation.tab: {
                    const nextIndex = (index + 1) % inputRepeater.count
                    return inputRepeater.itemAt(nextIndex)
                }
                Component.onCompleted: if (index === 0) forceActiveFocus()
            }
        }
    }
}
