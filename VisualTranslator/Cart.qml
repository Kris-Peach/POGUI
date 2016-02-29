import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Private 1.0
import QtGraphicalEffects 1.0
import "."
/*Window {
    id:main
    visible: true
    width: 400
    height: width+50*/
    Rectangle{
        width: 300
        height: width*1.4
        radius: width/30
        border.color:MyStyle.greyColor
        color:MyStyle.backgroundCard
        Text{
            id:inputText
            font.pixelSize: parent.width*2/24
            text:qsTr("Cat")
            anchors.top: parent.top; anchors.topMargin: parent.width/20
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Rectangle{
            id:pictureBox
            border.color: MyStyle.greyColor
            radius: 3
            //color:MyStyle.greyColor
            width: parent.width*0.8
            height: width*1.2
            //border.color: "#000000"
            anchors.top:parent.top; anchors.topMargin: parent.width/11//33
            anchors.centerIn: parent
            Image{
                id:picture
                source:"images/picture.jpg"
                width: parent.width-3
                height: width
                anchors.top:parent.top;anchors.topMargin: 1
                anchors.horizontalCenter: parent.horizontalCenter
                //anchors.centerIn: parent
            }
            Rectangle{
                id:buttons
                width: parent.width-3
                height: parent.width*0.2
                anchors.top:picture.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                color:"#00000000"
                //border.color:"#666fff"
                Image{
                    id:replaceButton
                    source: replace_area.pressed ? "images/rotate-down.png":"images/rotate.png"
                    width: parent.height
                    height: width
                    anchors.left:parent.left
                    MouseArea {
                                id: replace_area
                                anchors.fill: parent
                                hoverEnabled: true
                            }
                }
                Image{
                    id:likeButton
                    source: like_area.pressed ? "images/like-down.png" :"images/like.png"
                    width: parent.height
                    height: width
                    anchors.left:replaceButton.right
                    MouseArea {
                                id: like_area
                                anchors.fill: parent
                                hoverEnabled: true
                            }
                }
            }
        }
        Text{
            id:outputText
            font.pixelSize:parent.width*2/24
            text:qsTr("Кошка")
            anchors.bottom: parent.bottom; anchors.bottomMargin:  parent.width/20
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

//}

