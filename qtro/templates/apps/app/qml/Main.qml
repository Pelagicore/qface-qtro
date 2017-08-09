import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


{% for module in system.modules %}
import {{module}} 1.0
{% endfor %}

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("{{project}}")

    Button {
        anchors.centerIn: parent
        text: "Quit"
        onClicked: Qt.quit()
    }

{% for module in system.modules %}
{% for interface in module.interfaces %}
    {{interface}} {
        id: {{interface|lowerfirst}}Client
    }
{% endfor %}
{% endfor %}

}
