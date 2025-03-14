import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    Row {
        spacing: 10
        anchors.centerIn: parent

        TextField {
            id: addNum
            placeholderText: "请输入数字"
            validator: DoubleValidator { decimals: 2 }
        }

        Label {
            text: "+"
        }

        TextField {
            id: addedNum
            placeholderText: "请输入数字"
            validator: DoubleValidator { decimals: 2 }
        }

        Label {
            text: "="
        }

        TextField {
            id: resultNum
            placeholderText: "结果"
            readOnly: true
        }

        Button {
            text: "计算"
            onClicked: {
                calculator.calculate(addNum.text, addedNum.text)
                resultNum.text = calculator.text
            }
        }
    }







}
