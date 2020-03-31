import QtQuick 2.12
import QtQuick.Controls 2.12


SpinBox {
    id: control
    value: 50
    editable: true
    contentItem: TextInput {
        z: 2
        text: control.textFromValue(control.value, control.locale)

        font: control.font
        color: "orange"
        selectionColor: "orange"
        selectedTextColor: "black"
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter

        readOnly: !control.editable
        validator: control.validator
        inputMethodHints: Qt.ImhFormattedNumbersOnly
    }

    up.indicator: Rectangle {
        x: control.mirrored ? 0 : parent.width - width
        height: parent.height
        implicitWidth: 40
        implicitHeight: 40
        //radius: width/10
        color: control.up.pressed ? "white" : "black"
        border.color: enabled ? "orange" : "white"

        Text {
            text: "+"
            font.pixelSize: control.font.pixelSize * 2
            color: "orange"
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    down.indicator: Rectangle {
        x: control.mirrored ? parent.width - width : 0
        height: parent.height
        implicitWidth: 40
        implicitHeight: 40
        //radius: width/10
        color: control.down.pressed ? "white" : "black"
        border.color: enabled ? "orange" : "white"

        Text {
            text: "-"
            font.pixelSize: control.font.pixelSize * 2
            color: "orange"
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    background: Rectangle {
        implicitWidth: 150
        color: "black"
    }
}
