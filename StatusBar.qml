import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.14
import QtQuick.Window 2.11

RowLayout{
       width:  parent.width * 0.95
       height: parent.height * 0.06
       anchors.horizontalCenter: parent.horizontalCenter
       spacing: 0
       Rectangle{
              id: connectionStatus
              Layout.fillWidth: false
              Layout.preferredWidth: parent.width * 0.20
              Layout.fillHeight: true
              radius: 2
              color: "transparent"

              Rectangle{
                  width: parent.radius
                  height: parent.height
                  anchors.left: parent.left
                  color: parent.color
                  }

                  Button{
                      font.pixelSize: 12
                      text: "disconnect"
                  }
             }
       Rectangle
            {
           id:connectionStatusContainer
           Layout.fillWidth: false
           Layout.preferredWidth: parent.width * 0.30
           Layout.fillHeight: true
           radius: 2
           color: "transparent"//"#daf8e3"

                 Rectangle{
                    width: parent.radius
                    height: parent.height
                    anchors.left: parent.left
                    color: parent.color
                    }

                 Text {
                     anchors.fill: parent
                    fontSizeMode: Text.Fit
                    color:"#8b9dc3"
                    text: "Connected to port: 15"
                    font.pixelSize: 12
                    minimumPixelSize: 10
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    font.capitalization: Font.AllUppercase
                    }
            }

}




