import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    width: 400
    height: 400
    property alias view: view
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

        ListView {
            id: view
            width: 110
            height: 160
            Layout.columnSpan: 2
            Layout.rowSpan: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row1
                    spacing: 10
                    Rectangle {
                        width: 40
                        height: 40
                        color: colorCode
                    }

                    Text {
                        text: name
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                    }
                }
            }
            model: ListModel {
                ListElement {
                    name: "Grey"
                    colorCode: "grey"
                }

                ListElement {
                    name: "Red"
                    colorCode: "red"
                }

                ListElement {
                    name: "Blue"
                    colorCode: "blue"
                }

                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
            }
        }
    }
}
