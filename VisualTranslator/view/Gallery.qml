import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    id: root
    width: 400; //height: 400
    property string url:""
    Image{
        anchors.centerIn: parent
        source:url
        width: 350
        height: 350
    }

   /* Text {
        anchors.centerIn: parent
        text: qsTr(url)
    }*/
}
