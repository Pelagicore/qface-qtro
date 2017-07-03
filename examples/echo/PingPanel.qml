import QtQuick 2.4

PingPanelForm {
    id: root
    signal ping(string message)
    pingField.onClicked: {
        root.ping(messageField.text);
    }
}
