import QtQuick 2.8
import QtQml.Models 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

import org.example.ping 1.0

ApplicationWindow {
    visible: true
    width: 480
    height: 800
    title: qsTr("Ping")

    Ping {
        id: ping
        onPinged: {
            console.log('message: ')
            panel.response = message.source + ' / ' + message.message
            ping.echo("done");
        }
    }

    PingPanel {
        id: panel
        anchors.fill: parent
        view.model: ping.messages
        onPing: {
            ping.ping(message);
        }
    }

}
