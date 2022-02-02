import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Mifare Classic Tool")

    Rectangle {
        id: mainRectangle
        anchors.fill: parent
        color: "#c0c2ce"

    StatusBar {
        visible: true
        anchors.top: mainRectangle.top *0.1
        anchors.horizontalCenter: mainRectangle.horizontalCenter
        width: parent.width*0.95

        } //statusbar
    } //main rectangle
} // window
