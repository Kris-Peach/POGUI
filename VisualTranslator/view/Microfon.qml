import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.2
import Qt.controller.appmanager 1.0
import "."

Window {
    id: rmicr
    width: 300
    height: 400

    //property bool ifspeak: FALSE
    Rectangle{
        id:main
        width: 300
        height: 400
        color:MyStyle.backgroundColor
    Rectangle{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top; anchors.topMargin: 40
        width: 200
        height: 200
        border.color:MyStyle.greyColor
        border.width: 5
        radius: 100
        Image{
            anchors.centerIn:parent
            source:"images/big_microphone.png"
            width: 80

            height: width*1.6
        }
    }

    Rectangle{
        id:start
        anchors.left: main.left; anchors.leftMargin: 40
        anchors.bottom: main.bottom;anchors.bottomMargin: 40
        color:!start_area.enabled ? MyStyle.buttonColor: MyStyle.buttonColorDown
        width: 100
        height: 50
        radius: 10
        Text {
            id: text1
            color: "#ffffff"
            text: qsTr("Start")
            anchors.centerIn: parent
            font.pixelSize: 18
        }
        MouseArea {
                    id: start_area
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        AppManager.startSpeak()
                       // ifspeak=TRUE
                        start_area.enabled=false
                       // start.color=MyStyle.buttonColorEnable
                        stop_area.enabled=true
                   }
                }

    }
    Rectangle{
        id:stop
        anchors.right: parent.right; anchors.rightMargin: 40
        anchors.bottom: parent.bottom;anchors.bottomMargin: 40
        color:!stop_area.enabled ? MyStyle.buttonColor: MyStyle.buttonColorDown
        width: 100
        height: 50
        radius: 10
        enabled: true
        Text {
            id: text2
            color: "#ffffff"
            text: qsTr("Stop")
            anchors.centerIn: parent
            font.pixelSize: 18
        }
        MouseArea {
                    id: stop_area
                    anchors.fill: parent
                    hoverEnabled: true
                    enabled: false
                    onClicked: {
                        AppManager.stopSpeak()
                        rmicr.close()

                   }
                }
       /*onDestroyed: {
            if(ifspeak)
            AppManager.stopSpeak()
        }*/

    }

}
}
