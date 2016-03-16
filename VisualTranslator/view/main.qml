import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Private 1.0
import QtGraphicalEffects 1.0
import Qt.controller.appmanager 1.0
import "."
Window {
    id:mainWindow
    visible: true
    width: 800
    height: 600
    color:MyStyle.backgroundColor

    property string langInput: "ru"
    property string langOutput: "en"

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
            height:140
            border.color: MyStyle.greyColor
            ComboBox{
                id:inputLang
                currentIndex: 1
                anchors.right: parent.right; anchors.rightMargin: 5
                anchors.top: parent.top;anchors.topMargin: MyStyle.marginTop
                style:LightComboBoxStyle{ id:combo1 }
                width:100

                model:ListModel{
                    ListElement {text:"English"}
                    ListElement {text:"Русский"}
                }
                onCurrentIndexChanged: {
                    if(0===currentIndex) langInput="en"
                    else langInput="ru"
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
                            onClicked:{
                                textInput.text=""
                                textOutput.text=""
                            }

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
                        onClicked:{
                            var str=AppManager.translate(chooseTranslator.currentIndex,inputLang.currentIndex,outputLang.currentIndex,textInput.text)//yandexTranslater.yantranslate();
                            textOutput.text=qsTr(str);
                            container.model.clear()
                            if(checkTransleteInImage.checked)
                            {
                            var words=AppManager.getDataForCards(imageSource.currentIndex,textInput.text)
                            for(var i=0;i<words[0].length;i++)
                               container.model.append({"myword":words[0][i],"mytranslation":words[1][i],
                                                      "mysource":words[2][i]})
                            }

                           // if(checkTransleteInImage.checked)
                            //card1.urlImage=instaPicture.getPicture(str);
                        }
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
                        onClicked: {
                            var t=inputLang.currentIndex
                            inputLang.currentIndex=outputLang.currentIndex
                            outputLang.currentIndex=t
                            t=textInput.text
                            textInput.text=textOutput.text
                            textOutput.text=" "
                        }
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
                currentIndex: 0
                anchors.left: parent.left; anchors.leftMargin: MyStyle.marginBetween
                anchors.top: parent.top;anchors.topMargin: MyStyle.marginTop
                style:LightComboBoxStyle{id:combo4}
                width:100
                model:ListModel{
                    ListElement {text:"English"}
                    ListElement {text:"Русский"}
                }
                onCurrentIndexChanged: {
                    if(currentIndex==0) langOutput="en"
                    else langOutput="ru"
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
                    ListElement{text:"Multilect"}
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
                width:100
                model:ListModel{
                    ListElement {text:"Instagrame"}
                    ListElement {text:"GettyImag"}
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
                            onClicked: container.contentX-=container.contentX>0?50:0
                        }
                Image{
                    source: "images/arrow-left-white.png"
                    width: parent.width/2
                    height: width
                    anchors.centerIn: parent
                }
            }

            ListView{
                id:container
                spacing: 10
                orientation: ListView.Horizontal
                anchors.left: leftButton.right;anchors.leftMargin: 10
                anchors.right: rightButton.left;anchors.rightMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: imageSource.bottom;
                width: parent.width-2*leftButton.width-2*leftButton.anchors.leftMargin-2*anchors.leftMargin
                height: parent.height-imageSource.height

                model:ListModel{}
                delegate: Component{
                    id:componentModel
                    Card{urlImage: mysource
                         word:myword
                         translation: mytranslation
                         width:parent.height/1.5
                         //ma:MouseArea{onClicked: manager.updatePicture(word)}

                    }
                }
                cacheBuffer: 250
                clip:true
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
                            onClicked: container.contentX+=50
                        }
                Image{
                    source: "images/arrow-right-white.png"
                    width: parent.width/2
                    height: width
                    anchors.centerIn: parent
                }
            }
        }
    }
}
