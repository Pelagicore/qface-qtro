import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    width: 400
    height: 400
//    property alias responseField: responseField
    property alias pingField: pingField
    property alias messageField: messageField
    property alias response: responseField.text

    GridLayout {
        id: gridLayout
        width: 401
        columns: 2
        anchors.fill: parent

        TextField {
            id: messageField
            text: qsTr("Hello")
            Layout.fillWidth: true
        }

        Button {
            id: pingField
            text: qsTr("Ping")
        }

        TextField {
            id: responseField
            width: 335
            height: 40
            text: qsTr("")
            Layout.fillWidth: true
            Layout.columnSpan: 2
            Layout.rowSpan: 1
        }

        Item {
            id: item1
            width: 200
            height: 200
            Layout.columnSpan: 2
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
