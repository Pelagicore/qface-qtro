import QtQuick 2.8
import QtQml.Models 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

import org.example.echo 1.0

ApplicationWindow {
    visible: true
    width: 480
    height: 800
    title: qsTr("Echo")

    Echo {
        id: echo
    }

    ListView {
        anchors.fill: parent
        model: ObjectModel {
            ItemDelegate {
                text: "MSG: " + echo.message
            }
            ItemDelegate {
                text: "Say Hello"
                onClicked: {
                    echo.sayHello();
                }
            }
        }
    }

}
