import QtQuick
import QtMultimedia
import QtQuick.Controls
import Qt.labs.platform as Platform

Item {
    property string fileName: "file:///D:\\Desktop\\ResourcesSets\\Media\\AppleBad!.mp4"

    id: root
    anchors.fill: parent

    MediaPlayer {
        id: mediaPlayer
        source: fileName
        audioOutput: audioOutput
        videoOutput: videoOutput
        autoPlay: true
    }

    AudioOutput {
        id: audioOutput
        volume: 100
    }

    VideoOutput {
        id: videoOutput
        anchors.fill: parent
    }

    StatusRect {
        anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: function(mouse) {
           if (mouse.button === Qt.LeftButton) {
               if (mediaPlayer.playbackState === MediaPlayer.PlayingState) mediaPlayer.pause()
               else mediaPlayer.play()
           } else if (mouse.button === Qt.RightButton) {
               popup.x = mouseX
               popup.y = mouseY
               popup.open()
           }
       }
    }

    Menu {
        id: popup
        MenuItem {
            text: "打开文件"
            onTriggered: fileDialog.open()
        }
    }

    Platform.FileDialog {
        id: fileDialog
        onAccepted: {
            root.fileName = fileDialog.file
            mediaPlayer.play()
        }
    }
}
