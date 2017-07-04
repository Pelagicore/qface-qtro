import QtQuick 2.4
import QtQuick.Controls 2.2

PingPanelForm {
    id: root
    signal ping(string message)
    pingField.onClicked: {
        root.ping(messageField.text);
    }
    view.delegate: ItemDelegate {
        width: ListView.view.width
        text: model.message ? model.message: '???'
    }
}
