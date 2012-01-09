import QtQuick 1.1
import com.nokia.meego 1.0

Item {
    id: subTitleButton

    property alias titleText: title.text
    property alias subTitleText: subTitle.text
    property alias icon: icon.source

    signal clicked

    height: 80
    width: parent.width

    BorderImage {
        id: background
        anchors.fill: parent
        visible: mouseArea.pressed
        source: "image://theme/meegotouch-list-background-pressed-center"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: background
        onClicked: {
            subTitleButton.clicked();
        }
    }

    Label {
        id: title

        anchors {
            left: parent.left
            leftMargin: 10
            rightMargin: 10
            topMargin: 10
            top: parent.top
        }

        font.bold: true
        text: "-"
    }

    Label {
        id: subTitle
        anchors {
            top:  title.bottom
            topMargin: 10
            left: parent.left
            leftMargin: 10
            rightMargin: 10
            right: icon.left
        }
        text: ""
    }

    Image {
        id: icon

        anchors {
            right: parent.right
            rightMargin: 10
            verticalCenter: parent.verticalCenter
        }
        height: sourceSize.height
        width: sourceSize.width
        source: "image://theme/meegotouch-combobox-indicator"
    }
}
