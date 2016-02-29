import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Private 1.0
import QtGraphicalEffects 1.0
import "."
Window {
    id:mainWindow
    visible: true
    width: 800
    height: 600
    color:MyStyle.backgroundColor

    Rectangle{
        id:head
        width: parent.width
        height: 85
        color:MyStyle.brightColor
        smooth: true
        visible: false
        Text {
            id: text1
            y: 35
            color: "#ffffff"
            anchors.left:parent.left; anchors.leftMargin: 50
            text: qsTr("Visual Translator")
            font.pixelSize: 22
        }
    }
    DropShadow {

            anchors.fill: source
            horizontalOffset: 0
            verticalOffset: 2
            fast: false
            radius:100.0
            samples:25
            color: "#78000000"
            source: head
            smooth: true;
            cached: true;
    }

    Rectangle{
        id:body
        anchors.top: head.bottom;
        anchors.topMargin: 15
        width: mainWindow.width
        height: parent.height-y
        color:MyStyle.backgroundColor
        Rectangle{
            id:input
            anchors.left: parent.left; anchors.leftMargin: mainWindow.width<=800 ? 30:mainWindow.width*0.05
            anchors.top: parent.top
            width: MyStyle.minWidthInputBox<mainWindow.width*0.43?mainWindow.width*0.43 : MyStyle.minWidthInputBox
            height:140//textInput.x+textInput.height+inputLang.height//translateButton.y+translateButton.height
            border.color: MyStyle.greyColor
            ComboBox{
                id:inputLang
                anchors.right: parent.right; anchors.rightMargin: 5
                anchors.top: parent.top;anchors.topMargin: MyStyle.marginTop
                style:LightComboBoxStyle{ id:combo1 }
                width:100//parent.width-inputVoice.width
                model:ListModel{
                    ListElement {text:"English"}
                    ListElement {text:"Русский"}
                }
            }
            Image{
                id:volumeInputButton
                width: 25
                height: inputLang.height
                source: volumeInput_area.pressed ? "images/Medium Volume Filled-50.png": "images/volume.png"
                anchors.right:inputLang.left;anchors.rightMargin: MyStyle.marginBetween
                anchors.top: parent.top;anchors.topMargin: MyStyle.marginTop
                MouseArea {
                            id: volumeInput_area
                            anchors.fill: parent
                            hoverEnabled: true
                        }
            }
            Image{
                id:microfonInputButton
                x: 150
                y: 0
                source:microfonInput_area.pressed?"images/microphone-down.png": "images/microphone.png"
                width: 25
                height: inputLang.height
                anchors.right:volumeInputButton.left;anchors.rightMargin: MyStyle.marginBetween
                anchors.top: parent.top;anchors.topMargin: MyStyle.marginTop
                MouseArea {
                            id: microfonInput_area
                            anchors.fill: parent
                            hoverEnabled: true
                        }
            }
            Image{
                id:clearInputButton
                source:clearInput_area.pressed ?"images/delete-down.png":"images/Delete.png"
                width: 25
                height: inputLang.height
                anchors.left: parent.left;anchors.leftMargin: MyStyle.marginBetween
                anchors.top: parent.top;anchors.topMargin: MyStyle.marginTop
                MouseArea {
                            id: clearInput_area
                            anchors.fill: parent
                            hoverEnabled: true
                        }
            }
            TextArea {
                id: textInput
                anchors.top:inputLang.bottom
                width:parent.width
                height:130
                font.pixelSize: 14
                style:LightTextAreaStyle{}
                anchors.left:parent.left;anchors.leftMargin: MyStyle.marginMicro
                anchors.right:parent.right;anchors.rightMargin: MyStyle.marginMicro
                anchors.bottom:parent.bottom;anchors.bottomMargin: MyStyle.marginMicro

            }
        }
        CheckBox{
            id:checkTransleteInImage
            anchors.left: input.left; //anchors.leftMargin: MyStyle.marginBetween
            anchors.top:input.bottom; anchors.topMargin: 15//MyStyle.marginBetween//textInput.bottom
            checked: true
            text:"Переводить в извображение"
        }
        Rectangle{
            id:translateButton
            anchors.right: input.right; anchors.rightMargin: 10
            anchors.top: input.bottom;anchors.topMargin: 13//MyStyle.marginBetween
            color:translateButton_area.pressed ? MyStyle.buttonColor: MyStyle.buttonColorDown
            width: 80
            height: 30
            radius: 4

            Text{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Перевод")
                color:MyStyle.textButtonColor
            }
            MouseArea {
                        id: translateButton_area
                        anchors.fill: parent
                        hoverEnabled: true
                    }

        }
        DropShadow {
                anchors.fill: translateButton
                horizontalOffset: 1
                verticalOffset: 1
                radius: 8.0
                samples: 16
                color: "#80000000"
                source: translateButton


            }
        Image{
            id:replaceButton
            width: 30
            height: inputLang.height
            source:replaceButton_area.pressed ?"images/replace-down.png":"images/replace.png"
            anchors.left: input.right; anchors.leftMargin: 10
            MouseArea {
                        id: replaceButton_area
                        anchors.fill: parent
                        hoverEnabled: true
                    }

        }
        Rectangle{
            id:output
            anchors.left:replaceButton.right; anchors.leftMargin: 10
            height:140
            border.color: MyStyle.greyColor
            width: MyStyle.minWidthInputBox<mainWindow.width*0.43?mainWindow.width*0.43 : MyStyle.minWidthInputBox
            ComboBox{
                id:outputLang
                anchors.left: parent.left; anchors.leftMargin: MyStyle.marginBetween
                anchors.top: parent.top;anchors.topMargin: MyStyle.marginTop
                style:LightComboBoxStyle{id:combo4}
                width:100
                model:ListModel{
                    ListElement {text:"English"}
                    ListElement {text:"Русский"}
                }
            }
            ComboBox{
                id:chooseTranslator
                anchors.left: outputLang.right;anchors.leftMargin: MyStyle.marginBetween//10
                anchors.top: parent.top;anchors.topMargin: MyStyle.marginTop
                style:LightComboBoxStyle{id:combo2}
                width:100
                model:ListModel{
                    ListElement{text:"Yandex"}
                    ListElement{text:"Bing"}
                }

            }

            Image{
                id:volumeOutputButton
                width: 25
                height: chooseTranslator.height        
                anchors.left:chooseTranslator.right;anchors.leftMargin:MyStyle.marginBetween //10
                source: volumeOutput_area.pressed ? "images/Medium Volume Filled-50.png": "images/volume.png"
                anchors.top: parent.top;anchors.topMargin: MyStyle.marginTop
                MouseArea {
                            id: volumeOutput_area
                            anchors.fill: parent
                            hoverEnabled: true
                        }

            }

            TextArea {
                id: textOutput
                anchors.top: outputLang.bottom
                y: outputLang.height
                width: parent.width
                height: 94
                text: qsTr("")
                font.pixelSize: 14
                style:LightTextAreaStyle{}
                anchors.left:parent.left;anchors.leftMargin: MyStyle.marginMicro
                anchors.right:parent.right;anchors.rightMargin: MyStyle.marginMicro
                anchors.bottom:parent.bottom;anchors.bottomMargin: MyStyle.marginMicro
                readOnly: true

            }

        }
        Rectangle{
            id:cardBox
            color:MyStyle.backgroundCardBox
            anchors.top: translateButton.bottom; anchors.topMargin: 30
            anchors.left:parent.left; anchors.leftMargin: input.x
            width: output.x+output.width-input.x
            height: mainWindow.height-y-130<MyStyle.minHeightCartBox ?
                        MyStyle.minHeightCartBox :  mainWindow.height-y-130
            border.color: MyStyle.greyColor
            ComboBox{
                id:imageSource
                anchors.left: parent.left
                anchors.top: parent.top
                style:LightComboBoxStyle{}
                anchors.horizontalCenter:parent.horizontalCenter
                width:100//parent.width-inputVoice.width
                model:ListModel{
                    ListElement {text:"Instagrame"}
                    ListElement {text:"Bing"}
                }
            }
            Rectangle{
                id:leftButton
                width: 50
                height: 50
                radius: width/2
                color:!left_area.pressed ? MyStyle.buttonColorDown: MyStyle.buttonColor
                anchors.verticalCenter: parent.verticalCenter
                anchors.left:parent.left; anchors.leftMargin: -15
                MouseArea {
                            id: left_area
                            anchors.fill: parent
                            hoverEnabled: true
                        }
                Image{
                    source: "images/arrow-left-white.png"
                    width: parent.width/2
                    height: width
                    anchors.centerIn: parent
                }
            }
            DropShadow {

                        anchors.fill: source
                        //horizontalOffset: 0.5
                        verticalOffset: 0.5
                        fast: false
                        radius:8.0
                        samples:16
                        color: "#78000000"
                        source: leftButton
                        smooth: true;
                        cached: true;
                }

            Row{
                id:container
                spacing: 2
                anchors.left: leftButton.right;anchors.leftMargin: 10
                anchors.right: rightButton.left;anchors.rightMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: imageSource.bottom;
                width: parent.width-2*leftButton.width-2*leftButton.anchors.leftMargin-2*anchors.leftMargin
                height: parent.height-imageSource.height

                Cart{
                    width:parent.height/1.5//parent.width/3.3
                    anchors.verticalCenter: parent.verticalCenter
                    //anchors.verticalCenterOffset: -136
                    //anchors.horizontalCenterOffset: 156
                }
            }
            Rectangle{
                id:rightButton
                width: 50
                height: 50
                radius: width/2
                color:!right_area.pressed ? MyStyle.buttonColorDown: MyStyle.buttonColor
                anchors.verticalCenter: parent.verticalCenter
                anchors.right:parent.right; anchors.rightMargin: -15
                MouseArea {
                            id: right_area
                            anchors.fill: parent
                            hoverEnabled: true
                        }
                Image{
                    source: "images/arrow-right-white.png"
                    width: parent.width/2
                    height: width
                    anchors.centerIn: parent
                }
            }
            DropShadow {

                    anchors.fill: source
                    horizontalOffset: 0
                    verticalOffset: 0.5
                    //fast: false
                    radius:8.0
                    samples:16
                    color: "#78000000"
                    source: rightButton
                    //smooth: true;
                   // cached: true;
            }
        }
    }
}
